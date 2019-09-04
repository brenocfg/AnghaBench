#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double Thickness; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Join; int /*<<< orphan*/  Cap; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_8__ {int A; scalar_t__ B; scalar_t__ G; scalar_t__ R; int /*<<< orphan*/  Type; } ;
typedef  TYPE_2__ uiDrawBrush ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
struct TYPE_9__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_3__ uiAreaDrawParams ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 double atof (char*) ; 
 int /*<<< orphan*/  negative ; 
 int /*<<< orphan*/  radians ; 
 int /*<<< orphan*/  startAngle ; 
 int /*<<< orphan*/  sweep ; 
 scalar_t__ uiCheckboxChecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathArcTo (int /*<<< orphan*/ *,double,double,double,double,double,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 char* uiEntryText (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeText (char*) ; 
 int uiPi ; 

__attribute__((used)) static void handlerDraw(uiAreaHandler *a, uiArea *area, uiAreaDrawParams *p)
{
	double xc = 128.0;
	double yc = 128.0;
	double radius = 100.0;
	uiDrawBrush source;
	uiDrawStrokeParams sp;
	uiDrawPath *path;
	char *startText;
	char *sweepText;
	double factor;

	source.Type = uiDrawBrushTypeSolid;
	source.R = 0;
	source.G = 0;
	source.B = 0;
	source.A = 1;
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	startText = uiEntryText(startAngle);
	sweepText = uiEntryText(sweep);

	factor = uiPi / 180;
	if (uiCheckboxChecked(radians))
		factor = 1;

	sp.Thickness = 10.0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, xc, yc);
	uiDrawPathArcTo(path,
		xc, yc,
		radius,
		atof(startText) * factor,
		atof(sweepText) * factor,
		uiCheckboxChecked(negative));
	uiDrawPathEnd(path);
	uiDrawStroke(p->Context, path, &source, &sp);
	uiDrawFreePath(path);

	uiFreeText(startText);
	uiFreeText(sweepText);
}