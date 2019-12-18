#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {double Thickness; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Join; int /*<<< orphan*/  Cap; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
struct TYPE_7__ {int AreaWidth; int AreaHeight; int /*<<< orphan*/  Context; } ;
typedef  TYPE_2__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  d2dClear (TYPE_2__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  d2dCornflowerBlue ; 
 int /*<<< orphan*/  d2dLightSlateGray ; 
 int /*<<< orphan*/  d2dSolidBrush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  d2dWhite ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void drawD2DSimpleApp(uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawBrush lightSlateGray;
	uiDrawBrush cornflowerBlue;
	uiDrawStrokeParams sp;
	int x, y;

	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	d2dSolidBrush(&lightSlateGray, d2dLightSlateGray, 1.0);
	d2dSolidBrush(&cornflowerBlue, d2dCornflowerBlue, 1.0);

	d2dClear(p, d2dWhite, 1.0);

	sp.Thickness = 0.5;
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;

	for (x = 0; x < p->AreaWidth; x += 10) {
		path = uiDrawNewPath(uiDrawFillModeWinding);
		uiDrawPathNewFigure(path, x, 0);
		uiDrawPathLineTo(path, x, p->AreaHeight);
		uiDrawPathEnd(path);
		uiDrawStroke(p->Context, path, &lightSlateGray, &sp);
		uiDrawFreePath(path);
	}

	for (y = 0; y < p->AreaHeight; y += 10) {
		path = uiDrawNewPath(uiDrawFillModeWinding);
		uiDrawPathNewFigure(path, 0, y);
		uiDrawPathLineTo(path, p->AreaWidth, y);
		uiDrawPathEnd(path);
		uiDrawStroke(p->Context, path, &lightSlateGray, &sp);
		uiDrawFreePath(path);
	}

	double left, top, right, bottom;

	left = p->AreaWidth / 2.0 - 50.0;
	right = p->AreaWidth / 2.0 + 50.0;
	top = p->AreaHeight / 2.0 - 50.0;
	bottom = p->AreaHeight / 2.0 + 50.0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, left, top, right - left, bottom - top);
	uiDrawPathEnd(path);
	uiDrawFill(p->Context, path, &lightSlateGray);
	uiDrawFreePath(path);

	left = p->AreaWidth / 2.0 - 100.0;
	right = p->AreaWidth / 2.0 + 100.0;
	top = p->AreaHeight / 2.0 - 100.0;
	bottom = p->AreaHeight / 2.0 + 100.0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, left, top, right - left, bottom - top);
	uiDrawPathEnd(path);
	sp.Thickness = 1.0;
	uiDrawStroke(p->Context, path, &cornflowerBlue, &sp);
	uiDrawFreePath(path);
}