#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* dts_options; scalar_t__ dts_reserve; } ;
typedef  TYPE_1__ dtrace_state_t ;
struct TYPE_7__ {TYPE_3__* dtpr_ecb; } ;
typedef  TYPE_2__ dtrace_probe_t ;
struct TYPE_8__ {scalar_t__ dte_alignment; scalar_t__ dte_needed; TYPE_1__* dte_state; struct TYPE_8__* dte_next; } ;
typedef  TYPE_3__ dtrace_ecb_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 size_t DTRACEOPT_BUFPOLICY ; 
 scalar_t__ DTRACEOPT_BUFPOLICY_FILL ; 
 int dtrace_probeid_end ; 
 TYPE_2__** dtrace_probes ; 

__attribute__((used)) static void
dtrace_state_prereserve(dtrace_state_t *state)
{
	dtrace_ecb_t *ecb;
	dtrace_probe_t *probe;

	state->dts_reserve = 0;

	if (state->dts_options[DTRACEOPT_BUFPOLICY] != DTRACEOPT_BUFPOLICY_FILL)
		return;

	/*
	 * If our buffer policy is a "fill" buffer policy, we need to set the
	 * prereserved space to be the space required by the END probes.
	 */
	probe = dtrace_probes[dtrace_probeid_end - 1];
	ASSERT(probe != NULL);

	for (ecb = probe->dtpr_ecb; ecb != NULL; ecb = ecb->dte_next) {
		if (ecb->dte_state != state)
			continue;

		state->dts_reserve += ecb->dte_needed + ecb->dte_alignment;
	}
}