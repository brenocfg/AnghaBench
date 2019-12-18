#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  wqe_size; } ;
struct TYPE_20__ {TYPE_1__ config; } ;
struct TYPE_18__ {int /*<<< orphan*/  os; int /*<<< orphan*/ * tcmd_wq_submit; int /*<<< orphan*/  io_port_dnrx; int /*<<< orphan*/  auto_xfer_rdy_buf_pool; TYPE_4__ sli; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_16__ {int /*<<< orphan*/  wqebuf; } ;
struct TYPE_19__ {TYPE_14__ wqe; TYPE_10__* wq; int /*<<< orphan*/ * axr_buf; int /*<<< orphan*/  indicator; int /*<<< orphan*/  type; scalar_t__ auto_xfer_rdy_dnrx; } ;
typedef  TYPE_3__ ocs_hw_io_t ;
typedef  int int32_t ;
struct TYPE_15__ {size_t instance; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_IO_DNRX_REQUEUE ; 
 int /*<<< orphan*/  OCS_HW_REQUE_XRI_REGTAG ; 
 int /*<<< orphan*/  OCS_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLI4_CQ_DEFAULT ; 
 int hw_wq_write (TYPE_10__*,TYPE_14__*) ; 
 int /*<<< orphan*/  ocs_hw_assert (int /*<<< orphan*/ ) ; 
 TYPE_10__* ocs_hw_queue_next_wq (TYPE_2__*,TYPE_3__*) ; 
 int ocs_hw_rqpair_auto_xfer_rdy_buffer_post (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_pool_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sli_requeue_xri_wqe (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t 
ocs_hw_reque_xri( ocs_hw_t *hw, ocs_hw_io_t *io )
{
	int32_t rc = 0;

	rc = ocs_hw_rqpair_auto_xfer_rdy_buffer_post(hw, io, 1);
	if (rc) {
		ocs_list_add_tail(&hw->io_port_dnrx, io);
		rc = -1;
		goto exit_ocs_hw_reque_xri;
	}

	io->auto_xfer_rdy_dnrx = 0;
	io->type = OCS_HW_IO_DNRX_REQUEUE;
	if (sli_requeue_xri_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, io->indicator, OCS_HW_REQUE_XRI_REGTAG, SLI4_CQ_DEFAULT)) {
		/* Clear buffer from XRI */
		ocs_pool_put(hw->auto_xfer_rdy_buf_pool, io->axr_buf);
		io->axr_buf = NULL;

		ocs_log_err(hw->os, "requeue_xri WQE error\n");
		ocs_list_add_tail(&hw->io_port_dnrx, io);

		rc = -1;
		goto exit_ocs_hw_reque_xri;
	}

	if (io->wq == NULL) {
		io->wq = ocs_hw_queue_next_wq(hw, io);
		ocs_hw_assert(io->wq != NULL);
	}

	/*
	 * Add IO to active io wqe list before submitting, in case the
	 * wcqe processing preempts this thread.
	 */
	OCS_STAT(hw->tcmd_wq_submit[io->wq->instance]++);
	OCS_STAT(io->wq->use_count++);
	
	rc = hw_wq_write(io->wq, &io->wqe);
	if (rc < 0) {
		ocs_log_err(hw->os, "sli_queue_write reque xri failed: %d\n", rc);
		rc = -1;
	}

exit_ocs_hw_reque_xri:
	return 0;
}