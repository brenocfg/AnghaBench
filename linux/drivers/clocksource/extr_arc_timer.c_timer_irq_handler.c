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
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_REG_TIMER0_CTRL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int TIMER_CTRL_NH ; 
 int /*<<< orphan*/  arc_clockevent_device ; 
 int clockevent_state_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 struct clock_event_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_aux_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t timer_irq_handler(int irq, void *dev_id)
{
	/*
	 * Note that generic IRQ core could have passed @evt for @dev_id if
	 * irq_set_chip_and_handler() asked for handle_percpu_devid_irq()
	 */
	struct clock_event_device *evt = this_cpu_ptr(&arc_clockevent_device);
	int irq_reenable = clockevent_state_periodic(evt);

	/*
	 * 1. ACK the interrupt
	 *    - For ARC700, any write to CTRL reg ACKs it, so just rewrite
	 *      Count when [N]ot [H]alted bit.
	 *    - For HS3x, it is a bit subtle. On taken count-down interrupt,
	 *      IP bit [3] is set, which needs to be cleared for ACK'ing.
	 *      The write below can only update the other two bits, hence
	 *      explicitly clears IP bit
	 * 2. Re-arm interrupt if periodic by writing to IE bit [0]
	 */
	write_aux_reg(ARC_REG_TIMER0_CTRL, irq_reenable | TIMER_CTRL_NH);

	evt->event_handler(evt);

	return IRQ_HANDLED;
}