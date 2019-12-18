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
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  asconf_supported; int /*<<< orphan*/  peer_supports_nat; int /*<<< orphan*/  prsctp_supported; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,...) ; 
#define  SCTP_ADD_IP_ADDRESS 135 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT2 ; 
#define  SCTP_DEL_IP_ADDRESS 134 
#define  SCTP_ERROR_CAUSE_IND 133 
#define  SCTP_HAS_NAT_SUPPORT 132 
#define  SCTP_PRSCTP_SUPPORTED 131 
#define  SCTP_SET_PRIM_ADDR 130 
#define  SCTP_SUCCESS_REPORT 129 
#define  SCTP_SUPPORTED_CHUNK_EXT 128 

__attribute__((used)) static void
sctp_process_unrecog_param(struct sctp_tcb *stcb, uint16_t parameter_type)
{
	switch (parameter_type) {
		/* pr-sctp draft */
	case SCTP_PRSCTP_SUPPORTED:
		stcb->asoc.prsctp_supported = 0;
		break;
	case SCTP_SUPPORTED_CHUNK_EXT:
		break;
		/* draft-ietf-tsvwg-addip-sctp */
	case SCTP_HAS_NAT_SUPPORT:
		stcb->asoc.peer_supports_nat = 0;
		break;
	case SCTP_ADD_IP_ADDRESS:
	case SCTP_DEL_IP_ADDRESS:
	case SCTP_SET_PRIM_ADDR:
		stcb->asoc.asconf_supported = 0;
		break;
	case SCTP_SUCCESS_REPORT:
	case SCTP_ERROR_CAUSE_IND:
		SCTPDBG(SCTP_DEBUG_INPUT2, "Huh, the peer does not support success? or error cause?\n");
		SCTPDBG(SCTP_DEBUG_INPUT2,
		    "Turning off ASCONF to this strange peer\n");
		stcb->asoc.asconf_supported = 0;
		break;
	default:
		SCTPDBG(SCTP_DEBUG_INPUT2,
		    "Peer does not support param type %d (0x%x)??\n",
		    parameter_type, parameter_type);
		break;
	}
}