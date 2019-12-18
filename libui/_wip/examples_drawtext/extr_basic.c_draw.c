#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int X; int Y; double Width; double Height; scalar_t__ Descent; scalar_t__ BaselineY; scalar_t__ Ascent; } ;
typedef  TYPE_1__ uiDrawTextLayoutLineMetrics ;
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_13__ {double R; double G; double B; double A; int /*<<< orphan*/  Type; } ;
typedef  TYPE_2__ uiDrawBrush ;
struct TYPE_14__ {int AreaWidth; int AreaHeight; int /*<<< orphan*/  Context; } ;
typedef  TYPE_3__ uiAreaDrawParams ;
struct TYPE_15__ {int Width; } ;

/* Variables and functions */
 TYPE_2__* fillBrushes ; 
 int margins ; 
 TYPE_6__ params ; 
 int /*<<< orphan*/  showExtents ; 
 int /*<<< orphan*/  showLineBounds ; 
 int /*<<< orphan*/  showLineGuides ; 
 TYPE_2__* strokeBrushes ; 
 int /*<<< orphan*/  strokeParams ; 
 scalar_t__ uiCheckboxChecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 
 int /*<<< orphan*/  uiDrawClip (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFreeTextLayout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiDrawNewTextLayout (TYPE_6__*) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,int,int,double,double) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawRestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawTextLayoutExtents (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  uiDrawTextLayoutLineGetMetrics (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int uiDrawTextLayoutNumLines (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void draw(uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawTextLayout *layout;
	uiDrawBrush b;

	b.Type = uiDrawBrushTypeSolid;

	// only clip the text, not the guides
	uiDrawSave(p->Context);

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, margins, margins,
		p->AreaWidth - 2 * margins,
		p->AreaHeight - 2 * margins);
	uiDrawPathEnd(path);
	uiDrawClip(p->Context, path);
	uiDrawFreePath(path);

	// TODO get rid of this later
#if 0
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, -100, -100,
		p->AreaWidth * 2,
		p->AreaHeight * 2);
	uiDrawPathEnd(path);
	b.R = 0.0;
	b.G = 1.0;
	b.B = 0.0;
	b.A = 1.0;
	uiDrawFill(p->Context, path, &b);
	uiDrawFreePath(path);
#endif

	params.Width = p->AreaWidth - 2 * margins;
	layout = uiDrawNewTextLayout(&params);
	uiDrawText(p->Context, layout, margins, margins);

	uiDrawRestore(p->Context);

	if (uiCheckboxChecked(showExtents)) {
		double width, height;

		uiDrawTextLayoutExtents(layout, &width, &height);
		path = uiDrawNewPath(uiDrawFillModeWinding);
		uiDrawPathAddRectangle(path, margins, margins,
			width, height);
		uiDrawPathEnd(path);
		b.R = 1.0;
		b.G = 0.0;
		b.B = 1.0;
		b.A = 0.5;
		uiDrawStroke(p->Context, path, &b, &strokeParams);
		uiDrawFreePath(path);
	}

	if (uiCheckboxChecked(showLineBounds) || uiCheckboxChecked(showLineGuides)) {
		uiDrawTextLayoutLineMetrics m;
		int i, n;
		int fill = 0;

		n = uiDrawTextLayoutNumLines(layout);
		for (i = 0; i < n; i++) {
			uiDrawTextLayoutLineGetMetrics(layout, i, &m);

			if (uiCheckboxChecked(showLineBounds)) {
				path = uiDrawNewPath(uiDrawFillModeWinding);
				uiDrawPathAddRectangle(path, margins + m.X, margins + m.Y,
					m.Width, m.Height);
				uiDrawPathEnd(path);
				uiDrawFill(p->Context, path, fillBrushes + fill);
				uiDrawFreePath(path);
				fill = (fill + 1) % 4;
			}
			if (uiCheckboxChecked(showLineGuides)) {
				// baseline
				path = uiDrawNewPath(uiDrawFillModeWinding);
				uiDrawPathNewFigure(path,
					margins + m.X,
					margins + m.BaselineY);
				uiDrawPathLineTo(path,
					margins + m.X + m.Width,
					margins + m.BaselineY);
				uiDrawPathEnd(path);
				uiDrawStroke(p->Context, path, &(strokeBrushes[0]), &strokeParams);
				uiDrawFreePath(path);

				// ascent line
				path = uiDrawNewPath(uiDrawFillModeWinding);
				uiDrawPathNewFigure(path,
					margins + m.X,
					margins + m.BaselineY - m.Ascent);
				uiDrawPathLineTo(path,
					margins + m.X + m.Width,
					margins + m.BaselineY - m.Ascent);
				uiDrawPathEnd(path);
				uiDrawStroke(p->Context, path, &(strokeBrushes[1]), &strokeParams);
				uiDrawFreePath(path);

				// descent line
				path = uiDrawNewPath(uiDrawFillModeWinding);
				uiDrawPathNewFigure(path,
					margins + m.X,
					margins + m.BaselineY + m.Descent);
				uiDrawPathLineTo(path,
					margins + m.X + m.Width,
					margins + m.BaselineY + m.Descent);
				uiDrawPathEnd(path);
				uiDrawStroke(p->Context, path, &(strokeBrushes[2]), &strokeParams);
				uiDrawFreePath(path);
			}
		}
	}

	uiDrawFreeTextLayout(layout);
}