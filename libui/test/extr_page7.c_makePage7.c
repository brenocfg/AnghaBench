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
typedef  int /*<<< orphan*/  uiGroup ;
typedef  int /*<<< orphan*/  uiBox ;

/* Variables and functions */
 int /*<<< orphan*/ * makePage7a () ; 
 int /*<<< orphan*/ * makePage7b () ; 
 int /*<<< orphan*/ * makePage7c () ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/ * newVerticalBox () ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 

uiBox *makePage7(void)
{
	uiBox *page7;
	uiGroup *group;
	uiBox *box2;

	page7 = newHorizontalBox();

	group = makePage7a();
	uiBoxAppend(page7, uiControl(group), 1);

	box2 = newVerticalBox();
	uiBoxAppend(page7, uiControl(box2), 1);

	group = makePage7b();
	uiBoxAppend(box2, uiControl(group), 1);

	group = makePage7c();
	uiBoxAppend(box2, uiControl(group), 1);

	return page7;
}