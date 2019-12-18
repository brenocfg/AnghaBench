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
struct tcpcb {scalar_t__ t_state; int t_flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ TCPS_CLOSED ; 
 scalar_t__ TCPS_LISTEN ; 
 scalar_t__ TCPS_SYN_RECEIVED ; 
 scalar_t__ TCPS_SYN_SENT ; 
 int TF_SACK_PERMIT ; 
 scalar_t__ bbr_sack_not_required ; 

__attribute__((used)) static int
bbr_handoff_ok(struct tcpcb *tp)
{
	if ((tp->t_state == TCPS_CLOSED) ||
	    (tp->t_state == TCPS_LISTEN)) {
		/* Sure no problem though it may not stick */
		return (0);
	}
	if ((tp->t_state == TCPS_SYN_SENT) ||
	    (tp->t_state == TCPS_SYN_RECEIVED)) {
		/*
		 * We really don't know you have to get to ESTAB or beyond
		 * to tell.
		 */
		return (EAGAIN);
	}
	if ((tp->t_flags & TF_SACK_PERMIT) || bbr_sack_not_required) {
		return (0);
	}
	/*
	 * If we reach here we don't do SACK on this connection so we can
	 * never do rack.
	 */
	return (EINVAL);
}