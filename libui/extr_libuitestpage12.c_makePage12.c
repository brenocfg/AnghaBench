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
 int /*<<< orphan*/ * half (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * newHorizontalBox () ; 
 int /*<<< orphan*/  uiBoxAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uiControl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiNewMultilineEntry ; 
 int /*<<< orphan*/  uiNewNonWrappingMultilineEntry ; 

uiBox *makePage12(void)
{
	uiBox *page12;
	uiBox *b;

	page12 = newHorizontalBox();

	b = half(uiNewMultilineEntry, "wrap");
	uiBoxAppend(page12, uiControl(b), 1);
	b = half(uiNewNonWrappingMultilineEntry, "no wrap");
	uiBoxAppend(page12, uiControl(b), 1);

	return page12;
}