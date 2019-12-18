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
typedef  int uint32_t ;
struct rtc_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int FMAN_RTC_TMR_CTRL_TE ; 
 int FMAN_RTC_TMR_CTRL_TMSR ; 
 int fman_rtc_get_timer_ctrl (struct rtc_regs*) ; 
 int /*<<< orphan*/  fman_rtc_set_timer_ctrl (struct rtc_regs*,int) ; 
 int /*<<< orphan*/  fman_rtc_set_timer_offset (struct rtc_regs*,int /*<<< orphan*/ ) ; 

void fman_rtc_enable(struct rtc_regs *regs, bool reset_clock)
{
	uint32_t tmr_ctrl = fman_rtc_get_timer_ctrl(regs);

	/* TODO check that no timestamping MACs are working in this stage. */
	if (reset_clock) {
		fman_rtc_set_timer_ctrl(regs, (tmr_ctrl | FMAN_RTC_TMR_CTRL_TMSR));

		DELAY(10);
		/* Clear TMR_OFF */
		fman_rtc_set_timer_offset(regs, 0);
	}

	fman_rtc_set_timer_ctrl(regs, (tmr_ctrl | FMAN_RTC_TMR_CTRL_TE));
}