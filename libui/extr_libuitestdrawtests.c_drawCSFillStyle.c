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
struct TYPE_5__ {int Thickness; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Join; int /*<<< orphan*/  Cap; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawMatrix ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
struct TYPE_6__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_2__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  crsourcergba (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,double,int) ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeAlternate ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/  uiDrawMatrixSetIdentity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawMatrixTranslate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathNewFigureWithArc (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uiDrawTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uiPi ; 

__attribute__((used)) static void drawCSFillStyle(uiAreaDrawParams *p)
{
	uiDrawBrush source;
	uiDrawStrokeParams sp;
	uiDrawPath *path;
	uiDrawMatrix m;

	crsourcergba(&source, 0, 0, 0, 1);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	sp.Thickness = 6;

	path = uiDrawNewPath(uiDrawFillModeAlternate);
	uiDrawPathAddRectangle(path, 12, 12, 232, 70);
	uiDrawPathNewFigureWithArc(path,
		64, 64,
		40,
		0, 2*uiPi,
		0);
	uiDrawPathNewFigureWithArc(path,
		192, 64,
		40,
		0, -2*uiPi,
		1);
	uiDrawPathEnd(path);

	crsourcergba(&source, 0, 0.7, 0, 1);
	uiDrawFill(p->Context, path, &source);
	crsourcergba(&source, 0, 0, 0, 1);
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);

	uiDrawMatrixSetIdentity(&m);
	uiDrawMatrixTranslate(&m, 0, 128);
	uiDrawTransform(p->Context, &m);

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, 12, 12, 232, 70);
	uiDrawPathNewFigureWithArc(path,
		64, 64,
		40,
		0, 2*uiPi,
		0);
	uiDrawPathNewFigureWithArc(path,
		192, 64,
		40,
		0, -2*uiPi,
		1);
	uiDrawPathEnd(path);

	crsourcergba(&source, 0, 0, 0.9, 1);
	uiDrawFill(p->Context, path, &source);
	crsourcergba(&source, 0, 0, 0, 1);
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);
}