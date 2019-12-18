#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int msg; } ;
struct TYPE_9__ {int speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  link_up; } ;
struct TYPE_8__ {int /*<<< orphan*/  ind_tbl_size; } ;
struct TYPE_6__ {int vf_id; int tns_mode; int /*<<< orphan*/  loopback_supported; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  node_id; } ;
union nic_mbx {TYPE_5__ msg; TYPE_4__ link_status; int /*<<< orphan*/  bgx_stats; TYPE_3__ rss_size; TYPE_1__ nic_cfg; } ;
typedef  int uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  rss_size; } ;
struct nicvf {int vf_id; int tns_mode; int speed; int /*<<< orphan*/  dev; int /*<<< orphan*/  ifp; int /*<<< orphan*/  link_up; int /*<<< orphan*/  duplex; void* pf_acked; TYPE_2__ rss_info; void* pf_nacked; int /*<<< orphan*/  loopback_supported; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int /*<<< orphan*/  NICVF_INTR_MBOX ; 
#define  NIC_MBOX_MSG_ACK 133 
#define  NIC_MBOX_MSG_BGX_LINK_CHANGE 132 
#define  NIC_MBOX_MSG_BGX_STATS 131 
#define  NIC_MBOX_MSG_NACK 130 
#define  NIC_MBOX_MSG_READY 129 
#define  NIC_MBOX_MSG_RSS_SIZE 128 
 int NIC_PF_VF_MAILBOX_SIZE ; 
 int NIC_VF_PF_MAILBOX_0_1 ; 
 void* TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setbaudrate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_read_bgx_stats (struct nicvf*,int /*<<< orphan*/ *) ; 
 int nicvf_reg_read (struct nicvf*,int) ; 

__attribute__((used)) static void
nicvf_handle_mbx_intr(struct nicvf *nic)
{
	union nic_mbx mbx = {};
	uint64_t *mbx_data;
	uint64_t mbx_addr;
	int i;

	mbx_addr = NIC_VF_PF_MAILBOX_0_1;
	mbx_data = (uint64_t *)&mbx;

	for (i = 0; i < NIC_PF_VF_MAILBOX_SIZE; i++) {
		*mbx_data = nicvf_reg_read(nic, mbx_addr);
		mbx_data++;
		mbx_addr += sizeof(uint64_t);
	}

	switch (mbx.msg.msg) {
	case NIC_MBOX_MSG_READY:
		nic->pf_acked = TRUE;
		nic->vf_id = mbx.nic_cfg.vf_id & 0x7F;
		nic->tns_mode = mbx.nic_cfg.tns_mode & 0x7F;
		nic->node = mbx.nic_cfg.node_id;
		memcpy(nic->hwaddr, mbx.nic_cfg.mac_addr, ETHER_ADDR_LEN);
		nic->loopback_supported = mbx.nic_cfg.loopback_supported;
		nic->link_up = FALSE;
		nic->duplex = 0;
		nic->speed = 0;
		break;
	case NIC_MBOX_MSG_ACK:
		nic->pf_acked = TRUE;
		break;
	case NIC_MBOX_MSG_NACK:
		nic->pf_nacked = TRUE;
		break;
	case NIC_MBOX_MSG_RSS_SIZE:
		nic->rss_info.rss_size = mbx.rss_size.ind_tbl_size;
		nic->pf_acked = TRUE;
		break;
	case NIC_MBOX_MSG_BGX_STATS:
		nicvf_read_bgx_stats(nic, &mbx.bgx_stats);
		nic->pf_acked = TRUE;
		break;
	case NIC_MBOX_MSG_BGX_LINK_CHANGE:
		nic->pf_acked = TRUE;
		nic->link_up = mbx.link_status.link_up;
		nic->duplex = mbx.link_status.duplex;
		nic->speed = mbx.link_status.speed;
		if (nic->link_up) {
			if_setbaudrate(nic->ifp, nic->speed * 1000000);
			if_link_state_change(nic->ifp, LINK_STATE_UP);
		} else {
			if_setbaudrate(nic->ifp, 0);
			if_link_state_change(nic->ifp, LINK_STATE_DOWN);
		}
		break;
	default:
		device_printf(nic->dev,
			   "Invalid message from PF, msg 0x%x\n", mbx.msg.msg);
		break;
	}
	nicvf_clear_intr(nic, NICVF_INTR_MBOX, 0);
}