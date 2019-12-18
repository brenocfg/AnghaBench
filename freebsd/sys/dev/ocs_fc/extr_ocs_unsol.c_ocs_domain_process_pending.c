#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_15__ {scalar_t__ pend_frames_processed; int /*<<< orphan*/  pend_frames_lock; int /*<<< orphan*/  pend_frames; } ;
typedef  TYPE_2__ ocs_xport_fcfi_t ;
struct TYPE_16__ {int /*<<< orphan*/  hw; TYPE_1__* xport; } ;
typedef  TYPE_3__ ocs_t ;
struct TYPE_17__ {int /*<<< orphan*/ * hio; } ;
typedef  TYPE_4__ ocs_hw_sequence_t ;
struct TYPE_18__ {size_t fcf_indicator; TYPE_3__* ocs; } ;
typedef  TYPE_5__ ocs_domain_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_14__ {TYPE_2__* fcfi; } ;

/* Variables and functions */
 size_t SLI4_MAX_FCFI ; 
 int /*<<< orphan*/  ocs_assert (int,int) ; 
 scalar_t__ ocs_domain_dispatch_frame (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ ocs_domain_frames_held (TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_hw_sequence_free (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_4__* ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_3__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_port_owned_abort (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

int32_t
ocs_domain_process_pending(ocs_domain_t *domain)
{
	ocs_t *ocs = domain->ocs;
	ocs_xport_fcfi_t *xport_fcfi;
	ocs_hw_sequence_t *seq = NULL;
	uint32_t pend_frames_processed = 0;

	ocs_assert(domain->fcf_indicator < SLI4_MAX_FCFI, -1);
	xport_fcfi = &ocs->xport->fcfi[domain->fcf_indicator];

	for (;;) {
		/* need to check for hold frames condition after each frame processed
		 * because any given frame could cause a transition to a state that
		 * holds frames
		 */
		if (ocs_domain_frames_held(domain)) {
			break;
		}

		/* Get next frame/sequence */
		ocs_lock(&xport_fcfi->pend_frames_lock);
			seq = ocs_list_remove_head(&xport_fcfi->pend_frames);
			if (seq == NULL) {
				pend_frames_processed = xport_fcfi->pend_frames_processed;
				xport_fcfi->pend_frames_processed = 0;
				ocs_unlock(&xport_fcfi->pend_frames_lock);
				break;
			}
			xport_fcfi->pend_frames_processed++;
		ocs_unlock(&xport_fcfi->pend_frames_lock);

		/* now dispatch frame(s) to dispatch function */
		if (ocs_domain_dispatch_frame(domain, seq)) {
			if (seq->hio != NULL) {
				ocs_port_owned_abort(ocs, seq->hio);
			}
			ocs_hw_sequence_free(&ocs->hw, seq);
		}
	}
	if (pend_frames_processed != 0) {
		ocs_log_debug(ocs, "%u domain frames held and processed\n", pend_frames_processed);
	}
	return 0;
}