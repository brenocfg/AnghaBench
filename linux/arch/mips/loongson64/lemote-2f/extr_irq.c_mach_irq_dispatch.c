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

/* Variables and functions */
 unsigned int CAUSEF_IP2 ; 
 unsigned int CAUSEF_IP3 ; 
 unsigned int CAUSEF_IP6 ; 
 unsigned int CAUSEF_IP7 ; 
 int /*<<< orphan*/  LOONGSON_TIMER_IRQ ; 
 int /*<<< orphan*/  LOONGSON_UART_IRQ ; 
 int /*<<< orphan*/  bonito_irqdispatch () ; 
 int /*<<< orphan*/  do_IRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_perfcnt_IRQ () ; 
 int /*<<< orphan*/  i8259_irqdispatch () ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

void mach_irq_dispatch(unsigned int pending)
{
	if (pending & CAUSEF_IP7)
		do_IRQ(LOONGSON_TIMER_IRQ);
	else if (pending & CAUSEF_IP6) {	/* North Bridge, Perf counter */
		do_perfcnt_IRQ();
		bonito_irqdispatch();
	} else if (pending & CAUSEF_IP3)	/* CPU UART */
		do_IRQ(LOONGSON_UART_IRQ);
	else if (pending & CAUSEF_IP2)	/* South Bridge */
		i8259_irqdispatch();
	else
		spurious_interrupt();
}