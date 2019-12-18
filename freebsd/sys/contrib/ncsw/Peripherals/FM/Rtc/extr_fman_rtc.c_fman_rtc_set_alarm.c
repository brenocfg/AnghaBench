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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtc_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMAN_RTC_TMR_TEVENT_ALM1 ; 
 int /*<<< orphan*/  FMAN_RTC_TMR_TEVENT_ALM2 ; 
 int /*<<< orphan*/  fman_rtc_enable_interupt (struct rtc_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_rtc_set_timer_alarm (struct rtc_regs*,int,int /*<<< orphan*/ ) ; 

void fman_rtc_set_alarm(struct rtc_regs *regs, int id, uint32_t val, bool enable)
{
	uint32_t    tmpReg;
	fman_rtc_set_timer_alarm(regs, id, val);
	if (enable) {
		if (id == 0)
			tmpReg = FMAN_RTC_TMR_TEVENT_ALM1;
		else
			tmpReg = FMAN_RTC_TMR_TEVENT_ALM2;
		fman_rtc_enable_interupt(regs, tmpReg);
	}
}