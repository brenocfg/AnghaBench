#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t processorid_t ;
typedef  int /*<<< orphan*/  dtrace_xcall_t ;
struct TYPE_28__ {int dcr_visible; TYPE_3__* dcr_cred; int /*<<< orphan*/  dcr_destructive; } ;
struct TYPE_24__ {int /*<<< orphan*/  dtvs_dynvars; } ;
struct TYPE_29__ {int* dts_options; scalar_t__ dts_activity; int dts_nspeculations; scalar_t__ dts_necbs; int dts_needed; scalar_t__ dts_getf; TYPE_6__* dts_speculations; TYPE_6__* dts_aggbuffer; TYPE_6__* dts_buffer; TYPE_4__ dts_cred; void* dts_deadman; void* dts_cleaner; int /*<<< orphan*/  dts_laststatus; int /*<<< orphan*/  dts_alive; TYPE_1__ dts_vstate; int /*<<< orphan*/ * dts_aggregations; scalar_t__ dts_speculates; struct TYPE_29__* dts_anon; scalar_t__ dts_destructive; } ;
typedef  TYPE_5__ dtrace_state_t ;
struct TYPE_30__ {int dtb_flags; struct TYPE_30__* dtsp_buffer; } ;
typedef  TYPE_6__ dtrace_speculation_t ;
typedef  int dtrace_optval_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
typedef  TYPE_6__ dtrace_buffer_t ;
struct TYPE_31__ {int cyt_interval; scalar_t__ cyt_when; } ;
typedef  TYPE_8__ cyc_time_t ;
struct TYPE_32__ {void* cyh_level; TYPE_5__* cyh_arg; void* cyh_func; } ;
typedef  TYPE_9__ cyc_handler_t ;
typedef  void* cyc_func_t ;
struct TYPE_27__ {TYPE_2__* cr_zone; } ;
struct TYPE_26__ {int /*<<< orphan*/  zone_dtrace_getf; } ;
struct TYPE_25__ {size_t dta_beganon; TYPE_5__* dta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* CY_LOW_LEVEL ; 
 int DTRACEBUF_INACTIVE ; 
 size_t DTRACEOPT_AGGSIZE ; 
 size_t DTRACEOPT_BUFRESIZE ; 
 int DTRACEOPT_BUFRESIZE_MANUAL ; 
 size_t DTRACEOPT_BUFSIZE ; 
 size_t DTRACEOPT_CLEANRATE ; 
 size_t DTRACEOPT_DYNVARSIZE ; 
 size_t DTRACEOPT_GRABANON ; 
 size_t DTRACEOPT_NSPEC ; 
 size_t DTRACEOPT_SPECSIZE ; 
 size_t DTRACEOPT_STATUSRATE ; 
 int DTRACEOPT_UNSET ; 
 scalar_t__ DTRACE_ACTIVITY_ACTIVE ; 
 scalar_t__ DTRACE_ACTIVITY_DRAINING ; 
 scalar_t__ DTRACE_ACTIVITY_INACTIVE ; 
 scalar_t__ DTRACE_ACTIVITY_WARMUP ; 
 int /*<<< orphan*/  DTRACE_CPUALL ; 
 int DTRACE_CRV_KERNEL ; 
 int EACCES ; 
 int EALREADY ; 
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int INT_MAX ; 
 int KM_NORMALPRI ; 
 int KM_NOSLEEP ; 
 int NANOSEC ; 
 int NCPU ; 
 int /*<<< orphan*/  callout_reset (void**,int,scalar_t__,TYPE_5__*) ; 
 int /*<<< orphan*/  cpu_lock ; 
 size_t curcpu ; 
 void* cyclic_add (TYPE_9__*,TYPE_8__*) ; 
 TYPE_20__ dtrace_anon ; 
 TYPE_5__* dtrace_anon_grab () ; 
 scalar_t__ dtrace_buffer_activate ; 
 int /*<<< orphan*/  dtrace_buffer_activate_cpu (TYPE_5__*,int) ; 
 int /*<<< orphan*/  dtrace_buffer_free (TYPE_6__*) ; 
 int dtrace_cleanrate_max ; 
 int dtrace_cleanrate_min ; 
 int /*<<< orphan*/ * dtrace_closef ; 
 int dtrace_deadman_interval ; 
 int dtrace_dstate_defsize ; 
 int dtrace_dstate_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dtrace_enabling_prime (TYPE_5__*) ; 
 int /*<<< orphan*/  dtrace_getf ; 
 int /*<<< orphan*/ * dtrace_getf_barrier ; 
 int /*<<< orphan*/  dtrace_gethrtime () ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probeid_begin ; 
 int dtrace_state_buffers (TYPE_5__*) ; 
 scalar_t__ dtrace_state_clean ; 
 scalar_t__ dtrace_state_deadman ; 
 int /*<<< orphan*/  dtrace_state_prereserve (TYPE_5__*) ; 
 int dtrace_statusrate_max ; 
 int /*<<< orphan*/  dtrace_xcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int hz ; 
 int /*<<< orphan*/  kmem_free (TYPE_6__*,int) ; 
 TYPE_6__* kmem_zalloc (int,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_state_go(dtrace_state_t *state, processorid_t *cpu)
{
	dtrace_optval_t *opt = state->dts_options, sz, nspec;
	dtrace_speculation_t *spec;
	dtrace_buffer_t *buf;
#ifdef illumos
	cyc_handler_t hdlr;
	cyc_time_t when;
#endif
	int rval = 0, i, bufsize = NCPU * sizeof (dtrace_buffer_t);
	dtrace_icookie_t cookie;

	mutex_enter(&cpu_lock);
	mutex_enter(&dtrace_lock);

	if (state->dts_activity != DTRACE_ACTIVITY_INACTIVE) {
		rval = EBUSY;
		goto out;
	}

	/*
	 * Before we can perform any checks, we must prime all of the
	 * retained enablings that correspond to this state.
	 */
	dtrace_enabling_prime(state);

	if (state->dts_destructive && !state->dts_cred.dcr_destructive) {
		rval = EACCES;
		goto out;
	}

	dtrace_state_prereserve(state);

	/*
	 * Now we want to do is try to allocate our speculations.
	 * We do not automatically resize the number of speculations; if
	 * this fails, we will fail the operation.
	 */
	nspec = opt[DTRACEOPT_NSPEC];
	ASSERT(nspec != DTRACEOPT_UNSET);

	if (nspec > INT_MAX) {
		rval = ENOMEM;
		goto out;
	}

	spec = kmem_zalloc(nspec * sizeof (dtrace_speculation_t),
	    KM_NOSLEEP | KM_NORMALPRI);

	if (spec == NULL) {
		rval = ENOMEM;
		goto out;
	}

	state->dts_speculations = spec;
	state->dts_nspeculations = (int)nspec;

	for (i = 0; i < nspec; i++) {
		if ((buf = kmem_zalloc(bufsize,
		    KM_NOSLEEP | KM_NORMALPRI)) == NULL) {
			rval = ENOMEM;
			goto err;
		}

		spec[i].dtsp_buffer = buf;
	}

	if (opt[DTRACEOPT_GRABANON] != DTRACEOPT_UNSET) {
		if (dtrace_anon.dta_state == NULL) {
			rval = ENOENT;
			goto out;
		}

		if (state->dts_necbs != 0) {
			rval = EALREADY;
			goto out;
		}

		state->dts_anon = dtrace_anon_grab();
		ASSERT(state->dts_anon != NULL);
		state = state->dts_anon;

		/*
		 * We want "grabanon" to be set in the grabbed state, so we'll
		 * copy that option value from the grabbing state into the
		 * grabbed state.
		 */
		state->dts_options[DTRACEOPT_GRABANON] =
		    opt[DTRACEOPT_GRABANON];

		*cpu = dtrace_anon.dta_beganon;

		/*
		 * If the anonymous state is active (as it almost certainly
		 * is if the anonymous enabling ultimately matched anything),
		 * we don't allow any further option processing -- but we
		 * don't return failure.
		 */
		if (state->dts_activity != DTRACE_ACTIVITY_INACTIVE)
			goto out;
	}

	if (opt[DTRACEOPT_AGGSIZE] != DTRACEOPT_UNSET &&
	    opt[DTRACEOPT_AGGSIZE] != 0) {
		if (state->dts_aggregations == NULL) {
			/*
			 * We're not going to create an aggregation buffer
			 * because we don't have any ECBs that contain
			 * aggregations -- set this option to 0.
			 */
			opt[DTRACEOPT_AGGSIZE] = 0;
		} else {
			/*
			 * If we have an aggregation buffer, we must also have
			 * a buffer to use as scratch.
			 */
			if (opt[DTRACEOPT_BUFSIZE] == DTRACEOPT_UNSET ||
			    opt[DTRACEOPT_BUFSIZE] < state->dts_needed) {
				opt[DTRACEOPT_BUFSIZE] = state->dts_needed;
			}
		}
	}

	if (opt[DTRACEOPT_SPECSIZE] != DTRACEOPT_UNSET &&
	    opt[DTRACEOPT_SPECSIZE] != 0) {
		if (!state->dts_speculates) {
			/*
			 * We're not going to create speculation buffers
			 * because we don't have any ECBs that actually
			 * speculate -- set the speculation size to 0.
			 */
			opt[DTRACEOPT_SPECSIZE] = 0;
		}
	}

	/*
	 * The bare minimum size for any buffer that we're actually going to
	 * do anything to is sizeof (uint64_t).
	 */
	sz = sizeof (uint64_t);

	if ((state->dts_needed != 0 && opt[DTRACEOPT_BUFSIZE] < sz) ||
	    (state->dts_speculates && opt[DTRACEOPT_SPECSIZE] < sz) ||
	    (state->dts_aggregations != NULL && opt[DTRACEOPT_AGGSIZE] < sz)) {
		/*
		 * A buffer size has been explicitly set to 0 (or to a size
		 * that will be adjusted to 0) and we need the space -- we
		 * need to return failure.  We return ENOSPC to differentiate
		 * it from failing to allocate a buffer due to failure to meet
		 * the reserve (for which we return E2BIG).
		 */
		rval = ENOSPC;
		goto out;
	}

	if ((rval = dtrace_state_buffers(state)) != 0)
		goto err;

	if ((sz = opt[DTRACEOPT_DYNVARSIZE]) == DTRACEOPT_UNSET)
		sz = dtrace_dstate_defsize;

	do {
		rval = dtrace_dstate_init(&state->dts_vstate.dtvs_dynvars, sz);

		if (rval == 0)
			break;

		if (opt[DTRACEOPT_BUFRESIZE] == DTRACEOPT_BUFRESIZE_MANUAL)
			goto err;
	} while (sz >>= 1);

	opt[DTRACEOPT_DYNVARSIZE] = sz;

	if (rval != 0)
		goto err;

	if (opt[DTRACEOPT_STATUSRATE] > dtrace_statusrate_max)
		opt[DTRACEOPT_STATUSRATE] = dtrace_statusrate_max;

	if (opt[DTRACEOPT_CLEANRATE] == 0)
		opt[DTRACEOPT_CLEANRATE] = dtrace_cleanrate_max;

	if (opt[DTRACEOPT_CLEANRATE] < dtrace_cleanrate_min)
		opt[DTRACEOPT_CLEANRATE] = dtrace_cleanrate_min;

	if (opt[DTRACEOPT_CLEANRATE] > dtrace_cleanrate_max)
		opt[DTRACEOPT_CLEANRATE] = dtrace_cleanrate_max;

	state->dts_alive = state->dts_laststatus = dtrace_gethrtime();
#ifdef illumos
	hdlr.cyh_func = (cyc_func_t)dtrace_state_clean;
	hdlr.cyh_arg = state;
	hdlr.cyh_level = CY_LOW_LEVEL;

	when.cyt_when = 0;
	when.cyt_interval = opt[DTRACEOPT_CLEANRATE];

	state->dts_cleaner = cyclic_add(&hdlr, &when);

	hdlr.cyh_func = (cyc_func_t)dtrace_state_deadman;
	hdlr.cyh_arg = state;
	hdlr.cyh_level = CY_LOW_LEVEL;

	when.cyt_when = 0;
	when.cyt_interval = dtrace_deadman_interval;

	state->dts_deadman = cyclic_add(&hdlr, &when);
#else
	callout_reset(&state->dts_cleaner, hz * opt[DTRACEOPT_CLEANRATE] / NANOSEC,
	    dtrace_state_clean, state);
	callout_reset(&state->dts_deadman, hz * dtrace_deadman_interval / NANOSEC,
	    dtrace_state_deadman, state);
#endif

	state->dts_activity = DTRACE_ACTIVITY_WARMUP;

#ifdef illumos
	if (state->dts_getf != 0 &&
	    !(state->dts_cred.dcr_visible & DTRACE_CRV_KERNEL)) {
		/*
		 * We don't have kernel privs but we have at least one call
		 * to getf(); we need to bump our zone's count, and (if
		 * this is the first enabling to have an unprivileged call
		 * to getf()) we need to hook into closef().
		 */
		state->dts_cred.dcr_cred->cr_zone->zone_dtrace_getf++;

		if (dtrace_getf++ == 0) {
			ASSERT(dtrace_closef == NULL);
			dtrace_closef = dtrace_getf_barrier;
		}
	}
#endif

	/*
	 * Now it's time to actually fire the BEGIN probe.  We need to disable
	 * interrupts here both to record the CPU on which we fired the BEGIN
	 * probe (the data from this CPU will be processed first at user
	 * level) and to manually activate the buffer for this CPU.
	 */
	cookie = dtrace_interrupt_disable();
	*cpu = curcpu;
	ASSERT(state->dts_buffer[*cpu].dtb_flags & DTRACEBUF_INACTIVE);
	state->dts_buffer[*cpu].dtb_flags &= ~DTRACEBUF_INACTIVE;

	dtrace_probe(dtrace_probeid_begin,
	    (uint64_t)(uintptr_t)state, 0, 0, 0, 0);
	dtrace_interrupt_enable(cookie);
	/*
	 * We may have had an exit action from a BEGIN probe; only change our
	 * state to ACTIVE if we're still in WARMUP.
	 */
	ASSERT(state->dts_activity == DTRACE_ACTIVITY_WARMUP ||
	    state->dts_activity == DTRACE_ACTIVITY_DRAINING);

	if (state->dts_activity == DTRACE_ACTIVITY_WARMUP)
		state->dts_activity = DTRACE_ACTIVITY_ACTIVE;

#ifdef __FreeBSD__
	/*
	 * We enable anonymous tracing before APs are started, so we must
	 * activate buffers using the current CPU.
	 */
	if (state == dtrace_anon.dta_state)
		for (int i = 0; i < NCPU; i++)
			dtrace_buffer_activate_cpu(state, i);
	else
		dtrace_xcall(DTRACE_CPUALL,
		    (dtrace_xcall_t)dtrace_buffer_activate, state);
#else
	/*
	 * Regardless of whether or not now we're in ACTIVE or DRAINING, we
	 * want each CPU to transition its principal buffer out of the
	 * INACTIVE state.  Doing this assures that no CPU will suddenly begin
	 * processing an ECB halfway down a probe's ECB chain; all CPUs will
	 * atomically transition from processing none of a state's ECBs to
	 * processing all of them.
	 */
	dtrace_xcall(DTRACE_CPUALL,
	    (dtrace_xcall_t)dtrace_buffer_activate, state);
#endif
	goto out;

err:
	dtrace_buffer_free(state->dts_buffer);
	dtrace_buffer_free(state->dts_aggbuffer);

	if ((nspec = state->dts_nspeculations) == 0) {
		ASSERT(state->dts_speculations == NULL);
		goto out;
	}

	spec = state->dts_speculations;
	ASSERT(spec != NULL);

	for (i = 0; i < state->dts_nspeculations; i++) {
		if ((buf = spec[i].dtsp_buffer) == NULL)
			break;

		dtrace_buffer_free(buf);
		kmem_free(buf, bufsize);
	}

	kmem_free(spec, nspec * sizeof (dtrace_speculation_t));
	state->dts_nspeculations = 0;
	state->dts_speculations = NULL;

out:
	mutex_exit(&dtrace_lock);
	mutex_exit(&cpu_lock);

	return (rval);
}