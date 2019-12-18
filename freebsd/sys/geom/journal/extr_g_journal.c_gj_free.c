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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_JOURNAL ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_journal_cache_mtx ; 
 size_t g_journal_cache_used ; 
 int /*<<< orphan*/  kdb_backtrace () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stack_print (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gj_free(void *p, size_t size)
{
#ifdef GJ_MEMDEBUG
	struct meminfo *mi;
#endif

	KASSERT(p != NULL, ("p=NULL"));
	KASSERT(size > 0, ("size=0"));
	mtx_lock(&g_journal_cache_mtx);
	KASSERT(g_journal_cache_used >= size, ("Freeing too much?"));
	g_journal_cache_used -= size;
	mtx_unlock(&g_journal_cache_mtx);
#ifdef GJ_MEMDEBUG
	mi = p = (void *)((u_char *)p - sizeof(*mi));
	if (mi->mi_size != size) {
		printf("GJOURNAL: Size mismatch! %zu != %zu\n", size,
		    mi->mi_size);
		printf("GJOURNAL: Alloc backtrace:\n");
		stack_print(&mi->mi_stack);
		printf("GJOURNAL: Free backtrace:\n");
		kdb_backtrace();
	}
#endif
	free(p, M_JOURNAL);
}