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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int rc_hpts_flags; scalar_t__ rc_last_delay_val; } ;
struct tcp_bbr {int rc_timer_first; scalar_t__ rc_pacer_started; int rc_tmr_stopped; TYPE_1__ r_ctl; TYPE_2__* rc_inp; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {scalar_t__ inp_in_hpts; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPTS_REMOVE_OUTPUT ; 
 int PACE_TMR_MASK ; 
 scalar_t__ TSTMP_GT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bbr_log_to_cancel (struct tcp_bbr*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  tcp_hpts_remove (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bbr_timer_cancel(struct tcp_bbr *bbr, int32_t line, uint32_t cts)
{
	if (bbr->r_ctl.rc_hpts_flags & PACE_TMR_MASK) {
		uint8_t hpts_removed = 0;

		if (bbr->rc_inp->inp_in_hpts &&
		    (bbr->rc_timer_first == 1)) {
			/*
			 * If we are canceling timer's when we have the
			 * timer ahead of the output being paced. We also
			 * must remove ourselves from the hpts.
			 */
			hpts_removed = 1;
			tcp_hpts_remove(bbr->rc_inp, HPTS_REMOVE_OUTPUT);
			if (bbr->r_ctl.rc_last_delay_val) {
				/* Update the last hptsi delay too */
				uint32_t time_since_send;

				if (TSTMP_GT(cts, bbr->rc_pacer_started))
					time_since_send = cts - bbr->rc_pacer_started;
				else
					time_since_send = 0;
				if (bbr->r_ctl.rc_last_delay_val > time_since_send) {
					/* Cut down our slot time */
					bbr->r_ctl.rc_last_delay_val -= time_since_send;
				} else {
					bbr->r_ctl.rc_last_delay_val = 0;
				}
				bbr->rc_pacer_started = cts;
			}
		}
		bbr->rc_timer_first = 0;
		bbr_log_to_cancel(bbr, line, cts, hpts_removed);
		bbr->rc_tmr_stopped = bbr->r_ctl.rc_hpts_flags & PACE_TMR_MASK;
		bbr->r_ctl.rc_hpts_flags &= ~(PACE_TMR_MASK);
	}
}