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
struct rtc_regs {TYPE_1__* tmr_alarm; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_alarm_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_rtc_set_timer_alarm_l(struct rtc_regs *regs, int index, uint32_t val)
{
	iowrite32be(val, &regs->tmr_alarm[index].tmr_alarm_l);
}