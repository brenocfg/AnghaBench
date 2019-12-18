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
typedef  int /*<<< orphan*/  uiLabel ;
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * description ; 
 int /*<<< orphan*/  msgBox ; 
 int /*<<< orphan*/  msgBoxError ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  openFile ; 
 int /*<<< orphan*/ * parent ; 
 int /*<<< orphan*/  saveFile ; 
 int /*<<< orphan*/ * title ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiEntrySetText (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewEntry () ; 

uiBox *makePage5(uiWindow *pw)
{
	uiBox *page5;
	uiBox *hbox;
	uiButton *button;
	uiLabel *label;

	parent = pw;

	page5 = newVerticalBox();

#define D(n, f) \
	hbox = newHorizontalBox(); \
	button = uiNewButton(n); \
	label = uiNewLabel(""); \
	uiButtonOnClicked(button, f, label); \
	uiBoxAppend(hbox, uiControl(button), 0); \
	uiBoxAppend(hbox, uiControl(label), 0); \
	uiBoxAppend(page5, uiControl(hbox), 0);

	D("Open File", openFile);
	D("Save File", saveFile);

	title = uiNewEntry();
	uiEntrySetText(title, "Title");
	description = uiNewEntry();
	uiEntrySetText(description, "Description");

	hbox = newHorizontalBox();
	button = uiNewButton("Message Box");
	uiButtonOnClicked(button, msgBox, NULL);
	uiBoxAppend(hbox, uiControl(button), 0);
	uiBoxAppend(hbox, uiControl(title), 0);
	uiBoxAppend(page5, uiControl(hbox), 0);

	hbox = newHorizontalBox();
	button = uiNewButton("Error Box");
	uiButtonOnClicked(button, msgBoxError, NULL);
	uiBoxAppend(hbox, uiControl(button), 0);
	uiBoxAppend(hbox, uiControl(description), 0);
	uiBoxAppend(page5, uiControl(hbox), 0);

	return page5;
}