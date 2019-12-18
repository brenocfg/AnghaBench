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
 int /*<<< orphan*/  GJ_DEBUG (int,char*) ; 
 scalar_t__ GJ_SWITCHER_DIE ; 
 scalar_t__ GJ_SWITCHER_DIED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/ * g_journal_switcher_proc ; 
 scalar_t__ g_journal_switcher_state ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int hz ; 
 int /*<<< orphan*/  tsleep (scalar_t__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
g_journal_stop_switcher(void)
{
	g_topology_assert();
	MPASS(g_journal_switcher_proc != NULL);
	g_journal_switcher_state = GJ_SWITCHER_DIE;
	wakeup(&g_journal_switcher_state);
	while (g_journal_switcher_state != GJ_SWITCHER_DIED)
		tsleep(&g_journal_switcher_state, PRIBIO, "jfini:wait", hz / 5);
	GJ_DEBUG(1, "Switcher died.");
	g_journal_switcher_proc = NULL;
}