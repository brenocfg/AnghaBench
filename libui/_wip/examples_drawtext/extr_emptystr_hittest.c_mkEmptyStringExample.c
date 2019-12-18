#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct example {char* name; int /*<<< orphan*/  key; int /*<<< orphan*/  mouse; int /*<<< orphan*/  draw; int /*<<< orphan*/  panel; } ;
struct TYPE_2__ {int /*<<< orphan*/  Align; int /*<<< orphan*/ * DefaultFont; int /*<<< orphan*/  String; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrstr ; 
 int /*<<< orphan*/  caretLabel ; 
 int /*<<< orphan*/  changeFont ; 
 int /*<<< orphan*/  changeTextAlign ; 
 int /*<<< orphan*/  defaultFont ; 
 int /*<<< orphan*/  draw ; 
 int /*<<< orphan*/  fontButton ; 
 struct example hitTestExample ; 
 int /*<<< orphan*/  key ; 
 int /*<<< orphan*/  mouse ; 
 int /*<<< orphan*/  newCheckbox (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panel ; 
 TYPE_1__ params ; 
 int /*<<< orphan*/  showLineBounds ; 
 int /*<<< orphan*/  text ; 
 int /*<<< orphan*/  textAlign ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiComboboxAppend (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiComboboxOnSelected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawTextAlignLeft ; 
 int /*<<< orphan*/  uiFontButtonOnChanged (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiNewAttributedString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiNewCombobox () ; 
 int /*<<< orphan*/  uiNewFontButton () ; 
 int /*<<< orphan*/  uiNewHorizontalBox () ; 
 int /*<<< orphan*/  uiNewLabel (char*) ; 
 int /*<<< orphan*/  uiNewVerticalBox () ; 
 int /*<<< orphan*/  vbox ; 

struct example *mkEmptyStringExample(void)
{
	panel = uiNewHorizontalBox();
	vbox = uiNewVerticalBox();
	// TODO the second vbox causes this not to stretch at least on OS X
	uiBoxAppend(panel, uiControl(vbox), 1);
	caretLabel = uiNewLabel("Caret information is shown here");
	uiBoxAppend(vbox, uiControl(caretLabel), 0);
	showLineBounds = newCheckbox(vbox, "Show Line Bounds (for debugging metrics)");
	vbox = uiNewVerticalBox();
	uiBoxAppend(panel, uiControl(vbox), 0);
	fontButton = uiNewFontButton();
	uiFontButtonOnChanged(fontButton, changeFont, NULL);
	// TODO set the font button to the current defaultFont
	uiBoxAppend(vbox, uiControl(fontButton), 0);
	textAlign = uiNewCombobox();
	// note that these are in the order in the enum
	uiComboboxAppend(textAlign, "Left");
	uiComboboxAppend(textAlign, "Center");
	uiComboboxAppend(textAlign, "Right");
	uiComboboxOnSelected(textAlign, changeTextAlign, NULL);
	uiBoxAppend(vbox, uiControl(textAlign), 0);

	hitTestExample.name = "Empty String";
	hitTestExample.panel = uiControl(panel);
	hitTestExample.draw = draw;
	hitTestExample.mouse = mouse;
	hitTestExample.key = key;

	attrstr = uiNewAttributedString(text);
	params.String = attrstr;
	params.DefaultFont = &defaultFont;
	params.Align = uiDrawTextAlignLeft;

	return &hitTestExample;
}