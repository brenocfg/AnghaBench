#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* sctp_cwnd_update_after_timeout ) (struct sctp_tcb*,struct sctp_nets*) ;} ;
struct TYPE_4__ {int minrto; int initial_rto; int maxrto; TYPE_1__ cc_functions; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct sctp_nets {int RTO; scalar_t__ RTO_measured; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sctp_tcb*,struct sctp_nets*) ; 

__attribute__((used)) static void
sctp_backoff_on_timeout(struct sctp_tcb *stcb,
    struct sctp_nets *net,
    int win_probe,
    int num_marked, int num_abandoned)
{
	if (net->RTO == 0) {
		if (net->RTO_measured) {
			net->RTO = stcb->asoc.minrto;
		} else {
			net->RTO = stcb->asoc.initial_rto;
		}
	}
	net->RTO <<= 1;
	if (net->RTO > stcb->asoc.maxrto) {
		net->RTO = stcb->asoc.maxrto;
	}
	if ((win_probe == 0) && (num_marked || num_abandoned)) {
		/* We don't apply penalty to window probe scenarios */
		/* JRS - Use the congestion control given in the CC module */
		stcb->asoc.cc_functions.sctp_cwnd_update_after_timeout(stcb, net);
	}
}