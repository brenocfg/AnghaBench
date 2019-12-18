#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int msg; } ;
struct TYPE_11__ {int /*<<< orphan*/  vf_id; int /*<<< orphan*/  max_frs; } ;
struct TYPE_10__ {int vf_id; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_14__ {int qs_num; int sq_num; int cfg; } ;
struct TYPE_9__ {int num; int cfg; } ;
struct TYPE_8__ {int qs_num; int rq_num; int cfg; } ;
union nic_mbx {TYPE_6__ msg; int /*<<< orphan*/  lbk; int /*<<< orphan*/  bgx_stats; int /*<<< orphan*/  rss_cfg; int /*<<< orphan*/  cpi_cfg; TYPE_4__ frs; TYPE_3__ mac; TYPE_7__ sq; TYPE_2__ qs; TYPE_1__ rq; } ;
typedef  int uint64_t ;
struct nicpf {void** mbx_lock; int /*<<< orphan*/  dev; TYPE_5__* vf_info; int /*<<< orphan*/  node; int /*<<< orphan*/ * vf_lmac_map; int /*<<< orphan*/ * speed; int /*<<< orphan*/ * duplex; int /*<<< orphan*/ * link; } ;
struct TYPE_12__ {void* vf_enabled; } ;

/* Variables and functions */
 void* FALSE ; 
 int MAX_LMAC ; 
 int NIC_GET_BGX_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
 int NIC_GET_LMAC_FROM_VF_LMAC_MAP (int /*<<< orphan*/ ) ; 
#define  NIC_MBOX_MSG_BGX_STATS 144 
#define  NIC_MBOX_MSG_CFG_DONE 143 
#define  NIC_MBOX_MSG_CPI_CFG 142 
#define  NIC_MBOX_MSG_LOOPBACK 141 
#define  NIC_MBOX_MSG_QS_CFG 140 
#define  NIC_MBOX_MSG_READY 139 
#define  NIC_MBOX_MSG_RQ_BP_CFG 138 
#define  NIC_MBOX_MSG_RQ_CFG 137 
#define  NIC_MBOX_MSG_RQ_DROP_CFG 136 
#define  NIC_MBOX_MSG_RQ_SW_SYNC 135 
#define  NIC_MBOX_MSG_RSS_CFG 134 
#define  NIC_MBOX_MSG_RSS_CFG_CONT 133 
#define  NIC_MBOX_MSG_RSS_SIZE 132 
#define  NIC_MBOX_MSG_SET_MAC 131 
#define  NIC_MBOX_MSG_SET_MAX_FRS 130 
#define  NIC_MBOX_MSG_SHUTDOWN 129 
#define  NIC_MBOX_MSG_SQ_CFG 128 
 int NIC_PF_QSET_0_127_CFG ; 
 int NIC_PF_QSET_0_127_RQ_0_7_BP_CFG ; 
 int NIC_PF_QSET_0_127_RQ_0_7_CFG ; 
 int NIC_PF_QSET_0_127_RQ_0_7_DROP_CFG ; 
 int NIC_PF_QSET_0_127_SQ_0_7_CFG ; 
 int NIC_PF_VF_MAILBOX_SIZE ; 
 int NIC_QS_ID_SHIFT ; 
 int NIC_Q_NUM_SHIFT ; 
 void* TRUE ; 
 int /*<<< orphan*/  bgx_set_lmac_mac (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  nic_config_cpi (struct nicpf*,int /*<<< orphan*/ *) ; 
 int nic_config_loopback (struct nicpf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nic_config_rss (struct nicpf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nic_get_bgx_stats (struct nicpf*,int /*<<< orphan*/ *) ; 
 int nic_get_mbx_addr (int) ; 
 int /*<<< orphan*/  nic_mbx_send_ack (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_mbx_send_nack (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_mbx_send_ready (struct nicpf*,int) ; 
 int nic_rcv_queue_sw_sync (struct nicpf*) ; 
 int nic_reg_read (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_reg_write (struct nicpf*,int,int) ; 
 int /*<<< orphan*/  nic_send_rss_size (struct nicpf*,int) ; 
 int /*<<< orphan*/  nic_tx_channel_cfg (struct nicpf*,int,TYPE_7__*) ; 
 int nic_update_hw_frs (struct nicpf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nic_handle_mbx_intr(struct nicpf *nic, int vf)
{
	union nic_mbx mbx = {};
	uint64_t *mbx_data;
	uint64_t mbx_addr;
	uint64_t reg_addr;
	uint64_t cfg;
	int bgx, lmac;
	int i;
	int ret = 0;

	nic->mbx_lock[vf] = TRUE;

	mbx_addr = nic_get_mbx_addr(vf);
	mbx_data = (uint64_t *)&mbx;

	for (i = 0; i < NIC_PF_VF_MAILBOX_SIZE; i++) {
		*mbx_data = nic_reg_read(nic, mbx_addr);
		mbx_data++;
		mbx_addr += sizeof(uint64_t);
	}

	switch (mbx.msg.msg) {
	case NIC_MBOX_MSG_READY:
		nic_mbx_send_ready(nic, vf);
		if (vf < MAX_LMAC) {
			nic->link[vf] = 0;
			nic->duplex[vf] = 0;
			nic->speed[vf] = 0;
		}
		ret = 1;
		break;
	case NIC_MBOX_MSG_QS_CFG:
		reg_addr = NIC_PF_QSET_0_127_CFG |
		    (mbx.qs.num << NIC_QS_ID_SHIFT);
		cfg = mbx.qs.cfg;
		nic_reg_write(nic, reg_addr, cfg);
		break;
	case NIC_MBOX_MSG_RQ_CFG:
		reg_addr = NIC_PF_QSET_0_127_RQ_0_7_CFG |
		    (mbx.rq.qs_num << NIC_QS_ID_SHIFT) |
		    (mbx.rq.rq_num << NIC_Q_NUM_SHIFT);
		nic_reg_write(nic, reg_addr, mbx.rq.cfg);
		break;
	case NIC_MBOX_MSG_RQ_BP_CFG:
		reg_addr = NIC_PF_QSET_0_127_RQ_0_7_BP_CFG |
		    (mbx.rq.qs_num << NIC_QS_ID_SHIFT) |
		    (mbx.rq.rq_num << NIC_Q_NUM_SHIFT);
		nic_reg_write(nic, reg_addr, mbx.rq.cfg);
		break;
	case NIC_MBOX_MSG_RQ_SW_SYNC:
		ret = nic_rcv_queue_sw_sync(nic);
		break;
	case NIC_MBOX_MSG_RQ_DROP_CFG:
		reg_addr = NIC_PF_QSET_0_127_RQ_0_7_DROP_CFG |
		    (mbx.rq.qs_num << NIC_QS_ID_SHIFT) |
		    (mbx.rq.rq_num << NIC_Q_NUM_SHIFT);
		nic_reg_write(nic, reg_addr, mbx.rq.cfg);
		break;
	case NIC_MBOX_MSG_SQ_CFG:
		reg_addr = NIC_PF_QSET_0_127_SQ_0_7_CFG |
		    (mbx.sq.qs_num << NIC_QS_ID_SHIFT) |
		    (mbx.sq.sq_num << NIC_Q_NUM_SHIFT);
		nic_reg_write(nic, reg_addr, mbx.sq.cfg);
		nic_tx_channel_cfg(nic, mbx.qs.num, &mbx.sq);
		break;
	case NIC_MBOX_MSG_SET_MAC:
		lmac = mbx.mac.vf_id;
		bgx = NIC_GET_BGX_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lmac]);
		lmac = NIC_GET_LMAC_FROM_VF_LMAC_MAP(nic->vf_lmac_map[lmac]);
		bgx_set_lmac_mac(nic->node, bgx, lmac, mbx.mac.mac_addr);
		break;
	case NIC_MBOX_MSG_SET_MAX_FRS:
		ret = nic_update_hw_frs(nic, mbx.frs.max_frs, mbx.frs.vf_id);
		break;
	case NIC_MBOX_MSG_CPI_CFG:
		nic_config_cpi(nic, &mbx.cpi_cfg);
		break;
	case NIC_MBOX_MSG_RSS_SIZE:
		nic_send_rss_size(nic, vf);
		goto unlock;
	case NIC_MBOX_MSG_RSS_CFG:
	case NIC_MBOX_MSG_RSS_CFG_CONT: /* fall through */
		nic_config_rss(nic, &mbx.rss_cfg);
		break;
	case NIC_MBOX_MSG_CFG_DONE:
		/* Last message of VF config msg sequence */
		nic->vf_info[vf].vf_enabled = TRUE;
		goto unlock;
	case NIC_MBOX_MSG_SHUTDOWN:
		/* First msg in VF teardown sequence */
		nic->vf_info[vf].vf_enabled = FALSE;
		break;
	case NIC_MBOX_MSG_BGX_STATS:
		nic_get_bgx_stats(nic, &mbx.bgx_stats);
		goto unlock;
	case NIC_MBOX_MSG_LOOPBACK:
		ret = nic_config_loopback(nic, &mbx.lbk);
		break;
	default:
		device_printf(nic->dev,
		    "Invalid msg from VF%d, msg 0x%x\n", vf, mbx.msg.msg);
		break;
	}

	if (ret == 0)
		nic_mbx_send_ack(nic, vf);
	else if (mbx.msg.msg != NIC_MBOX_MSG_READY)
		nic_mbx_send_nack(nic, vf);
unlock:
	nic->mbx_lock[vf] = FALSE;
}