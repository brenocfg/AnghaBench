#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bstp_port {int /*<<< orphan*/  bp_port_pv; int /*<<< orphan*/  bp_port_htime; int /*<<< orphan*/  bp_port_fdelay; int /*<<< orphan*/  bp_port_max_age; int /*<<< orphan*/  bp_port_msg_age; } ;
struct bstp_config_unit {int cu_role; int /*<<< orphan*/  cu_pv; int /*<<< orphan*/  cu_hello_time; int /*<<< orphan*/  cu_forward_delay; int /*<<< orphan*/  cu_max_age; int /*<<< orphan*/  cu_message_age; } ;

/* Variables and functions */
 int BSTP_PDU_INFERIOR ; 
 int BSTP_PDU_INFERIORALT ; 
 int BSTP_PDU_OTHER ; 
 int BSTP_PDU_REPEATED ; 
 int BSTP_PDU_SUPERIOR ; 
#define  BSTP_ROLE_ALTERNATE 131 
#define  BSTP_ROLE_BACKUP 130 
#define  BSTP_ROLE_DESIGNATED 129 
#define  BSTP_ROLE_ROOT 128 
 int /*<<< orphan*/  INFO_SAME ; 
 int /*<<< orphan*/  bstp_info_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstp_info_superior (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bstp_pdu_rcvtype(struct bstp_port *bp, struct bstp_config_unit *cu)
{
	int type;

	/* default return type */
	type = BSTP_PDU_OTHER;

	switch (cu->cu_role) {
	case BSTP_ROLE_DESIGNATED:
		if (bstp_info_superior(&bp->bp_port_pv, &cu->cu_pv))
			/* bpdu priority is superior */
			type = BSTP_PDU_SUPERIOR;
		else if (bstp_info_cmp(&bp->bp_port_pv, &cu->cu_pv) ==
		    INFO_SAME) {
			if (bp->bp_port_msg_age != cu->cu_message_age ||
			    bp->bp_port_max_age != cu->cu_max_age ||
			    bp->bp_port_fdelay != cu->cu_forward_delay ||
			    bp->bp_port_htime != cu->cu_hello_time)
				/* bpdu priority is equal and timers differ */
				type = BSTP_PDU_SUPERIOR;
			else
				/* bpdu is equal */
				type = BSTP_PDU_REPEATED;
		} else
			/* bpdu priority is worse */
			type = BSTP_PDU_INFERIOR;

		break;

	case BSTP_ROLE_ROOT:
	case BSTP_ROLE_ALTERNATE:
	case BSTP_ROLE_BACKUP:
		if (bstp_info_cmp(&bp->bp_port_pv, &cu->cu_pv) <= INFO_SAME)
			/*
			 * not a designated port and priority is the same or
			 * worse
			 */
			type = BSTP_PDU_INFERIORALT;
		break;
	}

	return (type);
}