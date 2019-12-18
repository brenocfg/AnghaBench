#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_21__ {int /*<<< orphan*/  wqebuf; } ;
typedef  TYPE_3__ ocs_hw_wqe_t ;
struct TYPE_20__ {int /*<<< orphan*/  wqe_size; } ;
struct TYPE_26__ {TYPE_2__ config; } ;
struct TYPE_22__ {int /*<<< orphan*/  os; TYPE_8__ sli; TYPE_7__** hw_wq; int /*<<< orphan*/ * wq_class_array; } ;
typedef  TYPE_4__ ocs_hw_t ;
struct TYPE_23__ {TYPE_14__* wqcb; TYPE_4__* hw; TYPE_3__ wqe; } ;
typedef  TYPE_5__ ocs_hw_send_frame_context_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_24__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_6__ ocs_dma_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_25__ {int /*<<< orphan*/  use_count; TYPE_1__* send_frame_io; } ;
typedef  TYPE_7__ hw_wq_t ;
typedef  int /*<<< orphan*/  fc_header_le_t ;
struct TYPE_19__ {int /*<<< orphan*/  indicator; } ;
struct TYPE_18__ {int /*<<< orphan*/  instance_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_NO_RESOURCES ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_HW_SEND_FRAME_TIMEOUT ; 
 int /*<<< orphan*/  OCS_STAT (int /*<<< orphan*/ ) ; 
 scalar_t__ hw_wq_write (TYPE_7__*,TYPE_3__*) ; 
 TYPE_14__* ocs_hw_reqtag_alloc (TYPE_4__*,void (*) (void*,int /*<<< orphan*/ *,int32_t),void*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_7__* ocs_varray_iter_next (int /*<<< orphan*/ ) ; 
 scalar_t__ sli_send_frame_wqe (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_send_frame(ocs_hw_t *hw, fc_header_le_t *hdr, uint8_t sof, uint8_t eof, ocs_dma_t *payload,
		   ocs_hw_send_frame_context_t *ctx, void (*callback)(void *arg, uint8_t *cqe, int32_t status), void *arg)
{
	int32_t rc;
	ocs_hw_wqe_t *wqe;
	uint32_t xri;
	hw_wq_t *wq;

	wqe = &ctx->wqe;

	/* populate the callback object */
	ctx->hw = hw;

	/* Fetch and populate request tag */
	ctx->wqcb = ocs_hw_reqtag_alloc(hw, callback, arg);
	if (ctx->wqcb == NULL) {
		ocs_log_err(hw->os, "can't allocate request tag\n");
		return OCS_HW_RTN_NO_RESOURCES;
	}

	/* Choose a work queue, first look for a class[1] wq, otherwise just use wq[0] */
	wq = ocs_varray_iter_next(hw->wq_class_array[1]);
	if (wq == NULL) {
		wq = hw->hw_wq[0];
	}

	/* Set XRI and RX_ID in the header based on which WQ, and which send_frame_io we are using */
	xri = wq->send_frame_io->indicator;

	/* Build the send frame WQE */
	rc = sli_send_frame_wqe(&hw->sli, wqe->wqebuf, hw->sli.config.wqe_size, sof, eof, (uint32_t*) hdr, payload,
				payload->len, OCS_HW_SEND_FRAME_TIMEOUT, xri, ctx->wqcb->instance_index);
	if (rc) {
		ocs_log_err(hw->os, "sli_send_frame_wqe failed: %d\n", rc);
		return OCS_HW_RTN_ERROR;
	}

	/* Write to WQ */
	rc = hw_wq_write(wq, wqe);
	if (rc) {
		ocs_log_err(hw->os, "hw_wq_write failed: %d\n", rc);
		return OCS_HW_RTN_ERROR;
	}

	OCS_STAT(wq->use_count++);

	return OCS_HW_RTN_SUCCESS;
}