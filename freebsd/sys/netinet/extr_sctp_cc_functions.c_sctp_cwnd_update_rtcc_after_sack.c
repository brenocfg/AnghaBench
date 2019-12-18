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
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_cwnd_update_after_sack_common (struct sctp_tcb*,struct sctp_association*,int,int,int,int) ; 

__attribute__((used)) static void
sctp_cwnd_update_rtcc_after_sack(struct sctp_tcb *stcb,
    struct sctp_association *asoc,
    int accum_moved, int reneged_all, int will_exit)
{
	/* Passing a one argument at the last enables the rtcc algorithm */
	sctp_cwnd_update_after_sack_common(stcb, asoc, accum_moved, reneged_all, will_exit, 1);
}