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
typedef  int /*<<< orphan*/  uiDrawMatrix ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
struct TYPE_7__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_2__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  d2dClear (TYPE_2__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  d2dCornflowerBlue ; 
 int /*<<< orphan*/  d2dForestGreen ; 
 int /*<<< orphan*/  d2dSolidBrush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  d2dWhite ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeAlternate ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/  uiDrawMatrixSetIdentity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawMatrixTranslate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathNewFigureWithArc (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uiDrawTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uiPi ; 

__attribute__((used)) static void drawD2DGeometryGroup(uiAreaDrawParams *p)
{
	uiDrawPath *alternate;
	uiDrawPath *winding;
	uiDrawBrush fill;
	uiDrawBrush stroke;
	uiDrawStrokeParams sp;
	uiDrawMatrix m;

	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	alternate = uiDrawNewPath(uiDrawFillModeAlternate);
	uiDrawPathNewFigureWithArc(alternate,
		105, 105,
		25,
		0, 2 * uiPi,
		0);
	uiDrawPathNewFigureWithArc(alternate,
		105, 105,
		50,
		0, 2 * uiPi,
		0);
	uiDrawPathNewFigureWithArc(alternate,
		105, 105,
		75,
		0, 2 * uiPi,
		0);
	uiDrawPathNewFigureWithArc(alternate,
		105, 105,
		100,
		0, 2 * uiPi,
		0);
	uiDrawPathEnd(alternate);

	winding = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigureWithArc(winding,
		105, 105,
		25,
		0, 2 * uiPi,
		0);
	uiDrawPathNewFigureWithArc(winding,
		105, 105,
		50,
		0, 2 * uiPi,
		0);
	uiDrawPathNewFigureWithArc(winding,
		105, 105,
		75,
		0, 2 * uiPi,
		0);
	uiDrawPathNewFigureWithArc(winding,
		105, 105,
		100,
		0, 2 * uiPi,
		0);
	uiDrawPathEnd(winding);

	d2dClear(p, d2dWhite, 1.0);

	// TODO grid

	// TODO the example doesn't provide these
	d2dSolidBrush(&fill, d2dForestGreen, 1.0);
	d2dSolidBrush(&stroke, d2dCornflowerBlue, 1.0);

	sp.Thickness = 1.0;
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;

	uiDrawFill(p->Context, alternate, &fill);
	uiDrawStroke(p->Context, alternate, &stroke, &sp);
	// TODO text

	uiDrawMatrixSetIdentity(&m);
	uiDrawMatrixTranslate(&m, 300, 0);
	uiDrawTransform(p->Context, &m);
	uiDrawFill(p->Context, winding, &fill);
	uiDrawStroke(p->Context, winding, &stroke, &sp);
//	// TODO text

	uiDrawFreePath(winding);
	uiDrawFreePath(alternate);
}