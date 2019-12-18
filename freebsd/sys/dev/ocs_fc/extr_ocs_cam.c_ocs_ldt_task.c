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
struct TYPE_7__ {scalar_t__ attached; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_8__ {int /*<<< orphan*/  ldt; TYPE_3__* tgt; TYPE_1__* ocs; } ;
typedef  TYPE_2__ ocs_fcport ;
struct TYPE_9__ {scalar_t__ state; scalar_t__ gone_timer; scalar_t__ is_target; } ;
typedef  TYPE_3__ ocs_fc_target_t ;

/* Variables and functions */
 int OCS_MAX_TARGETS ; 
 scalar_t__ OCS_TGT_STATE_LOST ; 
 scalar_t__ OCS_TGT_STATE_NONE ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ocs_delete_target (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_ldt ; 

__attribute__((used)) static void
ocs_ldt_task(void *arg, int pending)
{
	ocs_fcport *fcp = arg;
	ocs_t	*ocs = fcp->ocs;
	int i, more_to_do = 0;
	ocs_fc_target_t *tgt = NULL;

	for (i = 0; i < OCS_MAX_TARGETS; i++) {
		tgt = &fcp->tgt[i];

		if (tgt->state != OCS_TGT_STATE_LOST) {
			continue;
		}

		if ((tgt->gone_timer != 0) && (ocs->attached)){
			tgt->gone_timer -= 1;
			more_to_do++;
			continue;
		}

		if (tgt->is_target) {
			tgt->is_target = 0;
			ocs_delete_target(ocs, fcp, i);
		}

		tgt->state = OCS_TGT_STATE_NONE;
	}

	if (more_to_do) {
		callout_reset(&fcp->ldt, hz, ocs_ldt, fcp);
	} else {
		callout_deactivate(&fcp->ldt);
	}

}