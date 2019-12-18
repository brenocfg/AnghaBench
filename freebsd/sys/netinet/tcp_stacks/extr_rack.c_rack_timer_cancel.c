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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tcpcb {int dummy; } ;
struct TYPE_3__ {int rc_hpts_flags; int /*<<< orphan*/  rc_last_output_to; } ;
struct tcp_rack {int rc_tmr_stopped; TYPE_1__ r_ctl; TYPE_2__* rc_inp; } ;
struct TYPE_4__ {scalar_t__ inp_in_hpts; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPTS_REMOVE_OUTPUT ; 
 int PACE_PKT_OUTPUT ; 
 int PACE_TMR_MASK ; 
 scalar_t__ TSTMP_GEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rack_log_to_cancel (struct tcp_rack*,int,int) ; 
 int /*<<< orphan*/  tcp_hpts_remove (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rack_timer_cancel(struct tcpcb *tp, struct tcp_rack *rack, uint32_t cts, int line)
{
	uint8_t hpts_removed = 0;

	if ((rack->r_ctl.rc_hpts_flags & PACE_PKT_OUTPUT) &&
	    TSTMP_GEQ(cts, rack->r_ctl.rc_last_output_to)) {
		tcp_hpts_remove(rack->rc_inp, HPTS_REMOVE_OUTPUT);
		hpts_removed = 1;
	}
	if (rack->r_ctl.rc_hpts_flags & PACE_TMR_MASK) {
		rack->rc_tmr_stopped = rack->r_ctl.rc_hpts_flags & PACE_TMR_MASK;
		if (rack->rc_inp->inp_in_hpts &&
		    ((rack->r_ctl.rc_hpts_flags & PACE_PKT_OUTPUT) == 0)) {
			/*
			 * Canceling timer's when we have no output being
			 * paced. We also must remove ourselves from the
			 * hpts.
			 */
			tcp_hpts_remove(rack->rc_inp, HPTS_REMOVE_OUTPUT);
			hpts_removed = 1;
		}
		rack_log_to_cancel(rack, hpts_removed, line);
		rack->r_ctl.rc_hpts_flags &= ~(PACE_TMR_MASK);
	}
}