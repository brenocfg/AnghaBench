#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double Leading; scalar_t__ Descent; scalar_t__ Ascent; } ;
typedef  TYPE_1__ uiDrawTextFontMetrics ;
struct TYPE_9__ {int Thickness; double R; double G; double B; double A; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Join; int /*<<< orphan*/  Cap; int /*<<< orphan*/  Type; } ;
typedef  TYPE_2__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawContext ;
typedef  TYPE_2__ uiDrawBrush ;

/* Variables and functions */
 int /*<<< orphan*/  addLeading ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uiCheckboxChecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 
 int /*<<< orphan*/  uiDrawClip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,int,double) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,int,double) ; 
 int /*<<< orphan*/  uiDrawRestore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawSave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void drawGuides(uiDrawContext *c, uiDrawTextFontMetrics *m)
{
	uiDrawPath *p;
	uiDrawBrush b;
	uiDrawStrokeParams sp;
	double leading;
	double y;

	leading = 0;
	if (uiCheckboxChecked(addLeading))
		leading = m->Leading;

	memset(&b, 0, sizeof (uiDrawBrush));
	b.Type = uiDrawBrushTypeSolid;
	memset(&sp, 0, sizeof (uiDrawStrokeParams));
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.MiterLimit = uiDrawDefaultMiterLimit;
	sp.Thickness = 2;

	uiDrawSave(c);

	p = uiDrawNewPath(uiDrawFillModeWinding);
	y = 10;
	uiDrawPathNewFigure(p, 8, y);
	y += m->Ascent;
	uiDrawPathLineTo(p, 8, y);
	uiDrawPathEnd(p);
	b.R = 0.94;
	b.G = 0.5;
	b.B = 0.5;
	b.A = 1.0;
	uiDrawStroke(c, p, &b, &sp);
	uiDrawFreePath(p);

	p = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(p, 8, y);
	y += m->Descent;
	uiDrawPathLineTo(p, 8, y);
	uiDrawPathEnd(p);
	b.R = 0.12;
	b.G = 0.56;
	b.B = 1.0;
	b.A = 1.0;
	uiDrawStroke(c, p, &b, &sp);
	uiDrawFreePath(p);

	// and again for the second line
	p = uiDrawNewPath(uiDrawFillModeWinding);
	y += leading;
	uiDrawPathNewFigure(p, 8, y);
	y += m->Ascent;
	uiDrawPathLineTo(p, 8, y);
	uiDrawPathEnd(p);
	b.R = 0.94;
	b.G = 0.5;
	b.B = 0.5;
	b.A = 0.75;
	uiDrawStroke(c, p, &b, &sp);
	uiDrawFreePath(p);

	p = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(p, 8, y);
	y += m->Descent;
	uiDrawPathLineTo(p, 8, y);
	uiDrawPathEnd(p);
	b.R = 0.12;
	b.G = 0.56;
	b.B = 1.0;
	b.A = 0.75;
	uiDrawStroke(c, p, &b, &sp);
	uiDrawFreePath(p);

	// and a box to text layout top-left corners
	p = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(p, 0, 0, 10, 10);
	uiDrawPathEnd(p);
	uiDrawClip(c, p);
	b.R = 0.85;
	b.G = 0.65;
	b.B = 0.13;
	b.A = 1.0;
	uiDrawStroke(c, p, &b, &sp);
	uiDrawFreePath(p);

	uiDrawRestore(c);
}