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
typedef  int /*<<< orphan*/  uiDrawPath ;

/* Variables and functions */
 int /*<<< orphan*/  pointLocations (double,double,double*,double*) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathCloseFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,double,double) ; 

__attribute__((used)) static uiDrawPath *constructGraph(double width, double height, int extend)
{
	uiDrawPath *path;
	double xs[10], ys[10];
	int i;

	pointLocations(width, height, xs, ys);

	path = uiDrawNewPath(uiDrawFillModeWinding);

	uiDrawPathNewFigure(path, xs[0], ys[0]);
	for (i = 1; i < 10; i++)
		uiDrawPathLineTo(path, xs[i], ys[i]);

	if (extend) {
		uiDrawPathLineTo(path, width, height);
		uiDrawPathLineTo(path, 0, height);
		uiDrawPathCloseFigure(path);
	}

	uiDrawPathEnd(path);
	return path;
}