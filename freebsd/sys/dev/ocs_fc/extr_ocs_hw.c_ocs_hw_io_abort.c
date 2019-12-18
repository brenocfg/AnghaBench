#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  sli4_abort_type_e ;
struct TYPE_20__ {int /*<<< orphan*/  wqe_size; } ;
struct TYPE_24__ {TYPE_1__ config; } ;
struct TYPE_21__ {int /*<<< orphan*/  io_abort_lock; int /*<<< orphan*/ * os; TYPE_5__ sli; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
struct TYPE_19__ {int abort_wqe_submit_needed; int /*<<< orphan*/  wqebuf; int /*<<< orphan*/  abort_reqtag; void* id; void* send_abts; int /*<<< orphan*/  link; } ;
struct TYPE_22__ {int abort_in_progress; int /*<<< orphan*/  ref; TYPE_17__ wqe; TYPE_11__* wq; int /*<<< orphan*/  abort_reqtag; void* indicator; void* abort_arg; void* abort_done; int /*<<< orphan*/  reqtag; } ;
typedef  TYPE_3__ ocs_hw_io_t ;
struct TYPE_23__ {int /*<<< orphan*/  instance_index; } ;
typedef  TYPE_4__ hw_wq_callback_t ;
struct TYPE_18__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 scalar_t__ OCS_HW_RTN_ERROR ; 
 scalar_t__ OCS_HW_RTN_IO_ABORT_IN_PROGRESS ; 
 scalar_t__ OCS_HW_RTN_IO_NOT_ACTIVE ; 
 scalar_t__ OCS_HW_RTN_NO_RESOURCES ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_HW_STATE_ACTIVE ; 
 int /*<<< orphan*/  SLI4_CQ_DEFAULT ; 
 int /*<<< orphan*/  SLI_ABORT_MAX ; 
 int /*<<< orphan*/  SLI_ABORT_XRI ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 scalar_t__ hw_wq_write (TYPE_11__*,TYPE_17__*) ; 
 int /*<<< orphan*/  ocs_hw_assert (int /*<<< orphan*/ ) ; 
 TYPE_11__* ocs_hw_queue_next_wq (TYPE_2__*,TYPE_3__*) ; 
 TYPE_4__* ocs_hw_reqtag_alloc (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_hw_reqtag_free (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_hw_wq_process_abort ; 
 scalar_t__ ocs_list_on_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ *,char*,void*,...) ; 
 scalar_t__ ocs_ref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_abort_wqe (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_queue_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_queue_unlock (int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_io_abort(ocs_hw_t *hw, ocs_hw_io_t *io_to_abort, uint32_t send_abts, void *cb, void *arg)
{
	sli4_abort_type_e atype = SLI_ABORT_MAX;
	uint32_t	id = 0, mask = 0;
	ocs_hw_rtn_e	rc = OCS_HW_RTN_SUCCESS;
	hw_wq_callback_t *wqcb;

	if (!hw || !io_to_abort) {
		ocs_log_err(hw ? hw->os : NULL,
			    "bad parameter hw=%p io=%p\n",
			    hw, io_to_abort);
		return OCS_HW_RTN_ERROR;
	}

	if (hw->state != OCS_HW_STATE_ACTIVE) {
		ocs_log_err(hw->os, "cannot send IO abort, HW state=%d\n",
			    hw->state);
		return OCS_HW_RTN_ERROR;
	}

	/* take a reference on IO being aborted */
	if (ocs_ref_get_unless_zero(&io_to_abort->ref) == 0) {
		/* command no longer active */
		ocs_log_test(hw ? hw->os : NULL,
				"io not active xri=0x%x tag=0x%x\n",
				io_to_abort->indicator, io_to_abort->reqtag);
		return OCS_HW_RTN_IO_NOT_ACTIVE;
	}

	/* non-port owned XRI checks */
	/* Must have a valid WQ reference */
	if (io_to_abort->wq == NULL) {
		ocs_log_test(hw->os, "io_to_abort xri=0x%x not active on WQ\n",
				io_to_abort->indicator);
		ocs_ref_put(&io_to_abort->ref); /* ocs_ref_get(): same function */
		return OCS_HW_RTN_IO_NOT_ACTIVE;
	}

	/* Validation checks complete; now check to see if already being aborted */
	ocs_lock(&hw->io_abort_lock);
		if (io_to_abort->abort_in_progress) {
			ocs_unlock(&hw->io_abort_lock);
			ocs_ref_put(&io_to_abort->ref); /* ocs_ref_get(): same function */
			ocs_log_debug(hw ? hw->os : NULL,
				"io already being aborted xri=0x%x tag=0x%x\n",
				io_to_abort->indicator, io_to_abort->reqtag);
			return OCS_HW_RTN_IO_ABORT_IN_PROGRESS;
		}

		/*
		 * This IO is not already being aborted. Set flag so we won't try to
		 * abort it again. After all, we only have one abort_done callback.
		 */
		io_to_abort->abort_in_progress = 1;
	ocs_unlock(&hw->io_abort_lock);

	/*
	 * If we got here, the possibilities are:
	 * - host owned xri
	 *	- io_to_abort->wq_index != UINT32_MAX
	 *		- submit ABORT_WQE to same WQ
	 * - port owned xri:
	 *	- rxri: io_to_abort->wq_index == UINT32_MAX
	 *		- submit ABORT_WQE to any WQ
	 *	- non-rxri
	 *		- io_to_abort->index != UINT32_MAX
	 *			- submit ABORT_WQE to same WQ
	 *		- io_to_abort->index == UINT32_MAX
	 *			- submit ABORT_WQE to any WQ
	 */
	io_to_abort->abort_done = cb;
	io_to_abort->abort_arg  = arg;

	atype = SLI_ABORT_XRI;
	id = io_to_abort->indicator;

	/* Allocate a request tag for the abort portion of this IO */
	wqcb = ocs_hw_reqtag_alloc(hw, ocs_hw_wq_process_abort, io_to_abort);
	if (wqcb == NULL) {
		ocs_log_err(hw->os, "can't allocate request tag\n");
		return OCS_HW_RTN_NO_RESOURCES;
	}
	io_to_abort->abort_reqtag = wqcb->instance_index;

	/*
	 * If the wqe is on the pending list, then set this wqe to be
	 * aborted when the IO's wqe is removed from the list.
	 */
	if (io_to_abort->wq != NULL) {
		sli_queue_lock(io_to_abort->wq->queue);
			if (ocs_list_on_list(&io_to_abort->wqe.link)) {
				io_to_abort->wqe.abort_wqe_submit_needed = 1;
				io_to_abort->wqe.send_abts = send_abts;
				io_to_abort->wqe.id = id;
				io_to_abort->wqe.abort_reqtag = io_to_abort->abort_reqtag;
				sli_queue_unlock(io_to_abort->wq->queue);
				return 0;
		}
		sli_queue_unlock(io_to_abort->wq->queue);
	}

	if (sli_abort_wqe(&hw->sli, io_to_abort->wqe.wqebuf, hw->sli.config.wqe_size, atype, send_abts, id, mask,
			  io_to_abort->abort_reqtag, SLI4_CQ_DEFAULT)) {
		ocs_log_err(hw->os, "ABORT WQE error\n");
		io_to_abort->abort_reqtag = UINT32_MAX;
		ocs_hw_reqtag_free(hw, wqcb);
		rc = OCS_HW_RTN_ERROR;
	}

	if (OCS_HW_RTN_SUCCESS == rc) {
		if (io_to_abort->wq == NULL) {
			io_to_abort->wq = ocs_hw_queue_next_wq(hw, io_to_abort);
			ocs_hw_assert(io_to_abort->wq != NULL);
		}
		/* ABORT_WQE does not actually utilize an XRI on the Port,
		 * therefore, keep xbusy as-is to track the exchange's state,
		 * not the ABORT_WQE's state
		 */
		rc = hw_wq_write(io_to_abort->wq, &io_to_abort->wqe);
		if (rc > 0) {
			/* non-negative return is success */
			rc = 0;
			/* can't abort an abort so skip adding to timed wqe list */
		}
	}

	if (OCS_HW_RTN_SUCCESS != rc) {
		ocs_lock(&hw->io_abort_lock);
			io_to_abort->abort_in_progress = 0;
		ocs_unlock(&hw->io_abort_lock);
		ocs_ref_put(&io_to_abort->ref); /* ocs_ref_get(): same function */
	}
	return rc;
}