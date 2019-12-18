#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  p_pid; TYPE_2__* p_dtrace_helpers; } ;
typedef  TYPE_1__ proc_t ;
typedef  int /*<<< orphan*/  dtrace_vstate_t ;
struct TYPE_10__ {int dthps_generation; int dthps_nprovs; TYPE_3__** dthps_provs; TYPE_4__** dthps_actions; int /*<<< orphan*/  dthps_vstate; } ;
typedef  TYPE_2__ dtrace_helpers_t ;
struct TYPE_11__ {int dthp_generation; int /*<<< orphan*/  dthp_prov; } ;
typedef  TYPE_3__ dtrace_helper_provider_t ;
struct TYPE_12__ {int dtha_generation; struct TYPE_12__* dtha_next; } ;
typedef  TYPE_4__ dtrace_helper_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int DTRACE_NHELPER_ACTIONS ; 
 int EINVAL ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/ * dtrace_deferred_pid ; 
 int /*<<< orphan*/  dtrace_helper_action_destroy (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_helper_provider_destroy (TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_helper_provider_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 int /*<<< orphan*/ * dtrace_meta_pid ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_helper_destroygen(dtrace_helpers_t *help, int gen)
{
	proc_t *p = curproc;
	dtrace_vstate_t *vstate;
	int i;

	if (help == NULL)
		help = p->p_dtrace_helpers;

	ASSERT(MUTEX_HELD(&dtrace_lock));

	if (help == NULL || gen > help->dthps_generation)
		return (EINVAL);

	vstate = &help->dthps_vstate;

	for (i = 0; i < DTRACE_NHELPER_ACTIONS; i++) {
		dtrace_helper_action_t *last = NULL, *h, *next;

		for (h = help->dthps_actions[i]; h != NULL; h = next) {
			next = h->dtha_next;

			if (h->dtha_generation == gen) {
				if (last != NULL) {
					last->dtha_next = next;
				} else {
					help->dthps_actions[i] = next;
				}

				dtrace_helper_action_destroy(h, vstate);
			} else {
				last = h;
			}
		}
	}

	/*
	 * Interate until we've cleared out all helper providers with the
	 * given generation number.
	 */
	for (;;) {
		dtrace_helper_provider_t *prov;

		/*
		 * Look for a helper provider with the right generation. We
		 * have to start back at the beginning of the list each time
		 * because we drop dtrace_lock. It's unlikely that we'll make
		 * more than two passes.
		 */
		for (i = 0; i < help->dthps_nprovs; i++) {
			prov = help->dthps_provs[i];

			if (prov->dthp_generation == gen)
				break;
		}

		/*
		 * If there were no matches, we're done.
		 */
		if (i == help->dthps_nprovs)
			break;

		/*
		 * Move the last helper provider into this slot.
		 */
		help->dthps_nprovs--;
		help->dthps_provs[i] = help->dthps_provs[help->dthps_nprovs];
		help->dthps_provs[help->dthps_nprovs] = NULL;

		mutex_exit(&dtrace_lock);

		/*
		 * If we have a meta provider, remove this helper provider.
		 */
		mutex_enter(&dtrace_meta_lock);
		if (dtrace_meta_pid != NULL) {
			ASSERT(dtrace_deferred_pid == NULL);
			dtrace_helper_provider_remove(&prov->dthp_prov,
			    p->p_pid);
		}
		mutex_exit(&dtrace_meta_lock);

		dtrace_helper_provider_destroy(prov);

		mutex_enter(&dtrace_lock);
	}

	return (0);
}