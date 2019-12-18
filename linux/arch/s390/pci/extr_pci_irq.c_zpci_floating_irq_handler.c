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
struct airq_struct {int dummy; } ;
struct airq_iv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQIO_MSI ; 
 int /*<<< orphan*/  IRQIO_PCF ; 
 int /*<<< orphan*/  PCI_ISC ; 
 int /*<<< orphan*/  SIC_IRQ_MODE_SINGLE ; 
 int /*<<< orphan*/  airq_iv_end (struct airq_iv*) ; 
 int /*<<< orphan*/  airq_iv_get_data (struct airq_iv*,unsigned long) ; 
 int /*<<< orphan*/  airq_iv_lock (struct airq_iv*,unsigned long) ; 
 unsigned long airq_iv_scan (struct airq_iv*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  airq_iv_unlock (struct airq_iv*,unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 struct airq_iv** zpci_ibv ; 
 struct airq_iv* zpci_sbv ; 
 scalar_t__ zpci_set_irq_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zpci_floating_irq_handler(struct airq_struct *airq, bool floating)
{
	unsigned long si, ai;
	struct airq_iv *aibv;
	int irqs_on = 0;

	inc_irq_stat(IRQIO_PCF);
	for (si = 0;;) {
		/* Scan adapter summary indicator bit vector */
		si = airq_iv_scan(zpci_sbv, si, airq_iv_end(zpci_sbv));
		if (si == -1UL) {
			if (irqs_on++)
				/* End of second scan with interrupts on. */
				break;
			/* First scan complete, reenable interrupts. */
			if (zpci_set_irq_ctrl(SIC_IRQ_MODE_SINGLE, PCI_ISC))
				break;
			si = 0;
			continue;
		}

		/* Scan the adapter interrupt vector for this device. */
		aibv = zpci_ibv[si];
		for (ai = 0;;) {
			ai = airq_iv_scan(aibv, ai, airq_iv_end(aibv));
			if (ai == -1UL)
				break;
			inc_irq_stat(IRQIO_MSI);
			airq_iv_lock(aibv, ai);
			generic_handle_irq(airq_iv_get_data(aibv, ai));
			airq_iv_unlock(aibv, ai);
		}
	}
}