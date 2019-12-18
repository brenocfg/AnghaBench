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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCFEPORT_EPFR ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 unsigned int irq2ebit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intc_irq_ack(struct irq_data *d)
{
	unsigned int ebit = irq2ebit(d->irq);

	__raw_writeb(0x1 << ebit, MCFEPORT_EPFR);
}