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
struct rtc_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  FMAN_RTC_TMR_CTRL_TMSR ; 
 int /*<<< orphan*/  fman_rtc_set_timer_ctrl (struct rtc_regs*,int /*<<< orphan*/ ) ; 

void fman_rtc_timers_soft_reset(struct rtc_regs *regs)
{
	fman_rtc_set_timer_ctrl(regs, FMAN_RTC_TMR_CTRL_TMSR);
	DELAY(10);
	fman_rtc_set_timer_ctrl(regs, 0);
}