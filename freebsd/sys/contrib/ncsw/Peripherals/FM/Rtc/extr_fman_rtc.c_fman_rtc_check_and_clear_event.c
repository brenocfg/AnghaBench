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
struct rtc_regs {int /*<<< orphan*/  tmr_tevent; int /*<<< orphan*/  tmr_temask; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

uint32_t fman_rtc_check_and_clear_event(struct rtc_regs *regs)
{
	uint32_t event;

	event = ioread32be(&regs->tmr_tevent);
	event &= ioread32be(&regs->tmr_temask);

	if (event)
		iowrite32be(event, &regs->tmr_tevent);
	return event;
}