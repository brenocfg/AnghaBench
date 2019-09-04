#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double Thickness; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Join; int /*<<< orphan*/  Cap; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
struct TYPE_6__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_2__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  crsourcergba (int /*<<< orphan*/ *,int,double,double,double) ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathBezierTo (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void drawCSCurveTo(uiAreaDrawParams *p)
{
	double x=25.6,  y=128.0;
	double x1=102.4, y1=230.4,
		x2=153.6, y2=25.6,
		x3=230.4, y3=128.0;
	uiDrawBrush source;
	uiDrawStrokeParams sp;
	uiDrawPath *path;

	crsourcergba(&source, 0, 0, 0, 1);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	path = uiDrawNewPath(uiDrawFillModeWinding);

	uiDrawPathNewFigure(path, x, y);
	uiDrawPathBezierTo(path, x1, y1, x2, y2, x3, y3);
	uiDrawPathEnd(path);
	sp.Thickness = 10.0;
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);

	crsourcergba(&source, 1, 0.2, 0.2, 0.6);
	sp.Thickness = 6.0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, x, y);
	uiDrawPathLineTo(path, x1, y1);
	uiDrawPathNewFigure(path, x2, y2);
	uiDrawPathLineTo(path, x3, y3);
	uiDrawPathEnd(path);
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);
}