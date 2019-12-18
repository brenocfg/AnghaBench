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
typedef  int /*<<< orphan*/  uint64_t ;
struct drr_spill {int drr_length; int /*<<< orphan*/  drr_toguid; int /*<<< orphan*/  drr_object; } ;
struct TYPE_7__ {scalar_t__ dsa_pending_op; int /*<<< orphan*/  dsa_toguid; TYPE_5__* dsa_drr; } ;
typedef  TYPE_2__ dmu_sendarg_t ;
typedef  int /*<<< orphan*/  dmu_replay_record_t ;
struct TYPE_6__ {struct drr_spill drr_spill; } ;
struct TYPE_8__ {int /*<<< orphan*/  drr_type; TYPE_1__ drr_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRR_SPILL ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ PENDING_NONE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_5__*,int) ; 
 scalar_t__ dump_record (TYPE_2__*,void*,int) ; 

__attribute__((used)) static int
dump_spill(dmu_sendarg_t *dsp, uint64_t object, int blksz, void *data)
{
	struct drr_spill *drrs = &(dsp->dsa_drr->drr_u.drr_spill);

	if (dsp->dsa_pending_op != PENDING_NONE) {
		if (dump_record(dsp, NULL, 0) != 0)
			return (SET_ERROR(EINTR));
		dsp->dsa_pending_op = PENDING_NONE;
	}

	/* write a SPILL record */
	bzero(dsp->dsa_drr, sizeof (dmu_replay_record_t));
	dsp->dsa_drr->drr_type = DRR_SPILL;
	drrs->drr_object = object;
	drrs->drr_length = blksz;
	drrs->drr_toguid = dsp->dsa_toguid;

	if (dump_record(dsp, data, blksz) != 0)
		return (SET_ERROR(EINTR));
	return (0);
}