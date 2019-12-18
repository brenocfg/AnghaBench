#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_hw_t ;
struct TYPE_16__ {TYPE_2__* header; } ;
typedef  TYPE_7__ ocs_hw_sequence_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
struct TYPE_15__ {int /*<<< orphan*/  rqindex; } ;
struct TYPE_13__ {int size; int len; TYPE_8__* alloc; TYPE_3__* virt; } ;
struct TYPE_14__ {TYPE_4__ dma; int /*<<< orphan*/  rqindex; } ;
struct TYPE_12__ {int /*<<< orphan*/  f_ctl; int /*<<< orphan*/  type; int /*<<< orphan*/  r_ctl; int /*<<< orphan*/  info; } ;
struct TYPE_17__ {TYPE_6__ payload; TYPE_5__ header; TYPE_3__ hdr; scalar_t__ call_axr_data; scalar_t__ call_axr_cmd; scalar_t__ fcfi; scalar_t__ cmd_cqe; scalar_t__ data_cqe; } ;
typedef  TYPE_8__ ocs_hw_auto_xfer_rdy_buffer_t ;
struct TYPE_10__ {TYPE_8__* alloc; } ;
struct TYPE_11__ {TYPE_1__ dma; } ;

/* Variables and functions */
 int FC_FCTL_END_SEQUENCE ; 
 int FC_FCTL_EXCHANGE_RESPONDER ; 
 int FC_FCTL_FIRST_SEQUENCE ; 
 int FC_FCTL_LAST_SEQUENCE ; 
 int FC_FCTL_SEQUENCE_INITIATIVE ; 
 int /*<<< orphan*/  FC_RCTL_FC4_DATA ; 
 int /*<<< orphan*/  FC_RCTL_INFO_SOL_DATA ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  OCS_HW_RQ_INDEX_DUMMY_DATA ; 
 int /*<<< orphan*/  OCS_HW_RQ_INDEX_DUMMY_HDR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  fc_htobe24 (int) ; 
 int /*<<< orphan*/  ocs_hw_rqpair_auto_xfer_rdy_dnrx_check (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ocs_hw_rtn_e
ocs_hw_rqpair_auto_xfer_rdy_buffer_sequence_reset(ocs_hw_t *hw, ocs_hw_sequence_t *seq)
{
	ocs_hw_auto_xfer_rdy_buffer_t *buf = seq->header->dma.alloc;

	buf->data_cqe = 0;
	buf->cmd_cqe = 0;
	buf->fcfi = 0;
	buf->call_axr_cmd = 0;
	buf->call_axr_data = 0;

	/* build a fake data header in big endian */
	buf->hdr.info = FC_RCTL_INFO_SOL_DATA;
	buf->hdr.r_ctl = FC_RCTL_FC4_DATA;
	buf->hdr.type = FC_TYPE_FCP;
	buf->hdr.f_ctl = fc_htobe24(FC_FCTL_EXCHANGE_RESPONDER |
					FC_FCTL_FIRST_SEQUENCE |
					FC_FCTL_LAST_SEQUENCE |
					FC_FCTL_END_SEQUENCE |
					FC_FCTL_SEQUENCE_INITIATIVE);

	/* build the fake header DMA object */
	buf->header.rqindex = OCS_HW_RQ_INDEX_DUMMY_HDR;
	buf->header.dma.virt = &buf->hdr;
	buf->header.dma.alloc = buf;
	buf->header.dma.size = sizeof(buf->hdr);
	buf->header.dma.len = sizeof(buf->hdr);
	buf->payload.rqindex = OCS_HW_RQ_INDEX_DUMMY_DATA;

	ocs_hw_rqpair_auto_xfer_rdy_dnrx_check(hw);

	return OCS_HW_RTN_SUCCESS;
}