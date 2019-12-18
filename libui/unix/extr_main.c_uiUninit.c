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

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timers ; 
 int /*<<< orphan*/  uiprivUninitAlloc () ; 
 int /*<<< orphan*/  uiprivUninitMenus () ; 
 int /*<<< orphan*/  uninitTimer ; 

void uiUninit(void)
{
	g_hash_table_foreach(timers, uninitTimer, NULL);
	g_hash_table_destroy(timers);
	uiprivUninitMenus();
	uiprivUninitAlloc();
}