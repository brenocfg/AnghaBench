#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_61__   TYPE_9__ ;
typedef  struct TYPE_60__   TYPE_8__ ;
typedef  struct TYPE_59__   TYPE_7__ ;
typedef  struct TYPE_58__   TYPE_6__ ;
typedef  struct TYPE_57__   TYPE_5__ ;
typedef  struct TYPE_56__   TYPE_4__ ;
typedef  struct TYPE_55__   TYPE_46__ ;
typedef  struct TYPE_54__   TYPE_41__ ;
typedef  struct TYPE_53__   TYPE_3__ ;
typedef  struct TYPE_52__   TYPE_32__ ;
typedef  struct TYPE_51__   TYPE_2__ ;
typedef  struct TYPE_50__   TYPE_1__ ;
typedef  struct TYPE_49__   TYPE_12__ ;
typedef  struct TYPE_48__   TYPE_11__ ;
typedef  struct TYPE_47__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_59__ {scalar_t__ indicator; } ;
typedef  TYPE_7__ ocs_remote_node_t ;
struct TYPE_57__ {int /*<<< orphan*/  wqe_size; } ;
struct TYPE_49__ {TYPE_5__ config; } ;
struct TYPE_56__ {scalar_t__ unregistered_rid; int /*<<< orphan*/  retain_tsend_io_length; int /*<<< orphan*/  use_dif_sec_xri; int /*<<< orphan*/  use_dif_quarantine; scalar_t__ use_unregistered_rpi; } ;
struct TYPE_53__ {int /*<<< orphan*/  dif_mode; } ;
struct TYPE_60__ {int state; int /*<<< orphan*/  os; int /*<<< orphan*/ * tcmd_wq_submit; TYPE_12__ sli; int /*<<< orphan*/  auto_xfer_rdy_enabled; TYPE_4__ workaround; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  sec_hio_wait_count; int /*<<< orphan*/  sec_hio_wait_list; int /*<<< orphan*/  io_inuse; TYPE_3__ config; } ;
typedef  TYPE_8__ ocs_hw_t ;
typedef  int ocs_hw_rtn_e ;
typedef  int ocs_hw_io_type_e ;
struct TYPE_55__ {int /*<<< orphan*/  wqebuf; } ;
struct TYPE_58__ {scalar_t__ offset; int /*<<< orphan*/  app_id; int /*<<< orphan*/  cs_ctl; int /*<<< orphan*/  ox_id; int /*<<< orphan*/  timeout; int /*<<< orphan*/  flags; int /*<<< orphan*/  blk_size; int /*<<< orphan*/  dif_oper; } ;
struct TYPE_50__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  rsp; int /*<<< orphan*/  cmnd_size; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  blk_size; int /*<<< orphan*/  dif_oper; int /*<<< orphan*/  first_burst; } ;
struct TYPE_47__ {TYPE_6__ fcp_tgt; TYPE_1__ fcp_ini; } ;
struct TYPE_51__ {TYPE_11__* virt; } ;
struct TYPE_61__ {int type; void* xbusy; TYPE_46__ wqe; TYPE_32__* wq; int /*<<< orphan*/  is_port_owned; int /*<<< orphan*/  reqtag; int /*<<< orphan*/  indicator; int /*<<< orphan*/  def_sgl; int /*<<< orphan*/  tgt_wqe_timeout; int /*<<< orphan*/  auto_xfer_rdy_dnrx; scalar_t__ length; int /*<<< orphan*/  first_data_sge; TYPE_41__* sec_hio; int /*<<< orphan*/  state; scalar_t__ sec_len; TYPE_10__ sec_iparam; TYPE_41__* ovfl_io; void* quarantine; TYPE_2__ xfer_rdy; void* arg; void* done; TYPE_7__* rnode; } ;
typedef  TYPE_9__ ocs_hw_io_t ;
typedef  TYPE_10__ ocs_hw_io_param_t ;
struct TYPE_48__ {scalar_t__ rsvd; scalar_t__ fcp_burst_len; scalar_t__ fcp_data_ro; } ;
typedef  TYPE_11__ fcp_xfer_rdy_iu_t ;
struct TYPE_54__ {int /*<<< orphan*/  indicator; void* quarantine; } ;
struct TYPE_52__ {size_t instance; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUTRACE (char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  OCS_HW_DIF_MODE_SEPARATE ; 
 int /*<<< orphan*/  OCS_HW_DIF_OPER_DISABLED ; 
#define  OCS_HW_IO_INITIATOR_NODATA 133 
#define  OCS_HW_IO_INITIATOR_READ 132 
#define  OCS_HW_IO_INITIATOR_WRITE 131 
 int /*<<< orphan*/  OCS_HW_IO_STATE_WAIT_SEC_HIO ; 
#define  OCS_HW_IO_TARGET_READ 130 
#define  OCS_HW_IO_TARGET_RSP 129 
#define  OCS_HW_IO_TARGET_WRITE 128 
 int OCS_HW_RTN_ERROR ; 
 int OCS_HW_RTN_SUCCESS ; 
 int OCS_HW_STATE_ACTIVE ; 
 int /*<<< orphan*/  OCS_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLI4_CQ_DEFAULT ; 
 int /*<<< orphan*/  SLI4_IO_CONTINUATION ; 
 int /*<<< orphan*/  SLI4_IO_DNRX ; 
 void* TRUE ; 
 scalar_t__ UINT32_MAX ; 
 int hw_wq_write (TYPE_32__*,TYPE_46__*) ; 
 scalar_t__ ocs_htobe32 (scalar_t__) ; 
 int /*<<< orphan*/  ocs_hw_add_io_timed_wqe (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ocs_hw_assert (int /*<<< orphan*/ ) ; 
 TYPE_41__* ocs_hw_io_alloc (TYPE_8__*) ; 
 int /*<<< orphan*/  ocs_hw_io_ini_sge (TYPE_8__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_32__* ocs_hw_queue_next_wq (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ocs_hw_remove_io_timed_wqe (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ocs_hw_rqpair_auto_xfer_rdy_buffer_post (TYPE_8__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  ocs_list_remove (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sli_fcp_cont_treceive64_wqe (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_fcp_icmnd64_wqe (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_fcp_iread64_wqe (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_fcp_iwrite64_wqe (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_fcp_treceive64_wqe (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_fcp_trsp64_wqe (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sli_fcp_tsend64_wqe (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_io_send(ocs_hw_t *hw, ocs_hw_io_type_e type, ocs_hw_io_t *io,
		uint32_t len, ocs_hw_io_param_t *iparam, ocs_remote_node_t *rnode,
		void *cb, void *arg)
{
	ocs_hw_rtn_e	rc = OCS_HW_RTN_SUCCESS;
	uint32_t	rpi;
	uint8_t		send_wqe = TRUE;

	CPUTRACE("");

	if (!hw || !io || !rnode || !iparam) {
		ocs_log_err(NULL, "bad parm hw=%p io=%p iparam=%p rnode=%p\n",
			    hw, io, iparam, rnode);
		return OCS_HW_RTN_ERROR;
	}

	if (hw->state != OCS_HW_STATE_ACTIVE) {
		ocs_log_err(hw->os, "cannot send IO, HW state=%d\n", hw->state);
		return OCS_HW_RTN_ERROR;
	}

	rpi = rnode->indicator;

	if (hw->workaround.use_unregistered_rpi && (rpi == UINT32_MAX)) {
		rpi = hw->workaround.unregistered_rid;
		ocs_log_test(hw->os, "using unregistered RPI: %d\n", rpi);
	}

	/*
	 * Save state needed during later stages
	 */
	io->rnode = rnode;
	io->type  = type;
	io->done  = cb;
	io->arg   = arg;

	/*
	 * Format the work queue entry used to send the IO
	 */
	switch (type) {
	case OCS_HW_IO_INITIATOR_READ:
		/*
		 * If use_dif_quarantine workaround is in effect, and dif_separates then mark the
		 * initiator read IO for quarantine
		 */
		if (hw->workaround.use_dif_quarantine && (hw->config.dif_mode == OCS_HW_DIF_MODE_SEPARATE) &&
		    (iparam->fcp_tgt.dif_oper != OCS_HW_DIF_OPER_DISABLED)) {
			io->quarantine = TRUE;
		}

		ocs_hw_io_ini_sge(hw, io, iparam->fcp_ini.cmnd, iparam->fcp_ini.cmnd_size,
				iparam->fcp_ini.rsp);

		if (sli_fcp_iread64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &io->def_sgl, io->first_data_sge, len,
					io->indicator, io->reqtag, SLI4_CQ_DEFAULT, rpi, rnode,
					iparam->fcp_ini.dif_oper, iparam->fcp_ini.blk_size,
					iparam->fcp_ini.timeout)) {
			ocs_log_err(hw->os, "IREAD WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_IO_INITIATOR_WRITE:
		ocs_hw_io_ini_sge(hw, io, iparam->fcp_ini.cmnd, iparam->fcp_ini.cmnd_size,
				iparam->fcp_ini.rsp);

		if (sli_fcp_iwrite64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &io->def_sgl, io->first_data_sge,
					 len, iparam->fcp_ini.first_burst,
					 io->indicator, io->reqtag,
					SLI4_CQ_DEFAULT, rpi, rnode,
					iparam->fcp_ini.dif_oper, iparam->fcp_ini.blk_size,
					iparam->fcp_ini.timeout)) {
			ocs_log_err(hw->os, "IWRITE WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_IO_INITIATOR_NODATA:
		ocs_hw_io_ini_sge(hw, io, iparam->fcp_ini.cmnd, iparam->fcp_ini.cmnd_size,
				iparam->fcp_ini.rsp);

		if (sli_fcp_icmnd64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &io->def_sgl,
					io->indicator, io->reqtag, SLI4_CQ_DEFAULT,
					rpi, rnode, iparam->fcp_ini.timeout)) {
			ocs_log_err(hw->os, "ICMND WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}
		break;
	case OCS_HW_IO_TARGET_WRITE: {
		uint16_t flags = iparam->fcp_tgt.flags;
		fcp_xfer_rdy_iu_t *xfer = io->xfer_rdy.virt;

		/*
		 * Fill in the XFER_RDY for IF_TYPE 0 devices
		 */
		*((uint32_t *)xfer->fcp_data_ro) = ocs_htobe32(iparam->fcp_tgt.offset);
		*((uint32_t *)xfer->fcp_burst_len) = ocs_htobe32(len);
		*((uint32_t *)xfer->rsvd) = 0;

		if (io->xbusy) {
			flags |= SLI4_IO_CONTINUATION;
		} else {
			flags &= ~SLI4_IO_CONTINUATION;
		}

		io->tgt_wqe_timeout = iparam->fcp_tgt.timeout;

		/*
		 * If use_dif_quarantine workaround is in effect, and this is a DIF enabled IO
		 * then mark the target write IO for quarantine
		 */
		if (hw->workaround.use_dif_quarantine && (hw->config.dif_mode == OCS_HW_DIF_MODE_SEPARATE) &&
		    (iparam->fcp_tgt.dif_oper != OCS_HW_DIF_OPER_DISABLED)) {
			io->quarantine = TRUE;
		}

		/*
		 * BZ 161832 Workaround:
		 * Check for use_dif_sec_xri workaround.  Note, even though the first dataphase
		 * doesn't really need a secondary XRI, we allocate one anyway, as this avoids the
		 * potential for deadlock where all XRI's are allocated as primaries to IOs that
		 * are on hw->sec_hio_wait_list.   If this secondary XRI is not for the first
		 * data phase, it is marked for quarantine.
		 */
		if (hw->workaround.use_dif_sec_xri && (iparam->fcp_tgt.dif_oper != OCS_HW_DIF_OPER_DISABLED)) {

			/*
			 * If we have allocated a chained SGL for skyhawk, then
			 * we can re-use this for the sec_hio.
			 */
			if (io->ovfl_io != NULL) {
				io->sec_hio = io->ovfl_io;
				io->sec_hio->quarantine = TRUE;
			} else {
				io->sec_hio = ocs_hw_io_alloc(hw);
			}
			if (io->sec_hio == NULL) {
				/* Failed to allocate, so save full request context and put
				 * this IO on the wait list
				 */
				io->sec_iparam = *iparam;
				io->sec_len = len;
				ocs_lock(&hw->io_lock);
					ocs_list_remove(&hw->io_inuse,  io);
					ocs_list_add_tail(&hw->sec_hio_wait_list, io);
					io->state = OCS_HW_IO_STATE_WAIT_SEC_HIO;
					hw->sec_hio_wait_count++;
				ocs_unlock(&hw->io_lock);
				send_wqe = FALSE;
				/* Done */
				break;
			}
			/* We quarantine the secondary IO if this is the second or subsequent data phase */
			if (io->xbusy) {
				io->sec_hio->quarantine = TRUE;
			}
		}

		/*
		 * If not the first data phase, and io->sec_hio has been allocated, then issue
		 * FCP_CONT_TRECEIVE64 WQE, otherwise use the usual FCP_TRECEIVE64 WQE
		 */
		if (io->xbusy && (io->sec_hio != NULL)) {
			if (sli_fcp_cont_treceive64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &io->def_sgl, io->first_data_sge,
						   iparam->fcp_tgt.offset, len, io->indicator, io->sec_hio->indicator,
						   io->reqtag, SLI4_CQ_DEFAULT,
						   iparam->fcp_tgt.ox_id, rpi, rnode,
						   flags,
						   iparam->fcp_tgt.dif_oper, iparam->fcp_tgt.blk_size,
						   iparam->fcp_tgt.cs_ctl, iparam->fcp_tgt.app_id)) {
				ocs_log_err(hw->os, "TRECEIVE WQE error\n");
				rc = OCS_HW_RTN_ERROR;
			}
		} else {
			if (sli_fcp_treceive64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &io->def_sgl, io->first_data_sge,
						   iparam->fcp_tgt.offset, len, io->indicator, io->reqtag,
						   SLI4_CQ_DEFAULT,
						   iparam->fcp_tgt.ox_id, rpi, rnode,
						   flags,
						   iparam->fcp_tgt.dif_oper, iparam->fcp_tgt.blk_size,
						   iparam->fcp_tgt.cs_ctl, iparam->fcp_tgt.app_id)) {
				ocs_log_err(hw->os, "TRECEIVE WQE error\n");
				rc = OCS_HW_RTN_ERROR;
			}
		}
		break;
	}
	case OCS_HW_IO_TARGET_READ: {
		uint16_t flags = iparam->fcp_tgt.flags;

		if (io->xbusy) {
			flags |= SLI4_IO_CONTINUATION;
		} else {
			flags &= ~SLI4_IO_CONTINUATION;
		}

		io->tgt_wqe_timeout = iparam->fcp_tgt.timeout;
		if (sli_fcp_tsend64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size, &io->def_sgl, io->first_data_sge,
					iparam->fcp_tgt.offset, len, io->indicator, io->reqtag,
					SLI4_CQ_DEFAULT,
					iparam->fcp_tgt.ox_id, rpi, rnode,
					flags,
					iparam->fcp_tgt.dif_oper,
					iparam->fcp_tgt.blk_size,
					iparam->fcp_tgt.cs_ctl,
					iparam->fcp_tgt.app_id)) {
			ocs_log_err(hw->os, "TSEND WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		} else if (hw->workaround.retain_tsend_io_length) {
			io->length = len;
		}
		break;
	}
	case OCS_HW_IO_TARGET_RSP: {
		uint16_t flags = iparam->fcp_tgt.flags;

		if (io->xbusy) {
			flags |= SLI4_IO_CONTINUATION;
		} else {
			flags &= ~SLI4_IO_CONTINUATION;
		}

		/* post a new auto xfer ready buffer */
		if (hw->auto_xfer_rdy_enabled && io->is_port_owned) {
			if ((io->auto_xfer_rdy_dnrx = ocs_hw_rqpair_auto_xfer_rdy_buffer_post(hw, io, 1))) {
				flags |= SLI4_IO_DNRX;
			}
		}

		io->tgt_wqe_timeout = iparam->fcp_tgt.timeout;
		if (sli_fcp_trsp64_wqe(&hw->sli, io->wqe.wqebuf, hw->sli.config.wqe_size,
					&io->def_sgl,
					len,
					io->indicator, io->reqtag,
					SLI4_CQ_DEFAULT,
					iparam->fcp_tgt.ox_id,
					rpi, rnode,
					flags, iparam->fcp_tgt.cs_ctl,
					io->is_port_owned,
					iparam->fcp_tgt.app_id)) {
			ocs_log_err(hw->os, "TRSP WQE error\n");
			rc = OCS_HW_RTN_ERROR;
		}

		break;
	}
	default:
		ocs_log_err(hw->os, "unsupported IO type %#x\n", type);
		rc = OCS_HW_RTN_ERROR;
	}

	if (send_wqe && (OCS_HW_RTN_SUCCESS == rc)) {
		if (io->wq == NULL) {
			io->wq = ocs_hw_queue_next_wq(hw, io);
			ocs_hw_assert(io->wq != NULL);
		}

		io->xbusy = TRUE;

		/*
		 * Add IO to active io wqe list before submitting, in case the
		 * wcqe processing preempts this thread.
		 */
		OCS_STAT(hw->tcmd_wq_submit[io->wq->instance]++);
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