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
typedef  int /*<<< orphan*/  uiButton ;

/* Variables and functions */
 int /*<<< orphan*/  mainBox ; 
 int /*<<< orphan*/  mainTab ; 
 int moveBack ; 
 int /*<<< orphan*/  moveBackText ; 
 int /*<<< orphan*/  moveOutText ; 
 int /*<<< orphan*/  page1 ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiBoxDelete (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiButtonSetText (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTabDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiTabInsertAt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void movePage1(uiButton *b, void *data)
{
	if (moveBack) {
		uiBoxDelete(mainBox, 1);
		uiTabInsertAt(mainTab, "Page 1", 0, uiControl(page1));
		uiButtonSetText(b, moveOutText);
		moveBack = 0;
		return;
	}
	uiTabDelete(mainTab, 0);
	uiBoxAppend(mainBox, uiControl(page1), 1);
	uiButtonSetText(b, moveBackText);
	moveBack = 1;
}