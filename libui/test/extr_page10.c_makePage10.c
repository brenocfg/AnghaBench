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
typedef  int /*<<< orphan*/  uiBox ;
struct TYPE_3__ {int /*<<< orphan*/  KeyEvent; int /*<<< orphan*/  DragBroken; int /*<<< orphan*/  MouseCrossed; int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  Draw; } ;

/* Variables and functions */
 int /*<<< orphan*/  handlerDragBroken ; 
 int /*<<< orphan*/  handlerDraw ; 
 int /*<<< orphan*/  handlerKeyEvent ; 
 int /*<<< orphan*/  handlerMouseCrossed ; 
 int /*<<< orphan*/  handlerMouseEvent ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/ * noZ ; 
 int /*<<< orphan*/  onColorChanged ; 
 int /*<<< orphan*/  onFontChanged ; 
 int /*<<< orphan*/  onNoZ ; 
 int /*<<< orphan*/ * textApply ; 
 int /*<<< orphan*/ * textArea ; 
 TYPE_1__ textAreaHandler ; 
 int /*<<< orphan*/ * textColorButton ; 
 int /*<<< orphan*/ * textFontButton ; 
 int /*<<< orphan*/ * textString ; 
 int /*<<< orphan*/ * textWidth ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiCheckboxOnToggled (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiColorButtonOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiEntrySetText (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiFontButtonOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewArea (TYPE_1__*) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewCheckbox (char*) ; 
 int /*<<< orphan*/ * uiNewColorButton () ; 
 int /*<<< orphan*/ * uiNewEntry () ; 
 int /*<<< orphan*/ * uiNewFontButton () ; 

uiBox *makePage10(void)
{
	uiBox *page10;
	uiBox *vbox;
	uiBox *hbox;

	page10 = newVerticalBox();
	vbox = page10;

	hbox = newHorizontalBox();
	uiBoxAppend(vbox, uiControl(hbox), 0);

	textString = uiNewEntry();
	// TODO make it placeholder
	uiEntrySetText(textString, "Enter text here");
	uiBoxAppend(hbox, uiControl(textString), 1);

	textFontButton = uiNewFontButton();
	uiFontButtonOnChanged(textFontButton, onFontChanged, NULL);
	uiBoxAppend(hbox, uiControl(textFontButton), 1);

	textColorButton = uiNewColorButton();
	uiColorButtonOnChanged(textColorButton, onColorChanged, NULL);
	uiBoxAppend(hbox, uiControl(textColorButton), 1);

	hbox = newHorizontalBox();
	uiBoxAppend(vbox, uiControl(hbox), 0);

	textApply = uiNewButton("Apply");
	uiBoxAppend(hbox, uiControl(textApply), 1);

	textWidth = uiNewEntry();
	uiEntrySetText(textWidth, "-1");
	uiBoxAppend(hbox, uiControl(textWidth), 1);

	noZ = uiNewCheckbox("No Z Color");
	uiCheckboxOnToggled(noZ, onNoZ, NULL);
	uiBoxAppend(hbox, uiControl(noZ), 0);

	textAreaHandler.Draw = handlerDraw;
	textAreaHandler.MouseEvent = handlerMouseEvent;
	textAreaHandler.MouseCrossed = handlerMouseCrossed;
	textAreaHandler.DragBroken = handlerDragBroken;
	textAreaHandler.KeyEvent = handlerKeyEvent;
	textArea = uiNewArea(&textAreaHandler);
	uiBoxAppend(vbox, uiControl(textArea), 1);

	// dummy objects to test single-activation
	hbox = newHorizontalBox();
	uiBoxAppend(vbox, uiControl(hbox), 0);
	uiBoxAppend(hbox, uiControl(uiNewFontButton()), 1);
	uiBoxAppend(hbox, uiControl(uiNewColorButton()), 1);

	return page10;
}