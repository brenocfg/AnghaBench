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
typedef  int /*<<< orphan*/  uiFontDescriptor ;
struct TYPE_5__ {scalar_t__ Align; int /*<<< orphan*/  Width; int /*<<< orphan*/ * DefaultFont; int /*<<< orphan*/  String; } ;
typedef  TYPE_1__ uiDrawTextLayoutParams ;
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
typedef  scalar_t__ uiDrawTextAlign ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
struct TYPE_6__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  AreaWidth; } ;
typedef  TYPE_2__ uiAreaDrawParams ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  alignment ; 
 int /*<<< orphan*/  attrstr ; 
 int /*<<< orphan*/  fontButton ; 
 scalar_t__ uiComboboxSelected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawFreeTextLayout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewTextLayout (TYPE_1__*) ; 
 int /*<<< orphan*/  uiDrawText (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFontButtonFont (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeFontButtonFont (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handlerDraw(uiAreaHandler *a, uiArea *area, uiAreaDrawParams *p)
{
	uiDrawTextLayout *textLayout;
	uiFontDescriptor defaultFont;
	uiDrawTextLayoutParams params;

	params.String = attrstr;
	uiFontButtonFont(fontButton, &defaultFont);
	params.DefaultFont = &defaultFont;
	params.Width = p->AreaWidth;
	params.Align = (uiDrawTextAlign) uiComboboxSelected(alignment);
	textLayout = uiDrawNewTextLayout(&params);
	uiDrawText(p->Context, textLayout, 0, 0);
	uiDrawFreeTextLayout(textLayout);
	uiFreeFontButtonFont(&defaultFont);
}