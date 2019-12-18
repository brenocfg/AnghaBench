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
 int /*<<< orphan*/  MIN (size_t,size_t) ; 
 int /*<<< orphan*/  M_JOURNAL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_journal_cache_mtx ; 
 size_t g_journal_cache_used ; 
 int /*<<< orphan*/  gj_free (void*,size_t) ; 
 void* gj_malloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 void* realloc (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
gj_realloc(void *p, size_t size, size_t oldsize)
{
	void *np;

#ifndef GJ_MEMDEBUG
	mtx_lock(&g_journal_cache_mtx);
	g_journal_cache_used -= oldsize;
	g_journal_cache_used += size;
	mtx_unlock(&g_journal_cache_mtx);
	np = realloc(p, size, M_JOURNAL, M_WAITOK);
#else
	np = gj_malloc(size, M_WAITOK);
	bcopy(p, np, MIN(oldsize, size));
	gj_free(p, oldsize);
#endif
	return (np);
}