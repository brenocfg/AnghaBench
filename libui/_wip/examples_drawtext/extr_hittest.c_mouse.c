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
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
struct TYPE_5__ {int Down; scalar_t__ Y; scalar_t__ X; scalar_t__ AreaWidth; } ;
typedef  TYPE_1__ uiAreaMouseEvent ;
struct TYPE_6__ {scalar_t__ Width; } ;

/* Variables and functions */
 int /*<<< orphan*/  caretLabel ; 
 int caretLine ; 
 scalar_t__ caretPos ; 
 int margins ; 
 TYPE_2__ params ; 
 int /*<<< orphan*/  redraw () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  uiDrawFreeTextLayout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewTextLayout (TYPE_2__*) ; 
 int /*<<< orphan*/  uiDrawTextLayoutHitTest (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  uiLabelSetText (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mouse(uiAreaMouseEvent *e)
{
	uiDrawTextLayout *layout;
	char labelText[128];

	if (e->Down != 1)
		return;

	params.Width = e->AreaWidth - 2 * margins;
	layout = uiDrawNewTextLayout(&params);
	uiDrawTextLayoutHitTest(layout,
		e->X - margins, e->Y - margins,
		&caretPos, &caretLine);
	uiDrawFreeTextLayout(layout);

	// TODO move this into the draw handler so it is reflected by keyboard-based position changes
	// urgh %zd is not supported by MSVC with sprintf()
	// TODO get that part in test/ about having no other option
	sprintf(labelText, "pos %d line %d",
		(int) caretPos, caretLine);
	uiLabelSetText(caretLabel, labelText);

	redraw();
}