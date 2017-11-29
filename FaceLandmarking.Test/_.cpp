#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "../FaceLandmarking.Reader/dataset-reader.hpp"
#include "../FaceLandmarking.Reader/mask-io.hpp"
#include "../FaceLandmarking/mask-transformation/mask-normalizer.hpp"
#include "../FaceLandmarking/mask-transformation/mask-avg.hpp"
#include "../FaceLandmarking.Learning/average-face.hpp"
#include "ui/mask-ui.hpp"

using namespace cv;
using namespace std;
using namespace FaceLandmarking;

int main(int argc, char** argv)
{
	auto dataPath = "D:\\Programy\\FaceLandmarking\\Data";

	Learning::AverageFace averageFaceLoader(dataPath);
	FaceMask averageMask = averageFaceLoader.load();




	Reader::DatasetReader reader("D:\\Programy\\FaceLandmarking\\Data");

	namedWindow("example", WINDOW_AUTOSIZE);

	while (true)
	{
		auto key = waitKey(25);

		if (key == 32 && reader.hasNext()) {
			auto example = reader.loadNext();
			example.scaleFace(200, 200);

			auto normalizedMask = MaskTransformations::MaskNormalizer::normalizeMask(example.mask, Math::Point<float>(50, 50), Math::Size<float>(100, 100));
			auto averagenormalizedMask = MaskTransformations::MaskNormalizer::normalizeMask(averageMask, example.mask.faceCenter(), example.mask.faceSize());

			Mat exampleImage = example.image;
			exampleImage = Test::UI::MaskUI::drawMask(exampleImage, example.mask);
			exampleImage = Test::UI::MaskUI::drawMask(exampleImage, normalizedMask);
			exampleImage = Test::UI::MaskUI::drawMask(exampleImage, averageMask);
			exampleImage = Test::UI::MaskUI::drawMask(exampleImage, averagenormalizedMask, cv::Scalar(0, 0, 255));

			imshow("example", exampleImage);
		}
		else if (key >= 0)
			break;
	}

	return 0;

	//VideoCapture cap(0);
	//if (!cap.isOpened())
	//	return -1;
	//
	//Mat edges;
	//Mat gray;
	//Mat color;
	//Mat hsv[3];
	//Mat laplace1;
	//Mat laplace2;
	//Mat th;
	//
	//namedWindow("real", WINDOW_AUTOSIZE);
	//namedWindow("edges", WINDOW_AUTOSIZE);
	//namedWindow("gray", WINDOW_AUTOSIZE);
	//namedWindow("h", WINDOW_AUTOSIZE);
	//namedWindow("s", WINDOW_AUTOSIZE);
	//namedWindow("th", WINDOW_AUTOSIZE);
	//
	//for (;;)
	//{
	//	Mat frame;
	//	cap >> frame;
	//
	//	GaussianBlur(frame, frame, Size(5, 5), 2.5, 2.5);
	//
	//	//cvtColor(frame, edges, COLOR_BGR2GRAY);
	//	//Canny(edges, edges, 20, 50);
	//	//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
	//
	//	cvtColor(frame, gray, COLOR_BGR2GRAY);
	//
	//	frame.copyTo(color);
	//	cvtColor(color, color, COLOR_BGR2HSV_FULL);
	//	split(color, hsv);
	//
	//	//Canny(hsv[0], hsv[0], 100, 200);
	//	//Canny(hsv[1], hsv[1], 150, 200);
	//
	//	//frame.copyTo(laplace1);
	//	//Laplacian(laplace1, laplace2, CV_64F);
	//	//GaussianBlur(laplace2, laplace2, Size(7, 7), 1.5, 1.5);
	//	//Canny(laplace2, laplace2, 20, 50);
	//
	//	threshold(hsv[0], th, 190, 0, 3);
	//	threshold(th, th, 220, 0, 4);
	//
	//	imshow("real", frame);
	//	//imshow("edges", edges);
	//	imshow("gray", gray);
	//	imshow("h", hsv[0]);
	//	imshow("s", hsv[1]);
	//	imshow("th", hsv[2]);
	//
	//	if (waitKey(30) >= 0) break;
	//}
	//
	//return 0;
}

//int main(int argc, char** argv)
//{
//	Mat image;
//	image = imread("Lenna.png", IMREAD_COLOR);
//	if (image.empty())
//	{
//		cout << "Could not open or find the image" << std::endl;
//		return -1;
//	}
//
//	Mat edges;
//	Canny(image, edges, 100, 200);
//
//	namedWindow("1", WINDOW_AUTOSIZE);
//	imshow("1", image);
//
//	namedWindow("2", WINDOW_AUTOSIZE);
//	imshow("2", edges);
//
//	waitKey(0);
//	return 0;
//}