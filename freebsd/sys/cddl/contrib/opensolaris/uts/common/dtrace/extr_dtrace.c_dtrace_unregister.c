#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_func_t ;
struct TYPE_13__ {void (* dtps_enable ) (void*,dtrace_id_t,void*) ;int /*<<< orphan*/  (* dtps_destroy ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {scalar_t__ dtpv_defunct; struct TYPE_14__* dtpv_name; struct TYPE_14__* dtpv_next; scalar_t__ dtpr_id; struct TYPE_14__* dtpr_name; struct TYPE_14__* dtpr_func; struct TYPE_14__* dtpr_mod; int /*<<< orphan*/  dtpr_arg; int /*<<< orphan*/  dtpv_arg; TYPE_2__ dtpv_pops; struct TYPE_14__* dtpr_nextmod; struct TYPE_14__* dtpr_provider; int /*<<< orphan*/ * dtpr_ecb; } ;
typedef  TYPE_3__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
typedef  TYPE_3__ dtrace_probe_t ;
struct TYPE_12__ {scalar_t__ dts_necbs; } ;
struct TYPE_11__ {TYPE_1__* dta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 TYPE_10__ dtrace_anon ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/  dtrace_byfunc ; 
 int /*<<< orphan*/  dtrace_bymod ; 
 int /*<<< orphan*/  dtrace_byname ; 
 int /*<<< orphan*/ * dtrace_devi ; 
 scalar_t__ dtrace_enabling_reap ; 
 scalar_t__ dtrace_gethrtime () ; 
 int /*<<< orphan*/  dtrace_hash_remove (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int dtrace_nprobes ; 
 scalar_t__ dtrace_nullop ; 
 scalar_t__ dtrace_opens ; 
 TYPE_3__** dtrace_probes ; 
 TYPE_3__* dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 int /*<<< orphan*/  dtrace_taskq ; 
 scalar_t__ dtrace_unregister_defunct_reap ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mod_lock ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,void*) ; 
 int strlen (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,void*,int) ; 

int
dtrace_unregister(dtrace_provider_id_t id)
{
	dtrace_provider_t *old = (dtrace_provider_t *)id;
	dtrace_provider_t *prev = NULL;
	int i, self = 0, noreap = 0;
	dtrace_probe_t *probe, *first = NULL;

	if (old->dtpv_pops.dtps_enable ==
	    (void (*)(void *, dtrace_id_t, void *))dtrace_nullop) {
		/*
		 * If DTrace itself is the provider, we're called with locks
		 * already held.
		 */
		ASSERT(old == dtrace_provider);
#ifdef illumos
		ASSERT(dtrace_devi != NULL);
#endif
		ASSERT(MUTEX_HELD(&dtrace_provider_lock));
		ASSERT(MUTEX_HELD(&dtrace_lock));
		self = 1;

		if (dtrace_provider->dtpv_next != NULL) {
			/*
			 * There's another provider here; return failure.
			 */
			return (EBUSY);
		}
	} else {
		mutex_enter(&dtrace_provider_lock);
#ifdef illumos
		mutex_enter(&mod_lock);
#endif
		mutex_enter(&dtrace_lock);
	}

	/*
	 * If anyone has /dev/dtrace open, or if there are anonymous enabled
	 * probes, we refuse to let providers slither away, unless this
	 * provider has already been explicitly invalidated.
	 */
	if (!old->dtpv_defunct &&
	    (dtrace_opens || (dtrace_anon.dta_state != NULL &&
	    dtrace_anon.dta_state->dts_necbs > 0))) {
		if (!self) {
			mutex_exit(&dtrace_lock);
#ifdef illumos
			mutex_exit(&mod_lock);
#endif
			mutex_exit(&dtrace_provider_lock);
		}
		return (EBUSY);
	}

	/*
	 * Attempt to destroy the probes associated with this provider.
	 */
	for (i = 0; i < dtrace_nprobes; i++) {
		if ((probe = dtrace_probes[i]) == NULL)
			continue;

		if (probe->dtpr_provider != old)
			continue;

		if (probe->dtpr_ecb == NULL)
			continue;

		/*
		 * If we are trying to unregister a defunct provider, and the
		 * provider was made defunct within the interval dictated by
		 * dtrace_unregister_defunct_reap, we'll (asynchronously)
		 * attempt to reap our enablings.  To denote that the provider
		 * should reattempt to unregister itself at some point in the
		 * future, we will return a differentiable error code (EAGAIN
		 * instead of EBUSY) in this case.
		 */
		if (dtrace_gethrtime() - old->dtpv_defunct >
		    dtrace_unregister_defunct_reap)
			noreap = 1;

		if (!self) {
			mutex_exit(&dtrace_lock);
#ifdef illumos
			mutex_exit(&mod_lock);
#endif
			mutex_exit(&dtrace_provider_lock);
		}

		if (noreap)
			return (EBUSY);

		(void) taskq_dispatch(dtrace_taskq,
		    (task_func_t *)dtrace_enabling_reap, NULL, TQ_SLEEP);

		return (EAGAIN);
	}

	/*
	 * All of the probes for this provider are disabled; we can safely
	 * remove all of them from their hash chains and from the probe array.
	 */
	for (i = 0; i < dtrace_nprobes; i++) {
		if ((probe = dtrace_probes[i]) == NULL)
			continue;

		if (probe->dtpr_provider != old)
			continue;

		dtrace_probes[i] = NULL;

		dtrace_hash_remove(dtrace_bymod, probe);
		dtrace_hash_remove(dtrace_byfunc, probe);
		dtrace_hash_remove(dtrace_byname, probe);

		if (first == NULL) {
			first = probe;
			probe->dtpr_nextmod = NULL;
		} else {
			probe->dtpr_nextmod = first;
			first = probe;
		}
	}

	/*
	 * The provider's probes have been removed from the hash chains and
	 * from the probe array.  Now issue a dtrace_sync() to be sure that
	 * everyone has cleared out from any probe array processing.
	 */
	dtrace_sync();

	for (probe = first; probe != NULL; probe = first) {
		first = probe->dtpr_nextmod;

		old->dtpv_pops.dtps_destroy(old->dtpv_arg, probe->dtpr_id,
		    probe->dtpr_arg);
		kmem_free(probe->dtpr_mod, strlen(probe->dtpr_mod) + 1);
		kmem_free(probe->dtpr_func, strlen(probe->dtpr_func) + 1);
		kmem_free(probe->dtpr_name, strlen(probe->dtpr_name) + 1);
#ifdef illumos
		vmem_free(dtrace_arena, (void *)(uintptr_t)(probe->dtpr_id), 1);
#else
		free_unr(dtrace_arena, probe->dtpr_id);
#endif
		kmem_free(probe, sizeof (dtrace_probe_t));
	}

	if ((prev = dtrace_provider) == old) {
#ifdef illumos
		ASSERT(self || dtrace_devi == NULL);
		ASSERT(old->dtpv_next == NULL || dtrace_devi == NULL);
#endif
		dtrace_provider = old->dtpv_next;
	} else {
		while (prev != NULL && prev->dtpv_next != old)
			prev = prev->dtpv_next;

		if (prev == NULL) {
			panic("attempt to unregister non-existent "
			    "dtrace provider %p\n", (void *)id);
		}

		prev->dtpv_next = old->dtpv_next;
	}

	if (!self) {
		mutex_exit(&dtrace_lock);
#ifdef illumos
		mutex_exit(&mod_lock);
#endif
		mutex_exit(&dtrace_provider_lock);
	}

	kmem_free(old->dtpv_name, strlen(old->dtpv_name) + 1);
	kmem_free(old, sizeof (dtrace_provider_t));

	return (0);
}