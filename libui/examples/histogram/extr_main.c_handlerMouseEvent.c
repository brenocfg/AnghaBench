#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Y; int /*<<< orphan*/  X; int /*<<< orphan*/  AreaHeight; int /*<<< orphan*/  AreaWidth; } ;
typedef  TYPE_1__ uiAreaMouseEvent ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 int currentPoint ; 
 int /*<<< orphan*/  graphSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  histogram ; 
 scalar_t__ inPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  pointLocations (double,double,double*,double*) ; 
 int /*<<< orphan*/  uiAreaQueueRedrawAll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
	double graphWidth, graphHeight;
	double xs[10], ys[10];
	int i;

	graphSize(e->AreaWidth, e->AreaHeight, &graphWidth, &graphHeight);
	pointLocations(graphWidth, graphHeight, xs, ys);

	for (i = 0; i < 10; i++)
		if (inPoint(e->X, e->Y, xs[i], ys[i]))
			break;
	if (i == 10)		// not in a point
		i = -1;

	currentPoint = i;
	// TODO only redraw the relevant area
	uiAreaQueueRedrawAll(histogram);
}