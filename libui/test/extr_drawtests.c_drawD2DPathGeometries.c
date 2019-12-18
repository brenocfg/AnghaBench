#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {double Thickness; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Join; int /*<<< orphan*/  Cap; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_12__ {double Pos; double A; int /*<<< orphan*/  B; int /*<<< orphan*/  G; int /*<<< orphan*/  R; } ;
typedef  TYPE_2__ uiDrawBrushGradientStop ;
struct TYPE_13__ {int X0; int Y0; int X1; int Y1; int OuterRadius; int NumStops; TYPE_2__* Stops; int /*<<< orphan*/  Type; } ;
typedef  TYPE_3__ uiDrawBrush ;
struct TYPE_14__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_4__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  d2dBlack ; 
 int /*<<< orphan*/  d2dClear (TYPE_4__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  d2dColorToRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d2dForestGreen ; 
 int /*<<< orphan*/  d2dLightSkyBlue ; 
 int /*<<< orphan*/  d2dOliveDrab ; 
 int /*<<< orphan*/  d2dSolidBrush (TYPE_3__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  d2dWhite ; 
 int /*<<< orphan*/  d2dYellow ; 
 int /*<<< orphan*/  d2dYellowGreen ; 
 int /*<<< orphan*/  uiDrawBrushTypeRadialGradient ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathBezierTo (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  uiDrawPathCloseFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawPathNewFigureWithArc (int /*<<< orphan*/ *,double,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uiPi ; 

__attribute__((used)) static void drawD2DPathGeometries(uiAreaDrawParams *p)
{
	uiDrawPath *leftMountain;
	uiDrawPath *rightMountain;
	uiDrawPath *sun;
	uiDrawPath *sunRays;
	uiDrawPath *river;
	uiDrawBrush radial;
	uiDrawBrush scene;
	uiDrawStrokeParams sp;
	uiDrawBrushGradientStop stops[2];

	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	// TODO this is definitely wrong but the example doesn't have the right brush in it
	radial.Type = uiDrawBrushTypeRadialGradient;
	radial.X0 = 75;
	radial.Y0 = 75;
	radial.X1 = 75;
	radial.Y1 = 75;
	radial.OuterRadius = 75;
	stops[0].Pos = 0.0;
	d2dColorToRGB(d2dYellow, &(stops[0].R), &(stops[0].G), &(stops[0].B));
	stops[0].A = 1.0;
	stops[1].Pos = 1.0;
	d2dColorToRGB(d2dForestGreen, &(stops[1].R), &(stops[1].G), &(stops[1].B));
	stops[1].A = 1.0;
	radial.Stops = stops;
	radial.NumStops = 2;

	leftMountain = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(leftMountain, 346, 255);
	uiDrawPathLineTo(leftMountain, 267, 177);
	uiDrawPathLineTo(leftMountain, 236, 192);
	uiDrawPathLineTo(leftMountain, 212, 160);
	uiDrawPathLineTo(leftMountain, 156, 255);
	uiDrawPathLineTo(leftMountain, 346, 255);
	uiDrawPathCloseFigure(leftMountain);
	uiDrawPathEnd(leftMountain);

	rightMountain = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(rightMountain, 575, 263);
	uiDrawPathLineTo(rightMountain, 481, 146);
	uiDrawPathLineTo(rightMountain, 449, 181);
	uiDrawPathLineTo(rightMountain, 433, 159);
	uiDrawPathLineTo(rightMountain, 401, 214);
	uiDrawPathLineTo(rightMountain, 381, 199);
	uiDrawPathLineTo(rightMountain, 323, 263);
	uiDrawPathLineTo(rightMountain, 575, 263);
	uiDrawPathCloseFigure(rightMountain);
	uiDrawPathEnd(rightMountain);

	sun = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigureWithArc(sun,
		(440.0 - 270.0) / 2 + 270.0, 255,
		85,
		uiPi, uiPi,
		0);
	uiDrawPathCloseFigure(sun);
	uiDrawPathEnd(sun);

	// the original examples had these as hollow figures
	// we don't support them, so we'll have to stroke it separately
	sunRays = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(sunRays, 299, 182);
	uiDrawPathBezierTo(sunRays,
		299, 182,
		294, 176,
		285, 178);
	uiDrawPathBezierTo(sunRays,
		276, 179,
		272, 173,
		272, 173);
	uiDrawPathNewFigure(sunRays, 354, 156);
	uiDrawPathBezierTo(sunRays,
		354, 156,
		358, 149,
		354, 142);
	uiDrawPathBezierTo(sunRays,
		349, 134,
		354, 127,
		354, 127);
	uiDrawPathNewFigure(sunRays, 322, 164);
	uiDrawPathBezierTo(sunRays,
		322, 164,
		322, 156,
		314, 152);
	uiDrawPathBezierTo(sunRays,
		306, 149,
		305, 141,
		305, 141);
	uiDrawPathNewFigure(sunRays, 385, 164);
	uiDrawPathBezierTo(sunRays,
		385, 164,
		392, 161,
		394, 152);
	uiDrawPathBezierTo(sunRays,
		395, 144,
		402, 141,
		402, 142);
	uiDrawPathNewFigure(sunRays, 408, 182);
	uiDrawPathBezierTo(sunRays,
		408, 182,
		416, 184,
		422, 178);
	uiDrawPathBezierTo(sunRays,
		428, 171,
		435, 173,
		435, 173);
	uiDrawPathEnd(sunRays);

	river = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(river, 183, 392);
	uiDrawPathBezierTo(river,
		238, 284,
		472, 345,
		356, 303);
	uiDrawPathBezierTo(river,
		237, 261,
		333, 256,
		333, 256);
	uiDrawPathBezierTo(river,
		335, 257,
		241, 261,
		411, 306);
	uiDrawPathBezierTo(river,
		574, 350,
		288, 324,
		296, 392);
	uiDrawPathEnd(river);

	d2dClear(p, d2dWhite, 1.0);

	// TODO draw the grid

	uiDrawFill(p->Context, sun, &radial);

	d2dSolidBrush(&scene, d2dBlack, 1.0);
	sp.Thickness = 1.0;
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	uiDrawStroke(p->Context, sun, &scene, &sp);
	uiDrawStroke(p->Context, sunRays, &scene, &sp);

	d2dSolidBrush(&scene, d2dOliveDrab, 1.0);
	uiDrawFill(p->Context, leftMountain, &scene);

	d2dSolidBrush(&scene, d2dBlack, 1.0);
	uiDrawStroke(p->Context, leftMountain, &scene, &sp);

	d2dSolidBrush(&scene, d2dLightSkyBlue, 1.0);
	uiDrawFill(p->Context, river, &scene);

	d2dSolidBrush(&scene, d2dBlack, 1.0);
	uiDrawStroke(p->Context, river, &scene, &sp);

	d2dSolidBrush(&scene, d2dYellowGreen, 1.0);
	uiDrawFill(p->Context, rightMountain, &scene);

	d2dSolidBrush(&scene, d2dBlack, 1.0);
	uiDrawStroke(p->Context, rightMountain, &scene, &sp);

	uiDrawFreePath(leftMountain);
	uiDrawFreePath(rightMountain);
	uiDrawFreePath(sun);
	uiDrawFreePath(sunRays);
	uiDrawFreePath(river);
}