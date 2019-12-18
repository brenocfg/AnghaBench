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
typedef  int /*<<< orphan*/  uiGrid ;
typedef  int /*<<< orphan*/  uiBox ;
struct TYPE_3__ {int /*<<< orphan*/  KeyEvent; int /*<<< orphan*/  DragBroken; int /*<<< orphan*/  MouseCrossed; int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  Draw; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nullFeatures ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  onFontChanged ; 
 int /*<<< orphan*/  onNULLToggled ; 
 int /*<<< orphan*/  onTextChanged ; 
 int /*<<< orphan*/  remakeAttrStr () ; 
 int /*<<< orphan*/  shouldQuit ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * textEntry ; 
 int /*<<< orphan*/  uiAlignCenter ; 
 int /*<<< orphan*/  uiAlignFill ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiBoxSetPadded (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiCheckboxOnToggled (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiEntryOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiEntrySetText (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uiFontButtonOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiFreeAttributedString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeInitError (char const*) ; 
 int /*<<< orphan*/  uiGridAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiGridSetPadded (int /*<<< orphan*/ *,int) ; 
 char* uiInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiMain () ; 
 int /*<<< orphan*/ * uiNewArea (TYPE_1__*) ; 
 int /*<<< orphan*/ * uiNewCheckbox (char*) ; 
 int /*<<< orphan*/ * uiNewEntry () ; 
 int /*<<< orphan*/ * uiNewFontButton () ; 
 int /*<<< orphan*/ * uiNewGrid () ; 
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
	uiGrid *grid;
	uiBox *vbox;

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

	// TODO 800x600? the size of the GTK+ example?
	mainwin = uiNewWindow("libui OpenType Features Example", 640, 480, 1);
	uiWindowSetMargined(mainwin, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);

	grid = uiNewGrid();
	uiGridSetPadded(grid, 1);
	uiWindowSetChild(mainwin, uiControl(grid));

	fontButton = uiNewFontButton();
	uiFontButtonOnChanged(fontButton, onFontChanged, NULL);
	uiGridAppend(grid, uiControl(fontButton),
		0, 0, 1, 1,
		// TODO are these Y values correct?
		0, uiAlignFill, 0, uiAlignCenter);

	textEntry = uiNewEntry();
	uiEntrySetText(textEntry, "afford afire aflight");
	uiEntryOnChanged(textEntry, onTextChanged, NULL);
	uiGridAppend(grid, uiControl(textEntry),
		1, 0, 1, 1,
		// TODO are these Y values correct too?
		// TODO add a baseline align? or a form align?
		1, uiAlignFill, 0, uiAlignCenter);

	vbox = uiNewVerticalBox();
	uiBoxSetPadded(vbox, 1);
	uiGridAppend(grid, uiControl(vbox),
		0, 1, 1, 1,
		0, uiAlignFill, 1, uiAlignFill);

	nullFeatures = uiNewCheckbox("NULL uiOpenTypeFeatures");
	uiCheckboxOnToggled(nullFeatures, onNULLToggled, NULL);
	uiBoxAppend(vbox, uiControl(nullFeatures), 0);

	// TODO separator (if other stuff isn't a tab)

	// TODO needed for this to be testable on os x without rewriting everything again
	{
		int x;

		for (x = 0; x < 10; x++)
			uiBoxAppend(vbox, uiControl(uiNewEntry()), 0);
	}

	// TODO other stuff

	area = uiNewArea(&handler);
	uiGridAppend(grid, uiControl(area),
		1, 1, 1, 1,
		1, uiAlignFill, 1, uiAlignFill);

	// and set up the initial draw
	remakeAttrStr();

	uiControlShow(uiControl(mainwin));
	uiMain();

	uiControlDestroy(uiControl(mainwin));
	uiFreeAttributedString(attrstr);
	uiUninit();
	return 0;
}