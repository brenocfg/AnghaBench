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
 int /*<<< orphan*/  crsourcergba (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathBezierTo (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  uiDrawPathCloseFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void drawCSFillAndStroke2(uiAreaDrawParams *p)
{
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

	uiDrawPathNewFigure(path, 128.0, 25.6);
	uiDrawPathLineTo(path, 230.4, 230.4);
	uiDrawPathLineTo(path, 230.4 - 102.4, 230.4 + 0.0);
	uiDrawPathBezierTo(path, 51.2, 230.4, 51.2, 128.0, 128.0, 128.0);
	uiDrawPathCloseFigure(path);

	uiDrawPathNewFigure(path, 64.0, 25.6);
	uiDrawPathLineTo(path, 64.0 + 51.2, 25.6 + 51.2);
	uiDrawPathLineTo(path, 64.0 + 51.2 -51.2, 25.6 + 51.2 + 51.2);
	uiDrawPathLineTo(path, 64.0 + 51.2 -51.2 -51.2, 25.6 + 51.2 + 51.2 -51.2);
	uiDrawPathCloseFigure(path);

	uiDrawPathEnd(path);

	sp.Thickness = 10.0;
	crsourcergba(&source, 0, 0, 1, 1);
	uiDrawFill(p->Context, path, &source);
	crsourcergba(&source, 0, 0, 0, 1);
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);
}