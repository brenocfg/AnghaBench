#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int Thickness; void* MiterLimit; void* Join; void* Cap; scalar_t__ DashPhase; scalar_t__ NumDashes; int /*<<< orphan*/ * Dashes; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_9__ {int A; int R; double G; double B; int /*<<< orphan*/  Type; } ;
typedef  TYPE_2__ uiDrawBrush ;
struct TYPE_10__ {int ClipX; int ClipY; int ClipWidth; int ClipHeight; int /*<<< orphan*/  Context; } ;
typedef  TYPE_3__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 
 void* uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 void* uiDrawLineCapFlat ; 
 void* uiDrawLineJoinMiter ; 
 void* uiDrawLineJoinRound ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  uiDrawPathArcTo (int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathBezierTo (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  uiDrawPathCloseFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawPathNewFigureWithArc (int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int uiPi ; 

__attribute__((used)) static void drawOriginal(uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawBrush brush;
	uiDrawStrokeParams sp;

	sp.Dashes = NULL;
	sp.NumDashes = 0;
	sp.DashPhase = 0;

	brush.Type = uiDrawBrushTypeSolid;
	brush.A = 1;

	brush.R = 1;
	brush.G = 0;
	brush.B = 0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, p->ClipX + 5, p->ClipY + 5);
	uiDrawPathLineTo(path, (p->ClipX + p->ClipWidth) - 5, (p->ClipY + p->ClipHeight) - 5);
	uiDrawPathEnd(path);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.Thickness = 1;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	brush.R = 0;
	brush.G = 0;
	brush.B = 0.75;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, p->ClipX, p->ClipY);
	uiDrawPathLineTo(path, p->ClipX + p->ClipWidth, p->ClipY);
	uiDrawPathLineTo(path, 50, 150);
	uiDrawPathLineTo(path, 50, 50);
	uiDrawPathCloseFigure(path);
	uiDrawPathEnd(path);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinRound;
	sp.Thickness = 5;
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	brush.R = 0;
	brush.G = 0.75;
	brush.B = 0;
	brush.A = 0.5;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, 120, 80, 50, 50);
	uiDrawPathEnd(path);
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);
	brush.A = 1;

	brush.R = 0;
	brush.G = 0.5;
	brush.B = 0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, 5.5, 10.5);
	uiDrawPathLineTo(path, 5.5, 50.5);
	uiDrawPathEnd(path);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.Thickness = 1;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	brush.R = 0.5;
	brush.G = 0.75;
	brush.B = 0;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, 400, 100);
	uiDrawPathArcTo(path,
		400, 100,
		50,
		30. * (uiPi / 180.),
		300. * (uiPi / 180.),
		0);
	// the sweep test below doubles as a clockwise test so a checkbox isn't needed anymore
	uiDrawPathLineTo(path, 400, 100);
	uiDrawPathNewFigureWithArc(path,
		510, 100,
		50,
		30. * (uiPi / 180.),
		300. * (uiPi / 180.),
		0);
	uiDrawPathCloseFigure(path);
	// and now with 330 to make sure sweeps work properly
	uiDrawPathNewFigure(path, 400, 210);
	uiDrawPathArcTo(path,
		400, 210,
		50,
		30. * (uiPi / 180.),
		330. * (uiPi / 180.),
		0);
	uiDrawPathLineTo(path, 400, 210);
	uiDrawPathNewFigureWithArc(path,
		510, 210,
		50,
		30. * (uiPi / 180.),
		330. * (uiPi / 180.),
		0);
	uiDrawPathCloseFigure(path);
	uiDrawPathEnd(path);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.Thickness = 1;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	brush.R = 0;
	brush.G = 0.5;
	brush.B = 0.75;
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path, 300, 300);
	uiDrawPathBezierTo(path,
		350, 320,
		310, 390,
		435, 372);
	uiDrawPathEnd(path);
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.Thickness = 1;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);
}