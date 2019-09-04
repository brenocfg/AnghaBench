#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiInitOptions ;
struct TYPE_9__ {int /*<<< orphan*/  panel; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  KeyEvent; int /*<<< orphan*/  DragBroken; int /*<<< orphan*/  MouseCrossed; int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  Draw; } ;

/* Variables and functions */
 int /*<<< orphan*/  area ; 
 int /*<<< orphan*/  box ; 
 int /*<<< orphan*/  exampleList ; 
 TYPE_2__** examples ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__ handler ; 
 int /*<<< orphan*/  handlerDragBroken ; 
 int /*<<< orphan*/  handlerDraw ; 
 int /*<<< orphan*/  handlerKeyEvent ; 
 int /*<<< orphan*/  handlerMouseCrossed ; 
 int /*<<< orphan*/  handlerMouseEvent ; 
 int /*<<< orphan*/  mainwin ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* mkAttributesExample () ; 
 TYPE_2__* mkBasicExample () ; 
 TYPE_2__* mkEmptyStringExample () ; 
 TYPE_2__* mkHitTestExample () ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  onExampleChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shouldQuit ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiComboboxAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiComboboxOnSelected (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiComboboxSetSelected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlHide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeInitError (char const*) ; 
 char* uiInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiMain () ; 
 int /*<<< orphan*/  uiNewArea (TYPE_1__*) ; 
 int /*<<< orphan*/  uiNewCombobox () ; 
 int /*<<< orphan*/  uiNewVerticalBox () ; 
 int /*<<< orphan*/  uiNewWindow (char*,int,int,int) ; 
 int /*<<< orphan*/  uiOnShouldQuit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiUninit () ; 
 int /*<<< orphan*/  uiWindowOnClosing (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowSetChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
	uiInitOptions o;
	const char *err;
	int n;

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

	mainwin = uiNewWindow("libui Text-Drawing Example", 640, 480, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);

	box = uiNewVerticalBox();
	uiWindowSetChild(mainwin, uiControl(box));

	exampleList = uiNewCombobox();
	uiBoxAppend(box, uiControl(exampleList), 0);

	area = uiNewArea(&handler);
	uiBoxAppend(box, uiControl(area), 1);

	n = 0;
	examples[n] = mkBasicExample();
	uiComboboxAppend(exampleList, examples[n]->name);
	uiControlHide(examples[n]->panel);
	uiBoxAppend(box, examples[n]->panel, 0);
	n++;
	examples[n] = mkHitTestExample();
	uiComboboxAppend(exampleList, examples[n]->name);
	uiControlHide(examples[n]->panel);
	uiBoxAppend(box, examples[n]->panel, 0);
	n++;
	examples[n] = mkAttributesExample();
	uiComboboxAppend(exampleList, examples[n]->name);
	uiControlHide(examples[n]->panel);
	uiBoxAppend(box, examples[n]->panel, 0);
	n++;
	examples[n] = mkEmptyStringExample();
	uiComboboxAppend(exampleList, examples[n]->name);
	uiControlHide(examples[n]->panel);
	uiBoxAppend(box, examples[n]->panel, 0);
	n++;
	// and set things up for the initial state
	uiComboboxSetSelected(exampleList, 0);
	uiComboboxOnSelected(exampleList, onExampleChanged, NULL);
	// and set up the first one
	onExampleChanged(NULL, NULL);

	uiControlShow(uiControl(mainwin));
	uiMain();

	// TODO free examples

	uiUninit();
	return 0;
}