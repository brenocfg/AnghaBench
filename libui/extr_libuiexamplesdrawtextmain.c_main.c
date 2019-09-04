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
typedef  int /*<<< orphan*/  uiInitOptions ;
typedef  int /*<<< orphan*/  uiForm ;
typedef  int /*<<< orphan*/  uiBox ;
struct TYPE_3__ {int /*<<< orphan*/  KeyEvent; int /*<<< orphan*/  DragBroken; int /*<<< orphan*/  MouseCrossed; int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  Draw; } ;

/* Variables and functions */
 int /*<<< orphan*/ * alignment ; 
 int /*<<< orphan*/ * area ; 
 int /*<<< orphan*/  attrstr ; 
 int /*<<< orphan*/ * fontButton ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ handler ; 
 int /*<<< orphan*/  handlerDragBroken ; 
 int /*<<< orphan*/  handlerDraw ; 
 int /*<<< orphan*/  handlerKeyEvent ; 
 int /*<<< orphan*/  handlerMouseCrossed ; 
 int /*<<< orphan*/  handlerMouseEvent ; 
 int /*<<< orphan*/ * mainwin ; 
 int /*<<< orphan*/  makeAttributedString () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  onComboboxSelected ; 
 int /*<<< orphan*/  onFontChanged ; 
 int /*<<< orphan*/  shouldQuit ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiBoxSetPadded (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiComboboxAppend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiComboboxOnSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiComboboxSetSelected (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFontButtonOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFormAppend (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFormSetPadded (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiFreeAttributedString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeInitError (char const*) ; 
 char* uiInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiMain () ; 
 int /*<<< orphan*/ * uiNewArea (TYPE_1__*) ; 
 int /*<<< orphan*/ * uiNewCombobox () ; 
 int /*<<< orphan*/ * uiNewFontButton () ; 
 int /*<<< orphan*/ * uiNewForm () ; 
 int /*<<< orphan*/ * uiNewHorizontalBox () ; 
 int /*<<< orphan*/ * uiNewVerticalBox () ; 
 int /*<<< orphan*/ * uiNewWindow (char*,int,int,int) ; 
 int /*<<< orphan*/  uiOnShouldQuit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiUninit () ; 
 int /*<<< orphan*/  uiWindowOnClosing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetMargined (int /*<<< orphan*/ *,int) ; 

int main(void)
{
	uiInitOptions o;
	const char *err;
	uiBox *hbox, *vbox;
	uiForm *form;

	handler.Draw = handlerDraw;
	handler.MouseEvent = handlerMouseEvent;
	handler.MouseCrossed = handlerMouseCrossed;
	handler.DragBroken = handlerDragBroken;
	handler.KeyEvent = handlerKeyEvent;

	memset(&o, 0, sizeof (uiInitOptions));
	err = uiInit(&o);
	if (err != NULL) {
		fprintf(stderr, "error initializing ui: %s\n", err);
		uiFreeInitError(err);
		return 1;
	}

	uiOnShouldQuit(shouldQuit, NULL);

	makeAttributedString();

	mainwin = uiNewWindow("libui Text-Drawing Example", 640, 480, 1);
	uiWindowSetMargined(mainwin, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);

	hbox = uiNewHorizontalBox();
	uiBoxSetPadded(hbox, 1);
	uiWindowSetChild(mainwin, uiControl(hbox));

	vbox = uiNewVerticalBox();
	uiBoxSetPadded(vbox, 1);
	uiBoxAppend(hbox, uiControl(vbox), 0);

	fontButton = uiNewFontButton();
	uiFontButtonOnChanged(fontButton, onFontChanged, NULL);
	uiBoxAppend(vbox, uiControl(fontButton), 0);

	form = uiNewForm();
	uiFormSetPadded(form, 1);
	// TODO on OS X if this is set to 1 then the window can't resize; does the form not have the concept of stretchy trailing space?
	uiBoxAppend(vbox, uiControl(form), 0);

	alignment = uiNewCombobox();
	// note that the items match with the values of the uiDrawTextAlign values
	uiComboboxAppend(alignment, "Left");
	uiComboboxAppend(alignment, "Center");
	uiComboboxAppend(alignment, "Right");
	uiComboboxSetSelected(alignment, 0);		// start with left alignment
	uiComboboxOnSelected(alignment, onComboboxSelected, NULL);
	uiFormAppend(form, "Alignment", uiControl(alignment), 0);

	area = uiNewArea(&handler);
	uiBoxAppend(hbox, uiControl(area), 1);

	uiControlShow(uiControl(mainwin));
	uiMain();
	uiFreeAttributedString(attrstr);
	uiUninit();
	return 0;
}