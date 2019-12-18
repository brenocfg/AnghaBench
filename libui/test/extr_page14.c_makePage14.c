#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiTab ;
struct TYPE_2__ {int /*<<< orphan*/  (* f ) () ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * newTab () ; 
 TYPE_1__* pages ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  uiTabAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uiTab *makePage14(void)
{
	uiTab *page14;
	int i;

	page14 = newTab();

	for (i = 0; pages[i].name != NULL; i++)
		uiTabAppend(page14,
			pages[i].name,
			(*(pages[i].f))());

	return page14;
}