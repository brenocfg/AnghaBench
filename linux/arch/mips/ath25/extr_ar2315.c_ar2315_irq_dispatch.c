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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR2315_IRQ_LCBUS_PCI ; 
 int /*<<< orphan*/  AR2315_IRQ_MISC ; 
 int /*<<< orphan*/  AR2315_IRQ_WLAN0 ; 
 int /*<<< orphan*/  ATH25_IRQ_CPU_CLOCK ; 
 int CAUSEF_IP2 ; 
 int CAUSEF_IP3 ; 
 int CAUSEF_IP5 ; 
 int CAUSEF_IP7 ; 
 int /*<<< orphan*/  do_IRQ (int /*<<< orphan*/ ) ; 
 int read_c0_cause () ; 
 int read_c0_status () ; 
 int /*<<< orphan*/  spurious_interrupt () ; 

__attribute__((used)) static void ar2315_irq_dispatch(void)
{
	u32 pending = read_c0_status() & read_c0_cause();

	if (pending & CAUSEF_IP3)
		do_IRQ(AR2315_IRQ_WLAN0);
#ifdef CONFIG_PCI_AR2315
	else if (pending & CAUSEF_IP5)
		do_IRQ(AR2315_IRQ_LCBUS_PCI);
#endif
	else if (pending & CAUSEF_IP2)
		do_IRQ(AR2315_IRQ_MISC);
	else if (pending & CAUSEF_IP7)
		do_IRQ(ATH25_IRQ_CPU_CLOCK);
	else
		spurious_interrupt();
}