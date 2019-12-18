#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hrtime_t ;
struct TYPE_8__ {scalar_t__ dts_speculates; int /*<<< orphan*/ * dts_aggbuffer; int /*<<< orphan*/ * dts_buffer; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  dtpv_defunct; } ;
typedef  TYPE_2__ dtrace_provider_t ;
struct TYPE_10__ {TYPE_4__* dtpr_ecb; TYPE_2__* dtpr_provider; } ;
typedef  TYPE_3__ dtrace_probe_t ;
struct TYPE_11__ {TYPE_1__* dte_state; } ;
typedef  TYPE_4__ dtrace_ecb_t ;
typedef  int /*<<< orphan*/  dtrace_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  cpu_lock ; 
 int /*<<< orphan*/  dtrace_buffer_consumed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_ecb_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_ecb_disable (TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int dtrace_nprobes ; 
 TYPE_3__** dtrace_probes ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_enabling_reap(void)
{
	dtrace_provider_t *prov;
	dtrace_probe_t *probe;
	dtrace_ecb_t *ecb;
	hrtime_t when;
	int i;

	mutex_enter(&cpu_lock);
	mutex_enter(&dtrace_lock);

	for (i = 0; i < dtrace_nprobes; i++) {
		if ((probe = dtrace_probes[i]) == NULL)
			continue;

		if (probe->dtpr_ecb == NULL)
			continue;

		prov = probe->dtpr_provider;

		if ((when = prov->dtpv_defunct) == 0)
			continue;

		/*
		 * We have ECBs on a defunct provider:  we want to reap these
		 * ECBs to allow the provider to unregister.  The destruction
		 * of these ECBs must be done carefully:  if we destroy the ECB
		 * and the consumer later wishes to consume an EPID that
		 * corresponds to the destroyed ECB (and if the EPID metadata
		 * has not been previously consumed), the consumer will abort
		 * processing on the unknown EPID.  To reduce (but not, sadly,
		 * eliminate) the possibility of this, we will only destroy an
		 * ECB for a defunct provider if, for the state that
		 * corresponds to the ECB:
		 *
		 *  (a)	There is no speculative tracing (which can effectively
		 *	cache an EPID for an arbitrary amount of time).
		 *
		 *  (b)	The principal buffers have been switched twice since the
		 *	provider became defunct.
		 *
		 *  (c)	The aggregation buffers are of zero size or have been
		 *	switched twice since the provider became defunct.
		 *
		 * We use dts_speculates to determine (a) and call a function
		 * (dtrace_buffer_consumed()) to determine (b) and (c).  Note
		 * that as soon as we've been unable to destroy one of the ECBs
		 * associated with the probe, we quit trying -- reaping is only
		 * fruitful in as much as we can destroy all ECBs associated
		 * with the defunct provider's probes.
		 */
		while ((ecb = probe->dtpr_ecb) != NULL) {
			dtrace_state_t *state = ecb->dte_state;
			dtrace_buffer_t *buf = state->dts_buffer;
			dtrace_buffer_t *aggbuf = state->dts_aggbuffer;

			if (state->dts_speculates)
				break;

			if (!dtrace_buffer_consumed(buf, when))
				break;

			if (!dtrace_buffer_consumed(aggbuf, when))
				break;

			dtrace_ecb_disable(ecb);
			ASSERT(probe->dtpr_ecb != ecb);
			dtrace_ecb_destroy(ecb);
		}
	}

	mutex_exit(&dtrace_lock);
	mutex_exit(&cpu_lock);
}