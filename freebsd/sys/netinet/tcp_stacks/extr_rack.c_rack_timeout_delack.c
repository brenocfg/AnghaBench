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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {int /*<<< orphan*/  t_flags; TYPE_1__* t_timers; } ;
struct TYPE_4__ {int /*<<< orphan*/  rc_hpts_flags; } ;
struct tcp_rack {TYPE_2__ r_ctl; } ;
struct TYPE_3__ {int tt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACE_TMR_DELACK ; 
 int /*<<< orphan*/  RACK_TO_FRM_DELACK ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_ACKNOW ; 
 int /*<<< orphan*/  TF_DELACK ; 
 int TT_STOPPED ; 
 int /*<<< orphan*/  rack_log_to_event (struct tcp_rack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcps_delack ; 

__attribute__((used)) static int
rack_timeout_delack(struct tcpcb *tp, struct tcp_rack *rack, uint32_t cts)
{
	if (tp->t_timers->tt_flags & TT_STOPPED) {
		return (1);
	}
	rack_log_to_event(rack, RACK_TO_FRM_DELACK, 0);
	tp->t_flags &= ~TF_DELACK;
	tp->t_flags |= TF_ACKNOW;
	TCPSTAT_INC(tcps_delack);
	rack->r_ctl.rc_hpts_flags &= ~PACE_TMR_DELACK;
	return (0);
}