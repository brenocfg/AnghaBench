#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/ * datapoints ; 
 int uiSpinboxValue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointLocations(double width, double height, double *xs, double *ys)
{
	double xincr, yincr;
	int i, n;

	xincr = width / 9;		// 10 - 1 to make the last point be at the end
	yincr = height / 100;

	for (i = 0; i < 10; i++) {
		// get the value of the point
		n = uiSpinboxValue(datapoints[i]);
		// because y=0 is the top but n=0 is the bottom, we need to flip
		n = 100 - n;
		xs[i] = xincr * i;
		ys[i] = yincr * n;
	}
}