#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_62__   TYPE_9__ ;
typedef  struct TYPE_61__   TYPE_8__ ;
typedef  struct TYPE_60__   TYPE_7__ ;
typedef  struct TYPE_59__   TYPE_6__ ;
typedef  struct TYPE_58__   TYPE_5__ ;
typedef  struct TYPE_57__   TYPE_4__ ;
typedef  struct TYPE_56__   TYPE_43__ ;
typedef  struct TYPE_55__   TYPE_3__ ;
typedef  struct TYPE_54__   TYPE_36__ ;
typedef  struct TYPE_53__   TYPE_2__ ;
typedef  struct TYPE_52__   TYPE_1__ ;
typedef  struct TYPE_51__   TYPE_17__ ;
typedef  struct TYPE_50__   TYPE_16__ ;
typedef  struct TYPE_49__   TYPE_15__ ;
typedef  struct TYPE_48__   TYPE_14__ ;
typedef  struct TYPE_47__   TYPE_13__ ;
typedef  struct TYPE_46__   TYPE_12__ ;
typedef  struct TYPE_45__   TYPE_11__ ;
typedef  struct TYPE_44__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_59__ {int /*<<< orphan*/  acc; int /*<<< orphan*/  rjt; } ;
struct TYPE_44__ {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; TYPE_6__ u; void* type; } ;
typedef  TYPE_10__ sli_bls_payload_t ;
struct TYPE_45__ {void* last; int /*<<< orphan*/  buffer_length; void* sge_type; void* buffer_address_low; void* buffer_address_high; } ;
typedef  TYPE_11__ sli4_sge_t ;
typedef  int /*<<< orphan*/  ocs_remote_node_t ;
struct TYPE_61__ {int /*<<< orphan*/  wqe_size; } ;
struct TYPE_50__ {TYPE_8__ config; } ;
struct TYPE_46__ {scalar_t__ state; int /*<<< orphan*/  os; TYPE_16__ sli; } ;
typedef  TYPE_12__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_srrs_cb_t ;
typedef  int ocs_hw_rtn_e ;
typedef  int ocs_hw_io_type_e ;
struct TYPE_56__ {int /*<<< orphan*/  wqebuf; } ;
struct TYPE_47__ {int type; void* xbusy; TYPE_43__ wqe; TYPE_36__* wq; int /*<<< orphan*/  reqtag; int /*<<< orphan*/  indicator; TYPE_17__* sgl; void* arg; int /*<<< orphan*/  done; int /*<<< orphan*/ * rnode; } ;
typedef  TYPE_13__ ocs_hw_io_t ;
struct TYPE_62__ {int /*<<< orphan*/  df_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  timeout; } ;
struct TYPE_60__ {int /*<<< orphan*/  s_id; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  payload; } ;
struct TYPE_58__ {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  payload; } ;
struct TYPE_57__ {int /*<<< orphan*/  df_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  timeout; } ;
struct TYPE_55__ {int /*<<< orphan*/  df_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  timeout; } ;
struct TYPE_53__ {int /*<<< orphan*/  s_id; int /*<<< orphan*/  ox_id; } ;
struct TYPE_52__ {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  timeout; } ;
struct TYPE_48__ {TYPE_9__ bcast; TYPE_7__ bls_sid; TYPE_5__ bls; TYPE_4__ fc_ct_rsp; TYPE_3__ fc_ct; TYPE_2__ els_sid; TYPE_1__ els; } ;
typedef  TYPE_14__ ocs_hw_io_param_t ;
struct TYPE_49__ {int /*<<< orphan*/  size; scalar_t__ virt; int /*<<< orphan*/  phys; } ;
typedef  TYPE_15__ ocs_dma_t ;
struct TYPE_54__ {int /*<<< orphan*/  use_count; } ;
struct TYPE_51__ {TYPE_11__* virt; } ;

/* Variables and functions */
 void* FALSE ; 
