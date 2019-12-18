#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dts_necbs; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dtrace_provider_id_t ;
typedef  int /*<<< orphan*/  dtrace_anon_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  delete_unrhdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_anon ; 
 TYPE_1__* dtrace_anon_grab () ; 
 int /*<<< orphan*/  dtrace_arena ; 
 int /*<<< orphan*/ * dtrace_byfunc ; 
 int /*<<< orphan*/ * dtrace_bymod ; 
 int /*<<< orphan*/ * dtrace_byname ; 
 int /*<<< orphan*/  dtrace_dev ; 
 int /*<<< orphan*/  dtrace_errlock ; 
 int /*<<< orphan*/  dtrace_hash_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ dtrace_helpers ; 
 int /*<<< orphan*/  dtrace_invop_uninit () ; 
 int /*<<< orphan*/  dtrace_kld_load_tag ; 
 int /*<<< orphan*/  dtrace_kld_unload_try_tag ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_meta_lock ; 
 scalar_t__ dtrace_nprobes ; 
 scalar_t__ dtrace_opens ; 
 int /*<<< orphan*/ * dtrace_probes ; 
 int /*<<< orphan*/ * dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/ * dtrace_retained ; 
 int /*<<< orphan*/  dtrace_state_cache ; 
 int /*<<< orphan*/  dtrace_state_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  dtrace_taskq ; 
 int /*<<< orphan*/ * dtrace_toxrange ; 
 scalar_t__ dtrace_toxranges ; 
 scalar_t__ dtrace_toxranges_max ; 
 int /*<<< orphan*/ * dtrace_trap_func ; 
 scalar_t__ dtrace_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_vtime_active ; 
 scalar_t__ dtrace_vtime_references ; 
 int /*<<< orphan*/ * dtrace_vtime_switch_func ; 
 int /*<<< orphan*/  helper_dev ; 
 int /*<<< orphan*/  kld_load ; 
 int /*<<< orphan*/  kld_unload_try ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_unload()
{
	dtrace_state_t *state;
	int error = 0;

	destroy_dev(dtrace_dev);
	destroy_dev(helper_dev);

	mutex_enter(&dtrace_provider_lock);
	mutex_enter(&dtrace_lock);
	mutex_enter(&cpu_lock);

	ASSERT(dtrace_opens == 0);

	if (dtrace_helpers > 0) {
		mutex_exit(&cpu_lock);
		mutex_exit(&dtrace_lock);
		mutex_exit(&dtrace_provider_lock);
		return (EBUSY);
	}

	if (dtrace_unregister((dtrace_provider_id_t)dtrace_provider) != 0) {
		mutex_exit(&cpu_lock);
		mutex_exit(&dtrace_lock);
		mutex_exit(&dtrace_provider_lock);
		return (EBUSY);
	}

	dtrace_provider = NULL;
	EVENTHANDLER_DEREGISTER(kld_load, dtrace_kld_load_tag);
	EVENTHANDLER_DEREGISTER(kld_unload_try, dtrace_kld_unload_try_tag);

	if ((state = dtrace_anon_grab()) != NULL) {
		/*
		 * If there were ECBs on this state, the provider should
		 * have not been allowed to detach; assert that there is
		 * none.
		 */
		ASSERT(state->dts_necbs == 0);
		dtrace_state_destroy(state);
	}

	bzero(&dtrace_anon, sizeof (dtrace_anon_t));

	mutex_exit(&cpu_lock);

	if (dtrace_probes != NULL) {
		kmem_free(dtrace_probes, 0);
		dtrace_probes = NULL;
		dtrace_nprobes = 0;
	}

	dtrace_hash_destroy(dtrace_bymod);
	dtrace_hash_destroy(dtrace_byfunc);
	dtrace_hash_destroy(dtrace_byname);
	dtrace_bymod = NULL;
	dtrace_byfunc = NULL;
	dtrace_byname = NULL;

	kmem_cache_destroy(dtrace_state_cache);

	delete_unrhdr(dtrace_arena);

	if (dtrace_toxrange != NULL) {
		kmem_free(dtrace_toxrange, 0);
		dtrace_toxrange = NULL;
		dtrace_toxranges = 0;
		dtrace_toxranges_max = 0;
	}

	ASSERT(dtrace_vtime_references == 0);
	ASSERT(dtrace_opens == 0);
	ASSERT(dtrace_retained == NULL);

	mutex_exit(&dtrace_lock);
	mutex_exit(&dtrace_provider_lock);

	mutex_destroy(&dtrace_meta_lock);
	mutex_destroy(&dtrace_provider_lock);
	mutex_destroy(&dtrace_lock);
#ifdef DEBUG
	mutex_destroy(&dtrace_errlock);
#endif

	taskq_destroy(dtrace_taskq);

	/* Reset our hook for exceptions. */
	dtrace_invop_uninit();

	/*
	 * Reset our hook for thread switches, but ensure that vtime isn't
	 * active first.
	 */
	dtrace_vtime_active = 0;
	dtrace_vtime_switch_func = NULL;

	/* Unhook from the trap handler. */
	dtrace_trap_func = NULL;

	return (error);
}