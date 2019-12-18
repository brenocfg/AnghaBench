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
typedef  int uint64_t ;
struct rtc_regs {TYPE_1__* tmr_etts; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_etts_h; int /*<<< orphan*/  tmr_etts_l; } ;

/* Variables and functions */
 scalar_t__ ioread32be (int /*<<< orphan*/ *) ; 

uint64_t fman_rtc_get_trigger_stamp(struct rtc_regs *regs, int id)
{
	uint64_t time;
	/* TMR_CNT_L must be read first to get an accurate value */
	time = (uint64_t)ioread32be(&regs->tmr_etts[id].tmr_etts_l);
	time |= ((uint64_t)ioread32be(&regs->tmr_etts[id].tmr_etts_h)
		<< 32);

	return time;
}