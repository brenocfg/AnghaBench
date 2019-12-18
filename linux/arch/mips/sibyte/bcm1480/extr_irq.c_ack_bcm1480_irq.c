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
typedef  scalar_t__ uint32_t ;
typedef  unsigned int u64 ;
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_BCM1480_IMR_REGISTER (int /*<<< orphan*/ ,scalar_t__) ; 
 int BCM1480_IMR_HL_SPACING ; 
 unsigned int BCM1480_NR_IRQS ; 
 unsigned int BCM1480_NR_IRQS_HALF ; 
 int /*<<< orphan*/  IOADDR (int /*<<< orphan*/ ) ; 
 int NR_CPUS ; 
 scalar_t__ R_BCM1480_IMR_LDT_INTERRUPT_CLR_H ; 
 scalar_t__ R_BCM1480_IMR_LDT_INTERRUPT_H ; 
 unsigned int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bcm1480_irq_owner ; 
 int /*<<< orphan*/  bcm1480_mask_irq (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpu_logical_map (int) ; 
 scalar_t__ ht_eoi_space ; 

__attribute__((used)) static void ack_bcm1480_irq(struct irq_data *d)
{
	unsigned int irq_dirty, irq = d->irq;
	u64 pending;
	int k;

	/*
	 * If the interrupt was an HT interrupt, now is the time to
	 * clear it.  NOTE: we assume the HT bridge was set up to
	 * deliver the interrupts to all CPUs (which makes affinity
	 * changing easier for us)
	 */
	irq_dirty = irq;
	if ((irq_dirty >= BCM1480_NR_IRQS_HALF) && (irq_dirty <= BCM1480_NR_IRQS)) {
		irq_dirty -= BCM1480_NR_IRQS_HALF;
	}
	for (k=0; k<2; k++) { /* Loop through high and low LDT interrupts */
		pending = __raw_readq(IOADDR(A_BCM1480_IMR_REGISTER(bcm1480_irq_owner[irq],
						R_BCM1480_IMR_LDT_INTERRUPT_H + (k*BCM1480_IMR_HL_SPACING))));
		pending &= ((u64)1 << (irq_dirty));
		if (pending) {
#ifdef CONFIG_SMP
			int i;
			for (i=0; i<NR_CPUS; i++) {
				/*
				 * Clear for all CPUs so an affinity switch
				 * doesn't find an old status
				 */
				__raw_writeq(pending, IOADDR(A_BCM1480_IMR_REGISTER(cpu_logical_map(i),
								R_BCM1480_IMR_LDT_INTERRUPT_CLR_H + (k*BCM1480_IMR_HL_SPACING))));
			}
#else
			__raw_writeq(pending, IOADDR(A_BCM1480_IMR_REGISTER(0, R_BCM1480_IMR_LDT_INTERRUPT_CLR_H + (k*BCM1480_IMR_HL_SPACING))));
#endif

			/*
			 * Generate EOI.  For Pass 1 parts, EOI is a nop.  For
			 * Pass 2, the LDT world may be edge-triggered, but
			 * this EOI shouldn't hurt.  If they are
			 * level-sensitive, the EOI is required.
			 */
#ifdef CONFIG_PCI
			if (ht_eoi_space)
				*(uint32_t *)(ht_eoi_space+(irq<<16)+(7<<2)) = 0;
#endif
		}
	}
	bcm1480_mask_irq(bcm1480_irq_owner[irq], irq);
}