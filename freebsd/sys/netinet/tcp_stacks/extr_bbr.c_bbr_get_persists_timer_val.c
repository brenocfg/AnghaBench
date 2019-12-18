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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {scalar_t__ t_srtt; scalar_t__ t_rttvar; size_t t_rxtshift; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_bbr {TYPE_1__ r_ctl; } ;

/* Variables and functions */
 scalar_t__ BBR_INITIAL_RTO ; 
 int /*<<< orphan*/  PACE_TMR_PERSIT ; 
 int /*<<< orphan*/  TCPT_RANGESET_NOSLOP (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCP_RTT_SHIFT ; 
 scalar_t__ TICKS_2_USEC (scalar_t__) ; 
 int /*<<< orphan*/  bbr_persist_max ; 
 int /*<<< orphan*/  bbr_persist_min ; 
 int* tcp_backoff ; 

__attribute__((used)) static uint32_t
bbr_get_persists_timer_val(struct tcpcb *tp, struct tcp_bbr *bbr)
{
	uint64_t srtt, var;
	uint64_t ret_val;

	bbr->r_ctl.rc_hpts_flags |= PACE_TMR_PERSIT;
	if (tp->t_srtt == 0) {
		srtt = (uint64_t)BBR_INITIAL_RTO;
		var = 0;
	} else {
		srtt = ((uint64_t)TICKS_2_USEC(tp->t_srtt) >> TCP_RTT_SHIFT);
		var = ((uint64_t)TICKS_2_USEC(tp->t_rttvar) >> TCP_RTT_SHIFT);
	}
	TCPT_RANGESET_NOSLOP(ret_val, ((srtt + var) * tcp_backoff[tp->t_rxtshift]),
	    bbr_persist_min, bbr_persist_max);
	return ((uint32_t)ret_val);
}