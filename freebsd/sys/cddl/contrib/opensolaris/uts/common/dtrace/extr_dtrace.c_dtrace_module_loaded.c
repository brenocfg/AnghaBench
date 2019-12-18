#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_func_t ;
struct TYPE_8__ {int /*<<< orphan*/  mod_busy; } ;
typedef  TYPE_2__ modctl_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* dtps_provide_module ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  dtpv_arg; TYPE_1__ dtpv_pops; struct TYPE_9__* dtpv_next; } ;
typedef  TYPE_3__ dtrace_provider_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  delay (int) ; 
 scalar_t__ dtrace_enabling_matchall ; 
 int /*<<< orphan*/  dtrace_lock ; 
 TYPE_3__* dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/ * dtrace_retained ; 
 int /*<<< orphan*/  dtrace_taskq ; 
 int /*<<< orphan*/  mod_lock ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_module_loaded(modctl_t *ctl)
{
	dtrace_provider_t *prv;

	mutex_enter(&dtrace_provider_lock);
#ifdef illumos
	mutex_enter(&mod_lock);
#endif

#ifdef illumos
	ASSERT(ctl->mod_busy);
#endif

	/*
	 * We're going to call each providers per-module provide operation
	 * specifying only this module.
	 */
	for (prv = dtrace_provider; prv != NULL; prv = prv->dtpv_next)
		prv->dtpv_pops.dtps_provide_module(prv->dtpv_arg, ctl);

#ifdef illumos
	mutex_exit(&mod_lock);
#endif
	mutex_exit(&dtrace_provider_lock);

	/*
	 * If we have any retained enablings, we need to match against them.
	 * Enabling probes requires that cpu_lock be held, and we cannot hold
	 * cpu_lock here -- it is legal for cpu_lock to be held when loading a
	 * module.  (In particular, this happens when loading scheduling
	 * classes.)  So if we have any retained enablings, we need to dispatch
	 * our task queue to do the match for us.
	 */
	mutex_enter(&dtrace_lock);

	if (dtrace_retained == NULL) {
		mutex_exit(&dtrace_lock);
		return;
	}

	(void) taskq_dispatch(dtrace_taskq,
	    (task_func_t *)dtrace_enabling_matchall, NULL, TQ_SLEEP);

	mutex_exit(&dtrace_lock);

	/*
	 * And now, for a little heuristic sleaze:  in general, we want to
	 * match modules as soon as they load.  However, we cannot guarantee
	 * this, because it would lead us to the lock ordering violation
	 * outlined above.  The common case, of course, is that cpu_lock is
	 * _not_ held -- so we delay here for a clock tick, hoping that that's
	 * long enough for the task queue to do its work.  If it's not, it's
	 * not a serious problem -- it just means that the module that we
	 * just loaded may not be immediately instrumentable.
	 */
	delay(1);
}