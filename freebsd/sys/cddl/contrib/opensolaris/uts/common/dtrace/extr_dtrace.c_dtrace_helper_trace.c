#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int dtvs_nlocals; TYPE_2__** dtvs_locals; } ;
typedef  TYPE_1__ dtrace_vstate_t ;
struct TYPE_10__ {int dtsv_size; scalar_t__ dtsv_data; } ;
typedef  TYPE_2__ dtrace_statvar_t ;
struct TYPE_11__ {int dtms_present; int dtms_fltoffs; } ;
typedef  TYPE_3__ dtrace_mstate_t ;
struct TYPE_12__ {int dtht_where; int dtht_nlocals; int dtht_fltoffs; int /*<<< orphan*/ * dtht_locals; int /*<<< orphan*/  dtht_illval; int /*<<< orphan*/  dtht_fault; int /*<<< orphan*/ * dtht_helper; } ;
typedef  TYPE_4__ dtrace_helptrace_t ;
typedef  int /*<<< orphan*/  dtrace_helper_action_t ;
struct TYPE_13__ {int /*<<< orphan*/  cpuc_dtrace_illval; int /*<<< orphan*/  cpuc_dtrace_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_FLAGS2FLT (int /*<<< orphan*/ ) ; 
 int DTRACE_MSTATE_FLTOFFS ; 
 int NCPU ; 
 TYPE_8__* cpu_core ; 
 size_t curcpu ; 
 scalar_t__ dtrace_cas32 (scalar_t__*,scalar_t__,scalar_t__) ; 
 TYPE_4__* dtrace_helptrace_buffer ; 
 scalar_t__ dtrace_helptrace_bufsize ; 
 scalar_t__ dtrace_helptrace_next ; 
 int dtrace_helptrace_nlocals ; 
 int /*<<< orphan*/  dtrace_helptrace_wrapped ; 

__attribute__((used)) static void
dtrace_helper_trace(dtrace_helper_action_t *helper,
    dtrace_mstate_t *mstate, dtrace_vstate_t *vstate, int where)
{
	uint32_t size, next, nnext, i;
	dtrace_helptrace_t *ent, *buffer;
	uint16_t flags = cpu_core[curcpu].cpuc_dtrace_flags;

	if ((buffer = dtrace_helptrace_buffer) == NULL)
		return;

	ASSERT(vstate->dtvs_nlocals <= dtrace_helptrace_nlocals);

	/*
	 * What would a tracing framework be without its own tracing
	 * framework?  (Well, a hell of a lot simpler, for starters...)
	 */
	size = sizeof (dtrace_helptrace_t) + dtrace_helptrace_nlocals *
	    sizeof (uint64_t) - sizeof (uint64_t);

	/*
	 * Iterate until we can allocate a slot in the trace buffer.
	 */
	do {
		next = dtrace_helptrace_next;

		if (next + size < dtrace_helptrace_bufsize) {
			nnext = next + size;
		} else {
			nnext = size;
		}
	} while (dtrace_cas32(&dtrace_helptrace_next, next, nnext) != next);

	/*
	 * We have our slot; fill it in.
	 */
	if (nnext == size) {
		dtrace_helptrace_wrapped++;
		next = 0;
	}

	ent = (dtrace_helptrace_t *)((uintptr_t)buffer + next);
	ent->dtht_helper = helper;
	ent->dtht_where = where;
	ent->dtht_nlocals = vstate->dtvs_nlocals;

	ent->dtht_fltoffs = (mstate->dtms_present & DTRACE_MSTATE_FLTOFFS) ?
	    mstate->dtms_fltoffs : -1;
	ent->dtht_fault = DTRACE_FLAGS2FLT(flags);
	ent->dtht_illval = cpu_core[curcpu].cpuc_dtrace_illval;

	for (i = 0; i < vstate->dtvs_nlocals; i++) {
		dtrace_statvar_t *svar;

		if ((svar = vstate->dtvs_locals[i]) == NULL)
			continue;

		ASSERT(svar->dtsv_size >= NCPU * sizeof (uint64_t));
		ent->dtht_locals[i] =
		    ((uint64_t *)(uintptr_t)svar->dtsv_data)[curcpu];
	}
}