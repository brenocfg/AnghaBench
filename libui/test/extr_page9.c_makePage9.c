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
 int /*<<< orphan*/ * addLeading ; 
 int /*<<< orphan*/  handlerDragBroken ; 
 int /*<<< orphan*/  handlerDraw ; 
 int /*<<< orphan*/  handlerKeyEvent ; 
 int /*<<< orphan*/  handlerMouseCrossed ; 
 int /*<<< orphan*/  handlerMouseEvent ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  onTextApply ; 
 int /*<<< orphan*/ * textApply ; 
 int /*<<< orphan*/ * textArea ; 
 TYPE_1__ textAreaHandler ; 
 int /*<<< orphan*/ * textFont ; 
 int /*<<< orphan*/ * textItalic ; 
 int /*<<< orphan*/ * textSize ; 
 int /*<<< orphan*/ * textSmallCaps ; 
 int /*<<< orphan*/ * textStretch ; 
 int /*<<< orphan*/ * textString ; 
 int /*<<< orphan*/ * textWeight ; 
 int /*<<< orphan*/ * textWidth ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiCheckboxSetChecked (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiComboboxAppend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiComboboxSetSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawTextItalicNormal ; 
 int /*<<< orphan*/  uiDrawTextStretchNormal ; 
 int /*<<< orphan*/  uiDrawTextWeightNormal ; 
 int /*<<< orphan*/  uiEntrySetText (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * uiNewArea (TYPE_1__*) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewCheckbox (char*) ; 
 int /*<<< orphan*/ * uiNewCombobox () ; 
 int /*<<< orphan*/ * uiNewEntry () ; 

uiBox *makePage9(void)
{
	uiBox *page9;
	uiBox *vbox;
	uiBox *hbox;

	page9 = newVerticalBox();
	vbox = page9;

	hbox = newHorizontalBox();
	uiBoxAppend(vbox, uiControl(hbox), 0);

	textString = uiNewEntry();
	// TODO make it placeholder
	uiEntrySetText(textString, "Enter text here");
	uiBoxAppend(hbox, uiControl(textString), 1);

	textFont = uiNewEntry();
	uiEntrySetText(textFont, "Arial");
	uiBoxAppend(hbox, uiControl(textFont), 1);

	textSize = uiNewEntry();
	uiEntrySetText(textSize, "10");
	uiBoxAppend(hbox, uiControl(textSize), 1);

	hbox = newHorizontalBox();
	uiBoxAppend(vbox, uiControl(hbox), 0);

	textWeight = uiNewCombobox();
	uiComboboxAppend(textWeight, "Thin");
	uiComboboxAppend(textWeight, "Ultra Light");
	uiComboboxAppend(textWeight, "Light");
	uiComboboxAppend(textWeight, "Book");
	uiComboboxAppend(textWeight, "Normal");
	uiComboboxAppend(textWeight, "Medium");
	uiComboboxAppend(textWeight, "Semi Bold");
	uiComboboxAppend(textWeight, "Bold");
	uiComboboxAppend(textWeight, "Ultra Bold");
	uiComboboxAppend(textWeight, "Heavy");
	uiComboboxAppend(textWeight, "Ultra Heavy");
	uiComboboxSetSelected(textWeight, uiDrawTextWeightNormal);
	uiBoxAppend(hbox, uiControl(textWeight), 1);

	textItalic = uiNewCombobox();
	uiComboboxAppend(textItalic, "Normal");
	uiComboboxAppend(textItalic, "Oblique");
	uiComboboxAppend(textItalic, "Italic");
	uiComboboxSetSelected(textItalic, uiDrawTextItalicNormal);
	uiBoxAppend(hbox, uiControl(textItalic), 1);

	textSmallCaps = uiNewCheckbox("Small Caps");
	uiBoxAppend(hbox, uiControl(textSmallCaps), 1);

	hbox = newHorizontalBox();
	uiBoxAppend(vbox, uiControl(hbox), 0);

	textStretch = uiNewCombobox();
	uiComboboxAppend(textStretch, "Ultra Condensed");
	uiComboboxAppend(textStretch, "Extra Condensed");
	uiComboboxAppend(textStretch, "Condensed");
	uiComboboxAppend(textStretch, "Semi Condensed");
	uiComboboxAppend(textStretch, "Normal");
	uiComboboxAppend(textStretch, "Semi Expanded");
	uiComboboxAppend(textStretch, "Expanded");
	uiComboboxAppend(textStretch, "Extra Expanded");
	uiComboboxAppend(textStretch, "Ultra Expanded");
	uiComboboxSetSelected(textStretch, uiDrawTextStretchNormal);
	uiBoxAppend(hbox, uiControl(textStretch), 1);

	textWidth = uiNewEntry();
	uiEntrySetText(textWidth, "-1");
	uiBoxAppend(hbox, uiControl(textWidth), 1);

	hbox = newHorizontalBox();
	uiBoxAppend(vbox, uiControl(hbox), 0);

	textApply = uiNewButton("Apply");
	uiButtonOnClicked(textApply, onTextApply, NULL);
	uiBoxAppend(hbox, uiControl(textApply), 1);

	addLeading = uiNewCheckbox("Add Leading");
	uiCheckboxSetChecked(addLeading, 1);
	uiBoxAppend(hbox, uiControl(addLeading), 0);

	textAreaHandler.Draw = handlerDraw;
	textAreaHandler.MouseEvent = handlerMouseEvent;
	textAreaHandler.MouseCrossed = handlerMouseCrossed;
	textAreaHandler.DragBroken = handlerDragBroken;
	textAreaHandler.KeyEvent = handlerKeyEvent;
	textArea = uiNewArea(&textAreaHandler);
	uiBoxAppend(vbox, uiControl(textArea), 1);

	return page9;
}