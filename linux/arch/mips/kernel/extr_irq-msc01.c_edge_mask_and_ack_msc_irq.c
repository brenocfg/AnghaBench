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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 scalar_t__ MSC01_IC_EOI ; 
 scalar_t__ MSC01_IC_SUP ; 
 int MSC01_IC_SUP_EDGE_BIT ; 
 int /*<<< orphan*/  MSCIC_READ (scalar_t__,int) ; 
 int /*<<< orphan*/  MSCIC_WRITE (scalar_t__,int) ; 
 int /*<<< orphan*/  cpu_has_veic ; 
 int /*<<< orphan*/  mask_msc_irq (struct irq_data*) ; 

__attribute__((used)) static void edge_mask_and_ack_msc_irq(struct irq_data *d)
{
	unsigned int irq = d->irq;

	mask_msc_irq(d);
	if (!cpu_has_veic)
		MSCIC_WRITE(MSC01_IC_EOI, 0);
	else {
		u32 r;
		MSCIC_READ(MSC01_IC_SUP+irq*8, r);
		MSCIC_WRITE(MSC01_IC_SUP+irq*8, r | ~MSC01_IC_SUP_EDGE_BIT);
		MSCIC_WRITE(MSC01_IC_SUP+irq*8, r);
	}
}