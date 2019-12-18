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
 int FMAN_RTC_TMR_CTRL_FS ; 
 int FMAN_RTC_TMR_TEVENT_PP1 ; 
 int FMAN_RTC_TMR_TEVENT_PP2 ; 
 int /*<<< orphan*/  fman_rtc_disable_interupt (struct rtc_regs*,int) ; 
 int fman_rtc_get_timer_ctrl (struct rtc_regs*) ; 
 int /*<<< orphan*/  fman_rtc_set_timer_ctrl (struct rtc_regs*,int) ; 
 int /*<<< orphan*/  fman_rtc_set_timer_fiper (struct rtc_regs*,int,int) ; 

void fman_rtc_clear_periodic_pulse(struct rtc_regs *regs, int id)
{
	uint32_t tmp_reg;
	if (id == 0)
		tmp_reg = FMAN_RTC_TMR_TEVENT_PP1;
	else
		tmp_reg = FMAN_RTC_TMR_TEVENT_PP2;
	fman_rtc_disable_interupt(regs, tmp_reg);

	tmp_reg = fman_rtc_get_timer_ctrl(regs);
	if (tmp_reg & FMAN_RTC_TMR_CTRL_FS)
		fman_rtc_set_timer_ctrl(regs, tmp_reg & ~FMAN_RTC_TMR_CTRL_FS);

	fman_rtc_set_timer_fiper(regs, id, 0xFFFFFFFF);
}