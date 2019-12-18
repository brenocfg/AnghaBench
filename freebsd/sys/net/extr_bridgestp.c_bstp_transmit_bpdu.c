#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bstp_state {int dummy; } ;
struct TYPE_2__ {int pv_root_id; int pv_dbridge_id; int /*<<< orphan*/  pv_cost; } ;
struct bstp_port {int bp_port_id; int bp_desg_msg_age; int bp_desg_max_age; int bp_desg_htime; int bp_desg_fdelay; int bp_protover; TYPE_1__ bp_desg_pv; } ;
struct bstp_cbpdu {int /*<<< orphan*/  cbu_bpdutype; int /*<<< orphan*/  cbu_flags; void* cbu_forwarddelay; void* cbu_hellotime; void* cbu_maxage; void* cbu_messageage; void* cbu_portid; int /*<<< orphan*/  cbu_bridgeaddr; void* cbu_bridgepri; int /*<<< orphan*/  cbu_rootpathcost; int /*<<< orphan*/  cbu_rootaddr; void* cbu_rootpri; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK_ASSERT (struct bstp_state*) ; 
 int /*<<< orphan*/  BSTP_MSGTYPE_CFG ; 
 int /*<<< orphan*/  BSTP_MSGTYPE_RSTP ; 
#define  BSTP_PROTO_RSTP 129 
#define  BSTP_PROTO_STP 128 
 int /*<<< orphan*/  PV2ADDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_pdu_flags (struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_send_bpdu (struct bstp_state*,struct bstp_port*,struct bstp_cbpdu*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 

__attribute__((used)) static void
bstp_transmit_bpdu(struct bstp_state *bs, struct bstp_port *bp)
{
	struct bstp_cbpdu bpdu;

	BSTP_LOCK_ASSERT(bs);

	bpdu.cbu_rootpri = htons(bp->bp_desg_pv.pv_root_id >> 48);
	PV2ADDR(bp->bp_desg_pv.pv_root_id, bpdu.cbu_rootaddr);

	bpdu.cbu_rootpathcost = htonl(bp->bp_desg_pv.pv_cost);

	bpdu.cbu_bridgepri = htons(bp->bp_desg_pv.pv_dbridge_id >> 48);
	PV2ADDR(bp->bp_desg_pv.pv_dbridge_id, bpdu.cbu_bridgeaddr);

	bpdu.cbu_portid = htons(bp->bp_port_id);
	bpdu.cbu_messageage = htons(bp->bp_desg_msg_age);
	bpdu.cbu_maxage = htons(bp->bp_desg_max_age);
	bpdu.cbu_hellotime = htons(bp->bp_desg_htime);
	bpdu.cbu_forwarddelay = htons(bp->bp_desg_fdelay);

	bpdu.cbu_flags = bstp_pdu_flags(bp);

	switch (bp->bp_protover) {
		case BSTP_PROTO_STP:
			bpdu.cbu_bpdutype = BSTP_MSGTYPE_CFG;
			break;

		case BSTP_PROTO_RSTP:
			bpdu.cbu_bpdutype = BSTP_MSGTYPE_RSTP;
			break;
	}

	bstp_send_bpdu(bs, bp, &bpdu);
}