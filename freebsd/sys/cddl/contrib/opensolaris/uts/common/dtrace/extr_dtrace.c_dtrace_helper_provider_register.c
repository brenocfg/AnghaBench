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
struct TYPE_8__ {int /*<<< orphan*/  p_pid; } ;
typedef  TYPE_2__ proc_t ;
struct TYPE_9__ {int dthps_deferred; int dthps_nprovs; TYPE_1__** dthps_provs; struct TYPE_9__* dthps_prev; struct TYPE_9__* dthps_next; int /*<<< orphan*/  dthps_pid; } ;
typedef  TYPE_3__ dtrace_helpers_t ;
typedef  int /*<<< orphan*/  dof_helper_t ;
struct TYPE_7__ {int /*<<< orphan*/  dthp_prov; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_NOT_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_attached () ; 
 TYPE_3__* dtrace_deferred_pid ; 
 int /*<<< orphan*/  dtrace_helper_provide (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 int /*<<< orphan*/ * dtrace_meta_pid ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_helper_provider_register(proc_t *p, dtrace_helpers_t *help,
    dof_helper_t *dofhp)
{
	ASSERT(MUTEX_NOT_HELD(&dtrace_lock));

	mutex_enter(&dtrace_meta_lock);
	mutex_enter(&dtrace_lock);

	if (!dtrace_attached() || dtrace_meta_pid == NULL) {
		/*
		 * If the dtrace module is loaded but not attached, or if
		 * there aren't isn't a meta provider registered to deal with
		 * these provider descriptions, we need to postpone creating
		 * the actual providers until later.
		 */

		if (help->dthps_next == NULL && help->dthps_prev == NULL &&
		    dtrace_deferred_pid != help) {
			help->dthps_deferred = 1;
			help->dthps_pid = p->p_pid;
			help->dthps_next = dtrace_deferred_pid;
			help->dthps_prev = NULL;
			if (dtrace_deferred_pid != NULL)
				dtrace_deferred_pid->dthps_prev = help;
			dtrace_deferred_pid = help;
		}

		mutex_exit(&dtrace_lock);

	} else if (dofhp != NULL) {
		/*
		 * If the dtrace module is loaded and we have a particular
		 * helper provider description, pass that off to the
		 * meta provider.
		 */

		mutex_exit(&dtrace_lock);

		dtrace_helper_provide(dofhp, p->p_pid);

	} else {
		/*
		 * Otherwise, just pass all the helper provider descriptions
		 * off to the meta provider.
		 */

		int i;
		mutex_exit(&dtrace_lock);

		for (i = 0; i < help->dthps_nprovs; i++) {
			dtrace_helper_provide(&help->dthps_provs[i]->dthp_prov,
			    p->p_pid);
		}
	}

	mutex_exit(&dtrace_meta_lock);
}