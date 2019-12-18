#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_33__ {scalar_t__ status; int /*<<< orphan*/  total_data_placed; int /*<<< orphan*/  xri; } ;
typedef  TYPE_8__ sli4_fc_optimized_write_data_cqe_t ;
typedef  int /*<<< orphan*/  prop_buf ;
struct TYPE_32__ {int /*<<< orphan*/  unsolicited; } ;
struct TYPE_31__ {int /*<<< orphan*/  (* unsolicited ) (int /*<<< orphan*/ ,TYPE_10__*) ;int /*<<< orphan*/  (* bounce ) (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_28__ {scalar_t__ bounce; } ;
struct TYPE_34__ {TYPE_7__ args; TYPE_6__ callback; TYPE_3__ config; } ;
typedef  TYPE_9__ ocs_hw_t ;
struct TYPE_21__ {int auto_xrdy; TYPE_5__* header; int /*<<< orphan*/  status; int /*<<< orphan*/  hw_priv; int /*<<< orphan*/  fcfi; TYPE_2__* payload; TYPE_11__* hio; int /*<<< orphan*/  xri; scalar_t__ out_of_xris; TYPE_9__* hw; } ;
typedef  TYPE_10__ ocs_hw_sequence_t ;
struct TYPE_22__ {scalar_t__ type; int /*<<< orphan*/  axr_lock; TYPE_12__* axr_buf; } ;
typedef  TYPE_11__ ocs_hw_io_t ;
struct TYPE_26__ {int /*<<< orphan*/  len; } ;
struct TYPE_27__ {TYPE_1__ dma; } ;
struct TYPE_29__ {int len; TYPE_14__* virt; } ;
struct TYPE_30__ {TYPE_4__ dma; } ;
struct TYPE_23__ {int data_cqe; int call_axr_data; int /*<<< orphan*/  cmd_cqe; int /*<<< orphan*/  fcfi; TYPE_2__ payload; TYPE_5__ header; TYPE_10__ seq; } ;
typedef  TYPE_12__ ocs_hw_auto_xfer_rdy_buffer_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_24__ {int /*<<< orphan*/  eq; } ;
typedef  TYPE_13__ hw_cq_t ;
struct TYPE_25__ {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  d_id; int /*<<< orphan*/  s_id; } ;
typedef  TYPE_14__ fc_header_t ;

/* Variables and functions */
 scalar_t__ OCS_HW_IO_TARGET_RSP ; 
 int /*<<< orphan*/  OCS_HW_UNSOL_ABTS_RCVD ; 
 int /*<<< orphan*/  OCS_HW_UNSOL_ERROR ; 
 int /*<<< orphan*/  OCS_HW_UNSOL_SUCCESS ; 
 scalar_t__ SLI4_FC_WCQE_STATUS_REMOTE_STOP ; 
 scalar_t__ SLI4_FC_WCQE_STATUS_SUCCESS ; 
 int /*<<< orphan*/  fc_be24toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_be16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_get_property (char*,char*,int) ; 
 TYPE_11__* ocs_hw_io_lookup (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_unsol_process_bounce ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_10__*) ; 

int32_t
ocs_hw_rqpair_process_auto_xfr_rdy_data(ocs_hw_t *hw, hw_cq_t *cq, uint8_t *cqe)
{
	/* Seems silly to call a SLI function to decode - use the structure directly for performance */
	sli4_fc_optimized_write_data_cqe_t *opt_wr = (sli4_fc_optimized_write_data_cqe_t*)cqe;
	ocs_hw_sequence_t *seq;
	ocs_hw_io_t *io;
	ocs_hw_auto_xfer_rdy_buffer_t *buf;
#if defined(OCS_DISC_SPIN_DELAY)
	uint32_t 	delay = 0;
	char 		prop_buf[32];
#endif
	/* Look up the IO */
	io = ocs_hw_io_lookup(hw, opt_wr->xri);
	ocs_lock(&io->axr_lock);
	buf = io->axr_buf;
	buf->data_cqe = 1;
	seq = &buf->seq;
	seq->hw = hw;
	seq->auto_xrdy = 1;
	seq->out_of_xris = 0;
	seq->xri = opt_wr->xri;
	seq->hio = io;
	seq->header = &buf->header;
	seq->payload = &buf->payload;

	seq->header->dma.len = sizeof(fc_header_t);
	seq->payload->dma.len = opt_wr->total_data_placed;
	seq->fcfi = buf->fcfi;
	seq->hw_priv = cq->eq;


	if (opt_wr->status == SLI4_FC_WCQE_STATUS_SUCCESS) {
		seq->status = OCS_HW_UNSOL_SUCCESS;
	} else if (opt_wr->status == SLI4_FC_WCQE_STATUS_REMOTE_STOP) {
		seq->status = OCS_HW_UNSOL_ABTS_RCVD;
	} else {
		seq->status = OCS_HW_UNSOL_ERROR;
	}

 	/* If AXR CMD CQE came before previous TRSP CQE of same XRI */
	if(io->type == OCS_HW_IO_TARGET_RSP) {
		io->axr_buf->call_axr_data = 1;
		goto exit_ocs_hw_rqpair_process_auto_xfr_rdy_data;
	}

	if(!buf->cmd_cqe) {
		/* if data cqe came before cmd cqe, return here, cmd cqe will handle */
		goto exit_ocs_hw_rqpair_process_auto_xfr_rdy_data;
	}
#if defined(OCS_DISC_SPIN_DELAY)
	if (ocs_get_property("disk_spin_delay", prop_buf, sizeof(prop_buf)) == 0) {
		delay = ocs_strtoul(prop_buf, 0, 0);
		ocs_udelay(delay);
	}
#endif

	/* bounce enabled, single RQ, we snoop the ox_id to choose the cpuidx */
	if (hw->config.bounce) {
		fc_header_t *hdr = seq->header->dma.virt;
		uint32_t s_id = fc_be24toh(hdr->s_id);
		uint32_t d_id = fc_be24toh(hdr->d_id);
		uint32_t ox_id =  ocs_be16toh(hdr->ox_id);
		if (hw->callback.bounce != NULL) {
			(*hw->callback.bounce)(ocs_hw_unsol_process_bounce, seq, s_id, d_id, ox_id);
		}
	} else {
		hw->callback.unsolicited(hw->args.unsolicited, seq);
	}

exit_ocs_hw_rqpair_process_auto_xfr_rdy_data:
	ocs_unlock(&io->axr_lock);
	return 0;
}