#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int Thickness; int /*<<< orphan*/  MiterLimit; int /*<<< orphan*/  Join; int /*<<< orphan*/  Cap; } ;
typedef  TYPE_1__ uiDrawStrokeParams ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawMatrix ;
struct TYPE_11__ {double R; double G; double B; double A; int /*<<< orphan*/  Type; } ;
typedef  TYPE_2__ uiDrawBrush ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
struct TYPE_12__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  AreaHeight; int /*<<< orphan*/  AreaWidth; } ;
typedef  TYPE_3__ uiAreaDrawParams ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  colorBlack ; 
 int /*<<< orphan*/  colorButton ; 
 int /*<<< orphan*/  colorWhite ; 
 int /*<<< orphan*/ * constructGraph (double,double,int) ; 
 int currentPoint ; 
 int /*<<< orphan*/  graphSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pointLocations (double,double,double*,double*) ; 
 int /*<<< orphan*/  pointRadius ; 
 int /*<<< orphan*/  setSolidBrush (TYPE_2__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  uiColorButtonColor (int /*<<< orphan*/ ,double*,double*,double*,double*) ; 
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 
 int /*<<< orphan*/  uiDrawDefaultMiterLimit ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawLineCapFlat ; 
 int /*<<< orphan*/  uiDrawLineJoinMiter ; 
 int /*<<< orphan*/  uiDrawMatrixSetIdentity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawMatrixTranslate (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawPathLineTo (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawPathNewFigure (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawPathNewFigureWithArc (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawStroke (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uiDrawTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ xoffLeft ; 
 scalar_t__ yoffTop ; 

__attribute__((used)) static void handlerDraw(uiAreaHandler *a, uiArea *area, uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawBrush brush;
	uiDrawStrokeParams sp;
	uiDrawMatrix m;
	double graphWidth, graphHeight;
	double graphR, graphG, graphB, graphA;

	// fill the area with white
	setSolidBrush(&brush, colorWhite, 1.0);
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, 0, 0, p->AreaWidth, p->AreaHeight);
	uiDrawPathEnd(path);
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);

	// figure out dimensions
	graphSize(p->AreaWidth, p->AreaHeight, &graphWidth, &graphHeight);

	// clear sp to avoid passing garbage to uiDrawStroke()
	// for example, we don't use dashing
	memset(&sp, 0, sizeof (uiDrawStrokeParams));

	// make a stroke for both the axes and the histogram line
	sp.Cap = uiDrawLineCapFlat;
	sp.Join = uiDrawLineJoinMiter;
	sp.Thickness = 2;
	sp.MiterLimit = uiDrawDefaultMiterLimit;

	// draw the axes
	setSolidBrush(&brush, colorBlack, 1.0);
	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathNewFigure(path,
		xoffLeft, yoffTop);
	uiDrawPathLineTo(path,
		xoffLeft, yoffTop + graphHeight);
	uiDrawPathLineTo(path,
		xoffLeft + graphWidth, yoffTop + graphHeight);
	uiDrawPathEnd(path);
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	// now transform the coordinate space so (0, 0) is the top-left corner of the graph
	uiDrawMatrixSetIdentity(&m);
	uiDrawMatrixTranslate(&m, xoffLeft, yoffTop);
	uiDrawTransform(p->Context, &m);

	// now get the color for the graph itself and set up the brush
	uiColorButtonColor(colorButton, &graphR, &graphG, &graphB, &graphA);
	brush.Type = uiDrawBrushTypeSolid;
	brush.R = graphR;
	brush.G = graphG;
	brush.B = graphB;
	// we set brush->A below to different values for the fill and stroke

	// now create the fill for the graph below the graph line
	path = constructGraph(graphWidth, graphHeight, 1);
	brush.A = graphA / 2;
	uiDrawFill(p->Context, path, &brush);
	uiDrawFreePath(path);

	// now draw the histogram line
	path = constructGraph(graphWidth, graphHeight, 0);
	brush.A = graphA;
	uiDrawStroke(p->Context, path, &brush, &sp);
	uiDrawFreePath(path);

	// now draw the point being hovered over
	if (currentPoint != -1) {
		double xs[10], ys[10];

		pointLocations(graphWidth, graphHeight, xs, ys);
		path = uiDrawNewPath(uiDrawFillModeWinding);
		uiDrawPathNewFigureWithArc(path,
			xs[currentPoint], ys[currentPoint],
			pointRadius,
			0, 6.23,		// TODO pi
			0);
		uiDrawPathEnd(path);
		// use the same brush as for the histogram lines
		uiDrawFill(p->Context, path, &brush);
		uiDrawFreePath(path);
	}
}