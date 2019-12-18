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
typedef  int /*<<< orphan*/  dtrace_state_t ;
struct TYPE_8__ {scalar_t__ dtpr_gen; } ;
typedef  TYPE_2__ dtrace_probe_t ;
struct TYPE_9__ {scalar_t__ dten_probegen; TYPE_1__* dten_vstate; } ;
typedef  TYPE_3__ dtrace_enabling_t ;
typedef  int /*<<< orphan*/  dtrace_ecb_t ;
struct TYPE_7__ {int /*<<< orphan*/ * dtvs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int DTRACE_MATCH_DONE ; 
 int DTRACE_MATCH_NEXT ; 
 int /*<<< orphan*/ * dtrace_ecb_create (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dtrace_ecb_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_ecb_create_enable(dtrace_probe_t *probe, void *arg)
{
	dtrace_ecb_t *ecb;
	dtrace_enabling_t *enab = arg;
	dtrace_state_t *state = enab->dten_vstate->dtvs_state;

	ASSERT(state != NULL);

	if (probe != NULL && probe->dtpr_gen < enab->dten_probegen) {
		/*
		 * This probe was created in a generation for which this
		 * enabling has previously created ECBs; we don't want to
		 * enable it again, so just kick out.
		 */
		return (DTRACE_MATCH_NEXT);
	}

	if ((ecb = dtrace_ecb_create(state, probe, enab)) == NULL)
		return (DTRACE_MATCH_DONE);

	dtrace_ecb_enable(ecb);
	return (DTRACE_MATCH_NEXT);
}