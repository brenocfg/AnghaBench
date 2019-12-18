#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_19__ {int /*<<< orphan*/  pend_frames_lock; int /*<<< orphan*/  pend_frames; scalar_t__ hold_frames; } ;
typedef  TYPE_3__ ocs_xport_fcfi_t ;
struct TYPE_17__ {scalar_t__ override_fcfi; } ;
struct TYPE_16__ {int first_domain_idx; TYPE_1__ workaround; } ;
struct TYPE_20__ {TYPE_11__ hw; TYPE_2__* xport; } ;
typedef  TYPE_4__ ocs_t ;
struct TYPE_21__ {size_t fcfi; int /*<<< orphan*/ * hio; } ;
typedef  TYPE_5__ ocs_hw_sequence_t ;
typedef  int /*<<< orphan*/  ocs_domain_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_18__ {TYPE_3__* fcfi; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ ocs_domain_dispatch_frame (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_domain_process_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocs_hw_domain_get (TYPE_11__*,size_t) ; 
 int /*<<< orphan*/  ocs_hw_sequence_free (TYPE_11__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_4__*,char*,size_t) ; 
 int /*<<< orphan*/  ocs_port_owned_abort (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
ocs_unsol_process(ocs_t *ocs, ocs_hw_sequence_t *seq)
{
	ocs_xport_fcfi_t *xport_fcfi = NULL;
	ocs_domain_t *domain;
	uint8_t seq_fcfi = seq->fcfi;

	/* HW_WORKAROUND_OVERRIDE_FCFI_IN_SRB */
	if (ocs->hw.workaround.override_fcfi) {
		if (ocs->hw.first_domain_idx > -1) {
			seq_fcfi = ocs->hw.first_domain_idx;
		}
	}

	/* Range check seq->fcfi */
	if (seq_fcfi < ARRAY_SIZE(ocs->xport->fcfi)) {
		xport_fcfi = &ocs->xport->fcfi[seq_fcfi];
	}

	/* If the transport FCFI entry is NULL, then drop the frame */
	if (xport_fcfi == NULL) {
		ocs_log_test(ocs, "FCFI %d is not valid, dropping frame\n", seq->fcfi);
		if (seq->hio != NULL) {
			ocs_port_owned_abort(ocs, seq->hio);
		}

		ocs_hw_sequence_free(&ocs->hw, seq);
		return 0;
	}
	domain = ocs_hw_domain_get(&ocs->hw, seq_fcfi);

	/*
	 * If we are holding frames or the domain is not yet registered or
	 * there's already frames on the pending list,
	 * then add the new frame to pending list
	 */
	if (domain == NULL ||
	    xport_fcfi->hold_frames ||
	    !ocs_list_empty(&xport_fcfi->pend_frames)) {
		ocs_lock(&xport_fcfi->pend_frames_lock);
			ocs_list_add_tail(&xport_fcfi->pend_frames, seq);
		ocs_unlock(&xport_fcfi->pend_frames_lock);

		if (domain != NULL) {
			/* immediately process pending frames */
			ocs_domain_process_pending(domain);
		}
	} else {
		/*
		 * We are not holding frames and pending list is empty, just process frame.
		 * A non-zero return means the frame was not handled - so cleanup
		 */
		if (ocs_domain_dispatch_frame(domain, seq)) {
			if (seq->hio != NULL) {
				ocs_port_owned_abort(ocs, seq->hio);
			}
			ocs_hw_sequence_free(&ocs->hw, seq);
		}
	}
	return 0;
}