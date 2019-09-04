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
 int /*<<< orphan*/  crsourcergba (int /*<<< orphan*/ *,double,double,int,double) ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathArcTo (int /*<<< orphan*/ *,double,double,double,int,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathCloseFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathNewFigureWithArc (int /*<<< orphan*/ *,double,double,double,int,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 double uiPi ; 

__attribute__((used)) static void drawCSRoundRect(uiAreaDrawParams *p)
{
	double x         = 25.6,        /* parameters like cairo_rectangle */
		y         = 25.6,
		width         = 204.8,
		height        = 204.8,
		aspect        = 1.0,     /* aspect ratio */
		corner_radius = height / 10.0;   /* and corner curvature radius */

	double radius = corner_radius / aspect;
	double degrees = uiPi / 180.0;

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

	// top right corner
	uiDrawPathNewFigureWithArc(path,
		x + width - radius, y + radius,
		radius,
		-90 * degrees, uiPi / 2,
		0);
	// bottom right corner
	uiDrawPathArcTo(path,
		x + width - radius, y + height - radius,
		radius,
		0 * degrees, uiPi / 2,
		0);
	// bottom left corner
	uiDrawPathArcTo(path,
		x + radius, y + height - radius,
		radius,
		90 * degrees, uiPi / 2,
		0);
	// top left corner
	uiDrawPathArcTo(path,
		x + radius, y + radius,
		radius,
		180 * degrees, uiPi / 2,
		0);
	uiDrawPathCloseFigure(path);
	uiDrawPathEnd(path);

	crsourcergba(&source, 0.5, 0.5, 1, 1);
	uiDrawFill(p->Context, path, &source);
	crsourcergba(&source, 0.5, 0, 0, 0.5);
	sp.Thickness = 10.0;
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);
}