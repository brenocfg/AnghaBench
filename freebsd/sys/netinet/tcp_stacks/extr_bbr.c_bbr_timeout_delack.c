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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {int /*<<< orphan*/  t_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_bbr {TYPE_1__ r_ctl; scalar_t__ rc_all_timers_stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_TO_FRM_DELACK ; 
 int /*<<< orphan*/  PACE_TMR_DELACK ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_ACKNOW ; 
 int /*<<< orphan*/  TF_DELACK ; 
 int /*<<< orphan*/  bbr_log_to_event (struct tcp_bbr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_delack ; 

__attribute__((used)) static int
bbr_timeout_delack(struct tcpcb *tp, struct tcp_bbr *bbr, uint32_t cts)
{
	if (bbr->rc_all_timers_stopped) {
		return (1);
	}
	bbr_log_to_event(bbr, cts, BBR_TO_FRM_DELACK);
	tp->t_flags &= ~TF_DELACK;
	tp->t_flags |= TF_ACKNOW;
	TCPSTAT_INC(tcps_delack);
	bbr->r_ctl.rc_hpts_flags &= ~PACE_TMR_DELACK;
	return (0);
}