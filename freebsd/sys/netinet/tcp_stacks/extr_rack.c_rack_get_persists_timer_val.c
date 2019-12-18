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
typedef  scalar_t__ uint32_t ;
struct tcpcb {int t_srtt; int t_rttvar; size_t t_rxtshift; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_rack {TYPE_1__ r_ctl; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PACE_TMR_PERSIT ; 
 int /*<<< orphan*/  TCPT_RANGESET (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t TCP_MAXRXTSHIFT ; 
 int TCP_RTT_SHIFT ; 
 int TICKS_2_MSEC (int) ; 
 int /*<<< orphan*/  rack_persist_max ; 
 int /*<<< orphan*/  rack_persist_min ; 
 int* tcp_backoff ; 

__attribute__((used)) static uint32_t
rack_get_persists_timer_val(struct tcpcb *tp, struct tcp_rack *rack)
{
	int32_t t;
	int32_t tt;
	uint32_t ret_val;

	t = TICKS_2_MSEC((tp->t_srtt >> TCP_RTT_SHIFT) + ((tp->t_rttvar * 4) >> TCP_RTT_SHIFT));
	TCPT_RANGESET(tt, t * tcp_backoff[tp->t_rxtshift],
	    rack_persist_min, rack_persist_max);
	if (tp->t_rxtshift < TCP_MAXRXTSHIFT)
		tp->t_rxtshift++;
	rack->r_ctl.rc_hpts_flags |= PACE_TMR_PERSIT;
	ret_val = (uint32_t)tt;
	return (ret_val);
}