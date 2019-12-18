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
struct example {char* name; int /*<<< orphan*/ * key; int /*<<< orphan*/ * mouse; int /*<<< orphan*/  draw; int /*<<< orphan*/  panel; } ;
struct TYPE_2__ {int /*<<< orphan*/  Align; int /*<<< orphan*/ * DefaultFont; int /*<<< orphan*/  String; } ;

/* Variables and functions */
 struct example attributesExample ; 
 int /*<<< orphan*/  attrstr ; 
 int /*<<< orphan*/  changeFont ; 
 int /*<<< orphan*/  defaultFont ; 
 int /*<<< orphan*/  draw ; 
 int /*<<< orphan*/  fontButton ; 
 int /*<<< orphan*/  newCheckbox (char*) ; 
 int /*<<< orphan*/  panel ; 
 TYPE_1__ params ; 
 int /*<<< orphan*/  setupAttributedString () ; 
 int /*<<< orphan*/  showLineBounds ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiDrawTextAlignLeft ; 
 int /*<<< orphan*/  uiFontButtonOnChanged (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiNewFontButton () ; 
 int /*<<< orphan*/  uiNewVerticalBox () ; 

struct example *mkAttributesExample(void)
{
	panel = uiNewVerticalBox();
	showLineBounds = newCheckbox("Show Line Bounds");
	fontButton = uiNewFontButton();
	uiFontButtonOnChanged(fontButton, changeFont, NULL);
	// TODO set the font button to the current defaultFont
	uiBoxAppend(panel, uiControl(fontButton), 0);

	attributesExample.name = "Attributed Text";
	attributesExample.panel = uiControl(panel);
	attributesExample.draw = draw;
	attributesExample.mouse = NULL;
	attributesExample.key = NULL;

	setupAttributedString();
	params.String = attrstr;
	params.DefaultFont = &defaultFont;
	params.Align = uiDrawTextAlignLeft;

	return &attributesExample;
}