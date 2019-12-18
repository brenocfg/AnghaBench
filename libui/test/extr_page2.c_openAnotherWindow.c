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
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/ * makePage6 () ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiBoxSetPadded (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewEntry () ; 
 int /*<<< orphan*/ * uiNewVerticalBox () ; 
 int /*<<< orphan*/ * uiNewWindow (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetMargined (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void openAnotherWindow(uiButton *bb, void *data)
{
	uiWindow *w;
	uiBox *b;

	w = uiNewWindow("Another Window", 100, 100, data != NULL);
	if (data != NULL) {
		b = uiNewVerticalBox();
		uiBoxAppend(b, uiControl(uiNewEntry()), 0);
		uiBoxAppend(b, uiControl(uiNewButton("Button")), 0);
		uiBoxSetPadded(b, 1);
		uiWindowSetChild(w, uiControl(b));
	} else
		uiWindowSetChild(w, uiControl(makePage6()));
	uiWindowSetMargined(w, 1);
	uiControlShow(uiControl(w));
}