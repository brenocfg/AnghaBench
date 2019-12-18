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
struct airq_iv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQIO_MSI ; 
 int /*<<< orphan*/  PCI_ISC ; 
 int /*<<< orphan*/  SIC_IRQ_MODE_D_SINGLE ; 
 int /*<<< orphan*/  airq_iv_end (struct airq_iv*) ; 
 int /*<<< orphan*/  airq_iv_get_data (struct airq_iv*,unsigned long) ; 
 unsigned long airq_iv_scan (struct airq_iv*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 size_t smp_processor_id () ; 
 struct airq_iv** zpci_ibv ; 
 scalar_t__ zpci_set_irq_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zpci_handle_cpu_local_irq(bool rescan)
{
	struct airq_iv *dibv = zpci_ibv[smp_processor_id()];
	unsigned long bit;
	int irqs_on = 0;

	for (bit = 0;;) {
		/* Scan the directed IRQ bit vector */
		bit = airq_iv_scan(dibv, bit, airq_iv_end(dibv));
		if (bit == -1UL) {
			if (!rescan || irqs_on++)
				/* End of second scan with interrupts on. */
				break;
			/* First scan complete, reenable interrupts. */
			if (zpci_set_irq_ctrl(SIC_IRQ_MODE_D_SINGLE, PCI_ISC))
				break;
			bit = 0;
			continue;
		}
		inc_irq_stat(IRQIO_MSI);
		generic_handle_irq(airq_iv_get_data(dibv, bit));
	}
}