#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Height; scalar_t__ Y; } ;
typedef  TYPE_1__ uiDrawTextLayoutLineMetrics ;
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
typedef  int /*<<< orphan*/  uiDrawPath ;
typedef  int /*<<< orphan*/  uiDrawContext ;
typedef  int /*<<< orphan*/  uiDrawBrush ;

/* Variables and functions */
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,double,scalar_t__,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 double uiDrawTextLayoutByteLocationInLine (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  uiDrawTextLayoutExtents (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  uiDrawTextLayoutLineByteRange (int /*<<< orphan*/ *,int,size_t*,size_t*) ; 
 int /*<<< orphan*/  uiDrawTextLayoutLineGetMetrics (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int uiDrawTextLayoutNumLines (int /*<<< orphan*/ *) ; 

void drawTextBackground(uiDrawContext *c, double x, double y, uiDrawTextLayout *layout, size_t start, size_t end, uiDrawBrush *brush, int isSelection)
{
	int line, nLines;
	size_t lstart, lend;
	double layoutwid, layoutht;

	uiDrawTextLayoutExtents(layout, &layoutwid, &layoutht);
	nLines = uiDrawTextLayoutNumLines(layout);
	for (line = 0; line < nLines; line++) {
		uiDrawTextLayoutLineByteRange(layout, line, &lstart, &lend);
		if (start >= lstart && start < lend)
			break;
	}
	while (end - start > 0) {
		uiDrawTextLayoutLineMetrics m;
		double startx, endx;
		uiDrawPath *path;

		uiDrawTextLayoutLineByteRange(layout, line, &lstart, &lend);
		if (lend > end)		// don't cross lines
			lend = end;
		startx = uiDrawTextLayoutByteLocationInLine(layout, start, line);
		// TODO explain this; note the use of start with lend
		endx = layoutwid;
		if (!isSelection || end <= lend)
			endx = uiDrawTextLayoutByteLocationInLine(layout, lend, line);
		uiDrawTextLayoutLineGetMetrics(layout, line, &m);
		path = uiDrawNewPath(uiDrawFillModeWinding);
		uiDrawPathAddRectangle(path,
			x + startx, y + m.Y,
			endx - startx, m.Height);
		uiDrawPathEnd(path);
		uiDrawFill(c, path, brush);
		uiDrawFreePath(path);
		line++;
		start = lend;
	}
}