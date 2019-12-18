#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct drr_freeobjects {scalar_t__ drr_firstobj; scalar_t__ drr_numobjs; int /*<<< orphan*/  drr_toguid; } ;
struct TYPE_7__ {scalar_t__ dsa_pending_op; int /*<<< orphan*/  dsa_toguid; TYPE_5__* dsa_drr; } ;
typedef  TYPE_2__ dmu_sendarg_t ;
typedef  int /*<<< orphan*/  dmu_replay_record_t ;
struct TYPE_6__ {struct drr_freeobjects drr_freeobjects; } ;
struct TYPE_8__ {int /*<<< orphan*/  drr_type; TYPE_1__ drr_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRR_FREEOBJECTS ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ PENDING_FREEOBJECTS ; 
 scalar_t__ PENDING_NONE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 scalar_t__ dump_record (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_freeobjects(dmu_sendarg_t *dsp, uint64_t firstobj, uint64_t numobjs)
{
	struct drr_freeobjects *drrfo = &(dsp->dsa_drr->drr_u.drr_freeobjects);

	/*
	 * If there is a pending op, but it's not PENDING_FREEOBJECTS,
	 * push it out, since free block aggregation can only be done for
	 * blocks of the same type (i.e., DRR_FREE records can only be
	 * aggregated with other DRR_FREE records.  DRR_FREEOBJECTS records
	 * can only be aggregated with other DRR_FREEOBJECTS records.
	 */
	if (dsp->dsa_pending_op != PENDING_NONE &&
	    dsp->dsa_pending_op != PENDING_FREEOBJECTS) {
		if (dump_record(dsp, NULL, 0) != 0)
			return (SET_ERROR(EINTR));
		dsp->dsa_pending_op = PENDING_NONE;
	}
	if (dsp->dsa_pending_op == PENDING_FREEOBJECTS) {
		/*
		 * See whether this free object array can be aggregated
		 * with pending one
		 */
		if (drrfo->drr_firstobj + drrfo->drr_numobjs == firstobj) {
			drrfo->drr_numobjs += numobjs;
			return (0);
		} else {
			/* can't be aggregated.  Push out pending record */
			if (dump_record(dsp, NULL, 0) != 0)
				return (SET_ERROR(EINTR));
			dsp->dsa_pending_op = PENDING_NONE;
		}
	}

	/* write a FREEOBJECTS record */
	bzero(dsp->dsa_drr, sizeof (dmu_replay_record_t));
	dsp->dsa_drr->drr_type = DRR_FREEOBJECTS;
	drrfo->drr_firstobj = firstobj;
	drrfo->drr_numobjs = numobjs;
	drrfo->drr_toguid = dsp->dsa_toguid;

	dsp->dsa_pending_op = PENDING_FREEOBJECTS;

	return (0);
}