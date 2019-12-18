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
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/ * makeSet (int,int,int) ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/ * newhbox () ; 
 int /*<<< orphan*/ * newvbox () ; 
 int /*<<< orphan*/ * stub1 () ; 
 int /*<<< orphan*/ * stub2 () ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 

uiBox *makePage3(void)
{
	uiBox *page3;
	uiBox *hbox;
	uiBox *hbox2;
	uiBox *vbox;
	int hidden;

	page3 = newVerticalBox();

	// first the non-stretchy type
	for (hidden = 0; hidden < 4; hidden++) {
		// these two must stay unpadded as well, otherwise the test isn't meaningful
		hbox2 = (*newhbox)();
		vbox = (*newvbox)();
		// reference set
		hbox = makeSet(hidden, -1, 0);
		uiBoxAppend(vbox, uiControl(hbox), 0);
		// real thing
		hbox = makeSet(-1, hidden, 0);
		uiBoxAppend(vbox, uiControl(hbox), 0);
		// pack vbox in
		uiBoxAppend(hbox2, uiControl(vbox), 0);
		// and have a button in there for showing right margins
		uiBoxAppend(hbox2, uiControl(uiNewButton("Right Margin Test")), 1);
		uiBoxAppend(page3, uiControl(hbox2), 0);
	}

	// then the stretchy type
	for (hidden = 0; hidden < 4; hidden++) {
		hbox = makeSet(-1, hidden, 1);
		uiBoxAppend(page3, uiControl(hbox), 0);
	}

	return page3;
}