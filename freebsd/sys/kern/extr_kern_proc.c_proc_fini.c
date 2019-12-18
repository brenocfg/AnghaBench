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
struct proc {int /*<<< orphan*/ * p_ksi; int /*<<< orphan*/  p_mtx; int /*<<< orphan*/  p_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int /*<<< orphan*/ ,struct proc*) ; 
 int /*<<< orphan*/  FIRST_THREAD_IN_PROC (struct proc*) ; 
 int /*<<< orphan*/  ksiginfo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  process_fini ; 
 int /*<<< orphan*/  pstats_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
proc_fini(void *mem, int size)
{
#ifdef notnow
	struct proc *p;

	p = (struct proc *)mem;
	EVENTHANDLER_DIRECT_INVOKE(process_fini, p);
	pstats_free(p->p_stats);
	thread_free(FIRST_THREAD_IN_PROC(p));
	mtx_destroy(&p->p_mtx);
	if (p->p_ksi != NULL)
		ksiginfo_free(p->p_ksi);
#else
	panic("proc reclaimed");
#endif
}