#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uiWindow ;
typedef  int /*<<< orphan*/  uiInitOptions ;
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  onClosing ; 
 int /*<<< orphan*/  saySomething ; 
 int /*<<< orphan*/  sayTime ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiBoxSetPadded (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiMain () ; 
 int /*<<< orphan*/  uiMultilineEntrySetReadOnly (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewMultilineEntry () ; 
 int /*<<< orphan*/ * uiNewVerticalBox () ; 
 int /*<<< orphan*/ * uiNewWindow (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTimer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowOnClosing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiWindowSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetMargined (int /*<<< orphan*/ *,int) ; 

int main(void)
{
	uiInitOptions o;
	uiWindow *w;
	uiBox *b;
	uiButton *btn;

	memset(&o, 0, sizeof (uiInitOptions));
	if (uiInit(&o) != NULL)
		abort();

	w = uiNewWindow("Hello", 320, 240, 0);
	uiWindowSetMargined(w, 1);

	b = uiNewVerticalBox();
	uiBoxSetPadded(b, 1);
	uiWindowSetChild(w, uiControl(b));

	e = uiNewMultilineEntry();
	uiMultilineEntrySetReadOnly(e, 1);

	btn = uiNewButton("Say Something");
	uiButtonOnClicked(btn, saySomething, NULL);
	uiBoxAppend(b, uiControl(btn), 0);

	uiBoxAppend(b, uiControl(e), 1);

	uiTimer(1000, sayTime, NULL);

	uiWindowOnClosing(w, onClosing, NULL);
	uiControlShow(uiControl(w));
	uiMain();
	return 0;
}