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
struct TYPE_2__ {scalar_t__ auth_supported; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_nets {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT2 ; 
 int /*<<< orphan*/  sctp_asconf_send_nat_state_update (struct sctp_tcb*,struct sctp_nets*) ; 

__attribute__((used)) static int
sctp_handle_nat_missing_state(struct sctp_tcb *stcb,
    struct sctp_nets *net)
{
	/*
	 * return 0 means we want you to proceed with the abort non-zero
	 * means no abort processing
	 */
	if (stcb->asoc.auth_supported == 0) {
		SCTPDBG(SCTP_DEBUG_INPUT2, "sctp_handle_nat_missing_state: Peer does not support AUTH, cannot send an asconf\n");
		return (0);
	}
	sctp_asconf_send_nat_state_update(stcb, net);
	return (1);
}