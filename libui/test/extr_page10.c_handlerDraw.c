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
typedef  int /*<<< orphan*/  uiDrawTextLayout ;
typedef  int /*<<< orphan*/  uiDrawTextFont ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
struct TYPE_3__ {int /*<<< orphan*/  Context; } ;
typedef  TYPE_1__ uiAreaDrawParams ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  noZ ; 
 int /*<<< orphan*/  textColorButton ; 
 int /*<<< orphan*/  textFontButton ; 
 int /*<<< orphan*/  uiCheckboxChecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiColorButtonColor (int /*<<< orphan*/ ,double*,double*,double*,double*) ; 
 int /*<<< orphan*/  uiDrawFreeTextFont (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawFreeTextLayout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiDrawNewTextLayout (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiDrawText (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawTextLayoutExtents (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  uiDrawTextLayoutSetColor (int /*<<< orphan*/ *,int,int,double,double,int,double) ; 
 int /*<<< orphan*/ * uiFontButtonFont (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handlerDraw(uiAreaHandler *a, uiArea *area, uiAreaDrawParams *dp)
{
	uiDrawTextFont *font;
	uiDrawTextLayout *layout;
	double r, g, b, al;
	char surrogates[1 + 4 + 1 + 1];
	char composed[2 + 2 + 2 + 3 + 2 + 1];
	double width, height;

	font = uiFontButtonFont(textFontButton);

	layout = uiDrawNewTextLayout("One two three four", font, -1);
	uiDrawTextLayoutSetColor(layout,
		4, 7,
		1, 0, 0, 1);
	uiDrawTextLayoutSetColor(layout,
		8, 14,
		1, 0, 0.5, 0.5);
	uiColorButtonColor(textColorButton, &r, &g, &b, &al);
	uiDrawTextLayoutSetColor(layout,
		14, 18,
		r, g, b, al);
	uiDrawText(dp->Context, 10, 10, layout);
	uiDrawTextLayoutExtents(layout, &width, &height);
	uiDrawFreeTextLayout(layout);

	surrogates[0] = 'x';
	surrogates[1] = 0xF0;		// surrogates D800 DF08
	surrogates[2] = 0x90;
	surrogates[3] = 0x8C;
	surrogates[4] = 0x88;
	surrogates[5] = 'y';
	surrogates[6] = '\0';

	layout = uiDrawNewTextLayout(surrogates, font, -1);
	uiDrawTextLayoutSetColor(layout,
		1, 2,
		1, 0, 0.5, 0.5);
	uiDrawText(dp->Context, 10, 10 + height, layout);
	uiDrawFreeTextLayout(layout);

	composed[0] = 'z';
	composed[1] = 'z';
	composed[2] = 0xC3;		// 2
	composed[3] = 0xA9;
	composed[4] = 'z';
	composed[5] = 'z';
	composed[6] = 0x65;		// 5
	composed[7] = 0xCC;
	composed[8] = 0x81;
	composed[9] = 'z';
	composed[10] = 'z';
	composed[11] = '\0';

	layout = uiDrawNewTextLayout(composed, font, -1);
	uiDrawTextLayoutSetColor(layout,
		2, 3,
		1, 0, 0.5, 0.5);
	uiDrawTextLayoutSetColor(layout,
		5, 6,
		1, 0, 0.5, 0.5);
	if (!uiCheckboxChecked(noZ))
		uiDrawTextLayoutSetColor(layout,
			6, 7,
			0.5, 0, 1, 0.5);
	uiDrawText(dp->Context, 10, 10 + height + height, layout);
	uiDrawFreeTextLayout(layout);

	uiDrawFreeTextFont(font);
}