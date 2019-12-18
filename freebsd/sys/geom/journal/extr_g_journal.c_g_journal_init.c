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
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_FIRST ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct g_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GJ_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int g_journal_cache_divisor ; 
 int g_journal_cache_limit ; 
 int g_journal_cache_low ; 
 int g_journal_cache_switch ; 
 int /*<<< orphan*/ * g_journal_event_lowmem ; 
 int /*<<< orphan*/ * g_journal_event_shutdown ; 
 int /*<<< orphan*/  g_journal_lowmem ; 
 int /*<<< orphan*/  g_journal_shutdown ; 
 int /*<<< orphan*/  shutdown_post_sync ; 
 int vm_kmem_size ; 
 int /*<<< orphan*/  vm_lowmem ; 

__attribute__((used)) static void
g_journal_init(struct g_class *mp)
{

	/* Pick a conservative value if provided value sucks. */
	if (g_journal_cache_divisor <= 0 ||
	    (vm_kmem_size / g_journal_cache_divisor == 0)) {
		g_journal_cache_divisor = 5;
	}
	if (g_journal_cache_limit > 0) {
		g_journal_cache_limit = vm_kmem_size / g_journal_cache_divisor;
		g_journal_cache_low =
		    (g_journal_cache_limit / 100) * g_journal_cache_switch;
	}
	g_journal_event_shutdown = EVENTHANDLER_REGISTER(shutdown_post_sync,
	    g_journal_shutdown, mp, EVENTHANDLER_PRI_FIRST);
	if (g_journal_event_shutdown == NULL)
		GJ_DEBUG(0, "Warning! Cannot register shutdown event.");
	g_journal_event_lowmem = EVENTHANDLER_REGISTER(vm_lowmem,
	    g_journal_lowmem, mp, EVENTHANDLER_PRI_FIRST);
	if (g_journal_event_lowmem == NULL)
		GJ_DEBUG(0, "Warning! Cannot register lowmem event.");
}