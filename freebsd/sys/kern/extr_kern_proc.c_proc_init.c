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
struct proc {int /*<<< orphan*/ * p_pgrp; int /*<<< orphan*/  p_stats; int /*<<< orphan*/  p_threads; int /*<<< orphan*/  p_pwait; int /*<<< orphan*/  p_profmtx; int /*<<< orphan*/  p_itimmtx; int /*<<< orphan*/  p_statmtx; int /*<<< orphan*/  p_slock; int /*<<< orphan*/  p_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int /*<<< orphan*/ ,struct proc*) ; 
 int MTX_DEF ; 
 int MTX_DUPOK ; 
 int MTX_NEW ; 
 int MTX_SPIN ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  process_init ; 
 int /*<<< orphan*/  pstats_alloc () ; 

__attribute__((used)) static int
proc_init(void *mem, int size, int flags)
{
	struct proc *p;

	p = (struct proc *)mem;
	mtx_init(&p->p_mtx, "process lock", NULL, MTX_DEF | MTX_DUPOK | MTX_NEW);
	mtx_init(&p->p_slock, "process slock", NULL, MTX_SPIN | MTX_NEW);
	mtx_init(&p->p_statmtx, "pstatl", NULL, MTX_SPIN | MTX_NEW);
	mtx_init(&p->p_itimmtx, "pitiml", NULL, MTX_SPIN | MTX_NEW);
	mtx_init(&p->p_profmtx, "pprofl", NULL, MTX_SPIN | MTX_NEW);
	cv_init(&p->p_pwait, "ppwait");
	TAILQ_INIT(&p->p_threads);	     /* all threads in proc */
	EVENTHANDLER_DIRECT_INVOKE(process_init, p);
	p->p_stats = pstats_alloc();
	p->p_pgrp = NULL;
	return (0);
}