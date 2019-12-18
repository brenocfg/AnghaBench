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
struct sctp_tcb {int dummy; } ;
struct sctp_nets {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_cwnd_update_after_ecn_echo_common (struct sctp_tcb*,struct sctp_nets*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sctp_cwnd_update_after_ecn_echo(struct sctp_tcb *stcb, struct sctp_nets *net,
    int in_window, int num_pkt_lost)
{
	/* Passing a zero argument in last disables the rtcc algorithm */
	sctp_cwnd_update_after_ecn_echo_common(stcb, net, in_window, num_pkt_lost, 0);
}