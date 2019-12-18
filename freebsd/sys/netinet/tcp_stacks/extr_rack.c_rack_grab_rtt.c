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
typedef  scalar_t__ uint32_t ;
struct tcpcb {int t_srtt; } ;
struct tcp_rack {scalar_t__ rc_rack_rtt; } ;

/* Variables and functions */
 scalar_t__ RACK_INITIAL_RTO ; 
 int TCP_RTT_SHIFT ; 
 scalar_t__ TICKS_2_MSEC (int) ; 

__attribute__((used)) static uint32_t
rack_grab_rtt(struct tcpcb *tp, struct tcp_rack *rack)
{
	/*
	 * We want the rack_rtt which is the
	 * last rtt we measured. However if that
	 * does not exist we fallback to the srtt (which
	 * we probably will never do) and then as a last
	 * resort we use RACK_INITIAL_RTO if no srtt is
	 * yet set.
	 */
	if (rack->rc_rack_rtt)
		return(rack->rc_rack_rtt);
	else if (tp->t_srtt == 0)
		return(RACK_INITIAL_RTO);
	return (TICKS_2_MSEC(tp->t_srtt >> TCP_RTT_SHIFT));
}