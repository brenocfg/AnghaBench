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
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  prsctp_supported; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_nets {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,int,int) ; 
#define  SCTP_ASCONF 131 
#define  SCTP_ASCONF_ACK 130 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT2 ; 
#define  SCTP_FORWARD_CUM_TSN 129 
#define  SCTP_IFORWARD_CUM_TSN 128 
 int /*<<< orphan*/  sctp_asconf_cleanup (struct sctp_tcb*,struct sctp_nets*) ; 

__attribute__((used)) static void
sctp_process_unrecog_chunk(struct sctp_tcb *stcb, uint8_t chunk_type,
    struct sctp_nets *net)
{
	switch (chunk_type) {
	case SCTP_ASCONF_ACK:
	case SCTP_ASCONF:
		sctp_asconf_cleanup(stcb, net);
		break;
	case SCTP_IFORWARD_CUM_TSN:
	case SCTP_FORWARD_CUM_TSN:
		stcb->asoc.prsctp_supported = 0;
		break;
	default:
		SCTPDBG(SCTP_DEBUG_INPUT2,
		    "Peer does not support chunk type %d (0x%x).\n",
		    chunk_type, chunk_type);
		break;
	}
}