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
struct TYPE_5__ {double Thickness; void* MiterLimit; void* Join; void* Cap; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawMatrix ;
typedef  int /*<<< orphan*/  uiDrawBrush ;
struct TYPE_6__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_2__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  d2dBlack ; 
 int /*<<< orphan*/  d2dForestGreen ; 
 int /*<<< orphan*/  d2dSolidBrush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  d2dWhite ; 
 void* uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 void* uiDrawLineCapFlat ; 
 void* uiDrawLineJoinMiter ; 
 int /*<<< orphan*/  uiDrawMatrixRotate (int /*<<< orphan*/ *,double,double,double) ; 
 int /*<<< orphan*/  uiDrawMatrixSetIdentity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawMatrixTranslate (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawRestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uiDrawTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uiPi ; 

__attribute__((used)) static void drawD2DMultiTransforms(uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawBrush original;
	uiDrawBrush fill;
	uiDrawBrush transform;
	uiDrawStrokeParams originalsp;
	uiDrawStrokeParams transformsp;
	uiDrawMatrix mtranslate;
	uiDrawMatrix mrotate;

	originalsp.Dashes = NULL;
	originalsp.NumDashes = 0;
	originalsp.DashPhase = 0;
	transformsp.Dashes = NULL;
	transformsp.NumDashes = 0;
	transformsp.DashPhase = 0;

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, 300.0, 40.0, 360.0 - 300.0, 100.0 - 40.0);
	uiDrawPathEnd(path);

	// TODO the example doesn't specify what these should be
	d2dSolidBrush(&original, d2dBlack, 1.0);
	d2dSolidBrush(&fill, d2dWhite, 0.5);
	d2dSolidBrush(&transform, d2dForestGreen, 1.0);
	// TODO this needs to be dashed
	originalsp.Thickness = 1.0;
	originalsp.Cap = uiDrawLineCapFlat;
	originalsp.Join = uiDrawLineJoinMiter;
	originalsp.MiterLimit = uiDrawDefaultMiterLimit;
	transformsp.Thickness = 1.0;
	transformsp.Cap = uiDrawLineCapFlat;
	transformsp.Join = uiDrawLineJoinMiter;
	transformsp.MiterLimit = uiDrawDefaultMiterLimit;

	uiDrawMatrixSetIdentity(&mtranslate);
	uiDrawMatrixTranslate(&mtranslate, 20.0, 10.0);
	uiDrawMatrixSetIdentity(&mrotate);
	uiDrawMatrixRotate(&mrotate,
		330.0, 70.0,
		45.0 * (uiPi / 180));

	// save for when we do the opposite one
	uiDrawSave(p->Context);

	uiDrawStroke(p->Context, path, &original, &originalsp);

	uiDrawTransform(p->Context, &mrotate);
	uiDrawTransform(p->Context, &mtranslate);

	uiDrawFill(p->Context, path, &fill);
	uiDrawStroke(p->Context, path, &transform, &transformsp);

	uiDrawRestore(p->Context);
	uiDrawFreePath(path);

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, 40.0, 40.0, 100.0 - 40.0, 100.0 - 40.0);
	uiDrawPathEnd(path);

	uiDrawMatrixSetIdentity(&mtranslate);
	uiDrawMatrixTranslate(&mtranslate, 20.0, 10.0);
	uiDrawMatrixSetIdentity(&mrotate);
	uiDrawMatrixRotate(&mrotate,
		70.0, 70.0,
		45.0 * (uiPi / 180));

	uiDrawStroke(p->Context, path, &original, &originalsp);

	uiDrawTransform(p->Context, &mtranslate);
	uiDrawTransform(p->Context, &mrotate);

	uiDrawFill(p->Context, path, &fill);
	uiDrawStroke(p->Context, path, &transform, &transformsp);

	uiDrawFreePath(path);
}