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
typedef  int /*<<< orphan*/  uiInitOptions ;
struct TYPE_5__ {int /*<<< orphan*/  A; int /*<<< orphan*/  B; int /*<<< orphan*/  G; int /*<<< orphan*/  R; } ;
typedef  TYPE_1__ uiDrawBrush ;
typedef  int /*<<< orphan*/  uiBox ;
struct TYPE_6__ {int /*<<< orphan*/  KeyEvent; int /*<<< orphan*/  DragBroken; int /*<<< orphan*/  MouseCrossed; int /*<<< orphan*/  MouseEvent; int /*<<< orphan*/  Draw; } ;

/* Variables and functions */
 int /*<<< orphan*/ * colorButton ; 
 int /*<<< orphan*/  colorDodgerBlue ; 
 int /*<<< orphan*/ ** datapoints ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_2__ handler ; 
 int /*<<< orphan*/  handlerDragBroken ; 
 int /*<<< orphan*/  handlerDraw ; 
 int /*<<< orphan*/  handlerKeyEvent ; 
 int /*<<< orphan*/  handlerMouseCrossed ; 
 int /*<<< orphan*/  handlerMouseEvent ; 
 int /*<<< orphan*/ * histogram ; 
 int /*<<< orphan*/ * mainwin ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  onColorChanged ; 
 int /*<<< orphan*/  onDatapointChanged ; 
 int rand () ; 
 int /*<<< orphan*/  setSolidBrush (TYPE_1__*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  shouldQuit ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiBoxSetPadded (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiColorButtonOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiColorButtonSetColor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiFreeInitError (char const*) ; 
 char* uiInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiMain () ; 
 int /*<<< orphan*/ * uiNewArea (TYPE_2__*) ; 
 int /*<<< orphan*/ * uiNewColorButton () ; 
 int /*<<< orphan*/ * uiNewHorizontalBox () ; 
 int /*<<< orphan*/ * uiNewSpinbox (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * uiNewVerticalBox () ; 
 int /*<<< orphan*/ * uiNewWindow (char*,int,int,int) ; 
 int /*<<< orphan*/  uiOnShouldQuit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiSpinboxOnChanged (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiSpinboxSetValue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiUninit () ; 
 int /*<<< orphan*/  uiWindowOnClosing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetMargined (int /*<<< orphan*/ *,int) ; 

int main(void)
{
	uiInitOptions o;
	const char *err;
	uiBox *hbox, *vbox;
	int i;
	uiDrawBrush brush;

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

	mainwin = uiNewWindow("libui Histogram Example", 640, 480, 1);
	uiWindowSetMargined(mainwin, 1);
	uiWindowOnClosing(mainwin, onClosing, NULL);

	hbox = uiNewHorizontalBox();
	uiBoxSetPadded(hbox, 1);
	uiWindowSetChild(mainwin, uiControl(hbox));

	vbox = uiNewVerticalBox();
	uiBoxSetPadded(vbox, 1);
	uiBoxAppend(hbox, uiControl(vbox), 0);

	srand(time(NULL));
	for (i = 0; i < 10; i++) {
		datapoints[i] = uiNewSpinbox(0, 100);
		uiSpinboxSetValue(datapoints[i], rand() % 101);
		uiSpinboxOnChanged(datapoints[i], onDatapointChanged, NULL);
		uiBoxAppend(vbox, uiControl(datapoints[i]), 0);
	}

	colorButton = uiNewColorButton();
	// TODO inline these
	setSolidBrush(&brush, colorDodgerBlue, 1.0);
	uiColorButtonSetColor(colorButton,
		brush.R,
		brush.G,
		brush.B,
		brush.A);
	uiColorButtonOnChanged(colorButton, onColorChanged, NULL);
	uiBoxAppend(vbox, uiControl(colorButton), 0);

	histogram = uiNewArea(&handler);
	uiBoxAppend(hbox, uiControl(histogram), 1);

	uiControlShow(uiControl(mainwin));
	uiMain();
	uiUninit();
	return 0;
}