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
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawPathNewFigureWithArc (int /*<<< orphan*/ *,double,double,double,double,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 double uiPi ; 

__attribute__((used)) static void drawCSArc(uiAreaDrawParams *p)
{
	double xc = 128.0;
	double yc = 128.0;
	double radius = 100.0;
	double angle1 = 45.0  * (uiPi / 180.0);
	double angle2 = 180.0 * (uiPi / 180.0);
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

	sp.Thickness = 10.0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigureWithArc(path,
		xc, yc,
		radius,
		angle1,
		angle2 - angle1,
		0);
	uiDrawPathEnd(path);
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);

	crsourcergba(&source, 1, 0.2, 0.2, 0.6);
	sp.Thickness = 6.0;

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigureWithArc(path,
		xc, yc,
		10.0,
		0, 2 * uiPi,
		0);
	uiDrawPathEnd(path);
	uiDrawFill(p->Context, path, &source);
	uiDrawFreePath(path);

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigureWithArc(path,
		xc, yc,
		radius,
		angle1, 0,
		0);
	uiDrawPathLineTo(path, xc, yc);
	uiDrawPathNewFigureWithArc(path,
		xc, yc,
		radius,
		angle2, 0,
		0);
	uiDrawPathLineTo(path, xc, yc);
	uiDrawPathEnd(path);
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);
}