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
 int FMAN_RTC_TMR_CTRL_PP1L ; 
 int FMAN_RTC_TMR_CTRL_PP2L ; 
 int FMAN_RTC_TMR_TEVENT_ETS1 ; 
 int FMAN_RTC_TMR_TEVENT_ETS2 ; 
 int /*<<< orphan*/  fman_rtc_disable_interupt (struct rtc_regs*,int) ; 
 int fman_rtc_get_timer_ctrl (struct rtc_regs*) ; 
 int /*<<< orphan*/  fman_rtc_set_timer_ctrl (struct rtc_regs*,int) ; 

void fman_rtc_clear_external_trigger(struct rtc_regs *regs, int id)
{
	uint32_t    tmpReg, tmp_ctrl;

	if (id == 0)
		tmpReg = FMAN_RTC_TMR_TEVENT_ETS1;
	else
		tmpReg = FMAN_RTC_TMR_TEVENT_ETS2;
	fman_rtc_disable_interupt(regs, tmpReg);

	if (id == 0)
		tmpReg = FMAN_RTC_TMR_CTRL_PP1L;
	else
		tmpReg = FMAN_RTC_TMR_CTRL_PP2L;
	tmp_ctrl = fman_rtc_get_timer_ctrl(regs);
	if (tmp_ctrl & tmpReg)
		fman_rtc_set_timer_ctrl(regs, tmp_ctrl & ~tmpReg);
}