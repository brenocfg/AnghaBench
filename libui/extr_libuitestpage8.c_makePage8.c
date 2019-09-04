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
typedef  int /*<<< orphan*/  uiMultilineEntry ;
typedef  int /*<<< orphan*/  uiGroup ;
typedef  int /*<<< orphan*/  uiButton ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/ * newGroup (char*) ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  onListFonts ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonOnClicked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiGroupSetChild (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uiNewButton (char*) ; 
 int /*<<< orphan*/ * uiNewMultilineEntry () ; 

uiBox *makePage8(void)
{
	uiBox *page8;
	uiGroup *group;
	uiBox *vbox;
	uiMultilineEntry *me;
	uiButton *button;

	page8 = newHorizontalBox();

	group = newGroup("Font Families");
	uiBoxAppend(page8, uiControl(group), 1);

	vbox = newVerticalBox();
	uiGroupSetChild(group, uiControl(vbox));

	me = uiNewMultilineEntry();
	uiBoxAppend(vbox, uiControl(me), 1);

	button = uiNewButton("List Font Families");
	uiButtonOnClicked(button, onListFonts, me);
	uiBoxAppend(vbox, uiControl(button), 0);

	return page8;
}