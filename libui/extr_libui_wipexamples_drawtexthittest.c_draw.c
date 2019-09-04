#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int X; int Y; scalar_t__ Height; scalar_t__ Width; } ;
typedef  TYPE_1__ uiDrawTextLayoutLineMetrics ;
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_8__ {int /*<<< orphan*/  Context; scalar_t__ AreaWidth; scalar_t__ AreaHeight; } ;
typedef  TYPE_2__ uiAreaDrawParams ;
struct TYPE_9__ {scalar_t__ Width; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrstr ; 
 int caretLine ; 
 int /*<<< orphan*/  caretPos ; 
 scalar_t__ fillBrushes ; 
 int margins ; 
 TYPE_4__ params ; 
 int /*<<< orphan*/  showLineBounds ; 
 int /*<<< orphan*/  uiAttributedStringLen (int /*<<< orphan*/ ) ; 
 scalar_t__ uiCheckboxChecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawCaret (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  uiDrawClip (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFill (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawFillModeWinding ; 
 int /*<<< orphan*/  uiDrawFreePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFreeTextLayout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiDrawNewTextLayout (TYPE_4__*) ; 
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uiDrawPathEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawRestore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawSave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uiDrawTextLayoutLineGetMetrics (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int uiDrawTextLayoutNumLines (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void draw(uiAreaDrawParams *p)
{
	uiDrawPath *path;
	uiDrawTextLayout *layout;
	uiDrawTextLayoutLineMetrics m;

	// only clip the text, not the guides
	uiDrawSave(p->Context);

	path = uiDrawNewPath(uiDrawFillModeWinding);
	uiDrawPathAddRectangle(path, margins, margins,
		p->AreaWidth - 2 * margins,
		p->AreaHeight - 2 * margins);
	uiDrawPathEnd(path);
	uiDrawClip(p->Context, path);
	uiDrawFreePath(path);

	params.Width = p->AreaWidth - 2 * margins;
	layout = uiDrawNewTextLayout(&params);
	uiDrawText(p->Context, layout, margins, margins);

	uiDrawRestore(p->Context);

	if (caretLine == -1) {
		caretLine = uiDrawTextLayoutNumLines(layout) - 1;
		caretPos = uiAttributedStringLen(attrstr);
	}
	uiDrawCaret(p->Context, margins, margins,
		layout, caretPos, &caretLine);

	if (uiCheckboxChecked(showLineBounds)) {
		int i, n;
		int fill = 0;

		n = uiDrawTextLayoutNumLines(layout);
		for (i = 0; i < n; i++) {
			uiDrawTextLayoutLineGetMetrics(layout, i, &m);
			path = uiDrawNewPath(uiDrawFillModeWinding);
			uiDrawPathAddRectangle(path, margins + m.X, margins + m.Y,
				m.Width, m.Height);
			uiDrawPathEnd(path);
			uiDrawFill(p->Context, path, fillBrushes + fill);
			uiDrawFreePath(path);
			fill = (fill + 1) % 4;
		}
	}

	uiDrawFreeTextLayout(layout);
}