#define  OCS_HW_BCAST 136 
#define  OCS_HW_BLS_ACC 135 
#define  OCS_HW_BLS_ACC_SID 134 
#define  OCS_HW_BLS_RJT 133 
#define  OCS_HW_ELS_REQ 132 
#define  OCS_HW_ELS_RSP 131 
#define  OCS_HW_ELS_RSP_SID 130 
#define  OCS_HW_FC_CT 129 
#define  OCS_HW_FC_CT_RSP 128 
 int OCS_HW_RTN_ERROR ; 
 int OCS_HW_RTN_SUCCESS ; 
 scalar_t__ OCS_HW_STATE_ACTIVE ; 
 int /*<<< orphan*/  OCS_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLI4_CQ_DEFAULT ; 
 int /*<<< orphan*/  SLI4_IO_CONTINUATION ; 
 void* SLI4_SGE_TYPE_DATA ; 
 void* SLI_BLS_ACC ; 
 void* SLI_BLS_RJT ; 
 void* TRUE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int hw_wq_write (TYPE_36__*,TYPE_43__*) ; 
 void* ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 void* ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_add_io_timed_wqe (TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ocs_hw_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_hw_is_xri_port_owned (TYPE_12__*,int /*<<< orphan*/ ) ; 
 TYPE_36__* ocs_hw_queue_next_wq (TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ocs_hw_remove_io_timed_wqe (TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sli_els_request64_wqe (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_gen_request64_wqe (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_xmit_bcast64_wqe (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_xmit_bls_rsp64_wqe (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_xmit_els_rsp64_wqe (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_15__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_xmit_sequence64_wqe (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_srrs_send(ocs_hw_t *hw, ocs_hw_io_type_e type, ocs_hw_io_t *io,
		  ocs_dma_t *send, uint32_t len, ocs_dma_t *receive,
		  ocs_remote_node_t *rnode, ocs_hw_io_param_t *iparam,
		  ocs_hw_srrs_cb_t cb, void *arg)
{
	sli4_sge_t	*sge = NULL;
	ocs_hw_rtn_e	rc = OCS_HW_RTN_SUCCESS;
	uint16_t	local_flags = 0;

	if (!hw || !io || !rnode || !iparam) {
		ocs_log_err(NULL, "bad parm hw=%p io=%p send=%p receive=%p rnode=%p iparam=%p\n",
			    hw, io, send, receive, rnode, iparam);
		return OCS_HW_RTN_ERROR;
	}

	if (hw->state != OCS_HW_STATE_ACTIVE) {
		ocs_log_test(hw->os, "cannot send SRRS, HW state=%d\n", hw->state);
		return OCS_HW_RTN_ERROR;
	}

	if (ocs_hw_is_xri_port_owned(hw, io->indicator)) {
		/* We must set the XC bit for port owned XRIs */
		local_flags |= SLI4_IO_CONTINUATION;
	}
	io->rnode = rnode;
	io->type  = type;
	io->done = cb;
	io->arg  = arg;

	sge = io->sgl->virt;

	/* clear both SGE */
	ocs_memset(io->sgl->virt, 0, 2 * sizeof(sli4_sge_t));

	if (send) {
		sge[0].buffer_address_high = ocs_addr32_hi(send->phys);
		sge[0].buffer_address_low  = ocs_addr32_lo(send->phys);
		sge[0].sge_type = SLI4_SGE_TYPE_DATA;
		sge[0].buffer_length = len;
	}

	if ((OCS_HW_ELS_REQ == type) || (OCS_HW_FC_CT == type)) {
		sge[1].buffer_address_high = ocs_addr32_hi(receive->phys);
		sge[1].buffer_address_low  = ocs_addr32_lo(receive->phys);
		sge[1].sge_type = SLI4_SGE_TYPE_DATA;
		sge[1].buffer_length = receive->size;
		sge[1].last = TRUE;
	} else {
		sge[0].last = TRUE;
	}

	switch (type) {
	case OCS_HW_ELS_REQ:
		if ( (!send) || sli_els_request64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, io->sgl,
							*((uint8_t *)(send->virt)), /* req_type */
							len, receive->size,
							iparam->els.timeout, io->indicator, io->reqtag, SLI4_CQ_DEFAULT, rnode)) {
			ocs_log_err(hw->os, "REQ WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_ELS_RSP:
		if ( (!send) || sli_xmit_els_rsp64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, send, len,
					   io->indicator, io->reqtag, SLI4_CQ_DEFAULT,
					   iparam->els.ox_id,
							rnode, local_flags, UINT32_MAX)) {
			ocs_log_err(hw->os, "RSP WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_ELS_RSP_SID:
		if ( (!send) || sli_xmit_els_rsp64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, send, len,
					   io->indicator, io->reqtag, SLI4_CQ_DEFAULT,
					   iparam->els_sid.ox_id,
							rnode, local_flags, iparam->els_sid.s_id)) {
			ocs_log_err(hw->os, "RSP (SID) WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_FC_CT:
		if ( (!send) || sli_gen_request64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, io->sgl, len,
					  receive->size, iparam->fc_ct.timeout, io->indicator,
					  io->reqtag, SLI4_CQ_DEFAULT, rnode, iparam->fc_ct.r_ctl,
					  iparam->fc_ct.type, iparam->fc_ct.df_ctl)) {
			ocs_log_err(hw->os, "GEN WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_FC_CT_RSP:
		if ( (!send) || sli_xmit_sequence64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, io->sgl, len,
					  iparam->fc_ct_rsp.timeout, iparam->fc_ct_rsp.ox_id, io->indicator,
					  io->reqtag, rnode, iparam->fc_ct_rsp.r_ctl,
					  iparam->fc_ct_rsp.type, iparam->fc_ct_rsp.df_ctl)) {
			ocs_log_err(hw->os, "XMIT SEQ WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_BLS_ACC:
	case OCS_HW_BLS_RJT:
	{
		sli_bls_payload_t	bls;

		if (OCS_HW_BLS_ACC == type) {
			bls.type = SLI_BLS_ACC;
			ocs_memcpy(&bls.u.acc, iparam->bls.payload, sizeof(bls.u.acc));
		} else {
			bls.type = SLI_BLS_RJT;
			ocs_memcpy(&bls.u.rjt, iparam->bls.payload, sizeof(bls.u.rjt));
		}

		bls.ox_id = iparam->bls.ox_id;
		bls.rx_id = iparam->bls.rx_id;

		if (sli_xmit_bls_rsp64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &bls,
					   io->indicator, io->reqtag,
					   SLI4_CQ_DEFAULT,
					   rnode, UINT32_MAX)) {
			ocs_log_err(hw->os, "XMIT_BLS_RSP64 WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	}
	case OCS_HW_BLS_ACC_SID:
	{
		sli_bls_payload_t	bls;

		bls.type = SLI_BLS_ACC;
		ocs_memcpy(&bls.u.acc, iparam->bls_sid.payload, sizeof(bls.u.acc));

		bls.ox_id = iparam->bls_sid.ox_id;
		bls.rx_id = iparam->bls_sid.rx_id;

		if (sli_xmit_bls_rsp64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &bls,
					   io->indicator, io->reqtag,
					   SLI4_CQ_DEFAULT,
					   rnode, iparam->bls_sid.s_id)) {
			ocs_log_err(hw->os, "XMIT_BLS_RSP64 WQE SID error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	}
	case OCS_HW_BCAST:
		if ( (!send) || sli_xmit_bcast64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, send, len,
					iparam->bcast.timeout, io->indicator, io->reqtag,
					SLI4_CQ_DEFAULT, rnode,
					iparam->bcast.r_ctl, iparam->bcast.type, iparam->bcast.df_ctl)) {
			ocs_log_err(hw->os, "XMIT_BCAST64 WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	default:
		ocs_log_err(hw->os, "bad SRRS type %#x\n", type);
		rc = OCS_HW_RTN_ERROR;
	}

	if (OCS_HW_RTN_SUCCESS == rc) {
		if (io->wq == NULL) {
			io->wq = ocs_hw_queue_next_wq(hw, io);
			ocs_hw_assert(io->wq != NULL);
		}
		io->xbusy = TRUE;

		/*
		 * Add IO to active io wqe list before submitting, in case the
		 * wcqe processing preempts this thread.
		 */
		OCS_STAT(io->wq->use_count++);
		ocs_hw_add_io_timed_wqe(hw, io);
		rc = hw_wq_write(io->wq, &io->wqe);
		if (rc >= 0) {
			/* non-negative return is success */
			rc = 0;
		} else {
			/* failed to write wqe, remove from active wqe list */
			ocs_log_err(hw->os, "sli_queue_write failed: %d\n", rc);
			io->xbusy = FALSE;
			ocs_hw_remove_io_timed_wqe(hw, io);
		}
	}

	return rc;
}