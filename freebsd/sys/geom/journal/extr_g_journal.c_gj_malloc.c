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
typedef  int /*<<< orphan*/  u_char ;
struct meminfo {size_t mi_size; int /*<<< orphan*/  mi_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  GJ_DEBUG (int,char*) ; 
 int /*<<< orphan*/  M_JOURNAL ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  g_journal_cache_alloc_failures ; 
 scalar_t__ g_journal_cache_limit ; 
 scalar_t__ g_journal_cache_low ; 
 int /*<<< orphan*/  g_journal_cache_mtx ; 
 scalar_t__ g_journal_cache_used ; 
 int /*<<< orphan*/  g_journal_switcher_state ; 
 int g_journal_switcher_wokenup ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
gj_malloc(size_t size, int flags)
{
	void *p;
#ifdef GJ_MEMDEBUG
	struct meminfo *mi;
#endif

	mtx_lock(&g_journal_cache_mtx);
	if (g_journal_cache_limit > 0 && !g_journal_switcher_wokenup &&
	    g_journal_cache_used + size > g_journal_cache_low) {
		GJ_DEBUG(1, "No cache, waking up the switcher.");
		g_journal_switcher_wokenup = 1;
		wakeup(&g_journal_switcher_state);
	}
	if ((flags & M_NOWAIT) && g_journal_cache_limit > 0 &&
	    g_journal_cache_used + size > g_journal_cache_limit) {
		mtx_unlock(&g_journal_cache_mtx);
		g_journal_cache_alloc_failures++;
		return (NULL);
	}
	g_journal_cache_used += size;
	mtx_unlock(&g_journal_cache_mtx);
	flags &= ~M_NOWAIT;
#ifndef GJ_MEMDEBUG
	p = malloc(size, M_JOURNAL, flags | M_WAITOK);
#else
	mi = malloc(sizeof(*mi) + size, M_JOURNAL, flags | M_WAITOK);
	p = (u_char *)mi + sizeof(*mi);
	mi->mi_size = size;
	stack_save(&mi->mi_stack);
#endif
	return (p);
}