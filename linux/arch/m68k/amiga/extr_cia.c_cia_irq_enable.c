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
struct irq_data {unsigned int irq; } ;

/* Variables and functions */
 unsigned char CIA_ICR_SETCLR ; 
 unsigned int IRQ_AMIGA_CIAA ; 
 unsigned int IRQ_AMIGA_CIAB ; 
 int /*<<< orphan*/  cia_able_irq (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  cia_set_irq (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  ciaa_base ; 
 int /*<<< orphan*/  ciab_base ; 

__attribute__((used)) static void cia_irq_enable(struct irq_data *data)
{
	unsigned int irq = data->irq;
	unsigned char mask;

	if (irq >= IRQ_AMIGA_CIAB) {
		mask = 1 << (irq - IRQ_AMIGA_CIAB);
		cia_set_irq(&ciab_base, mask);
		cia_able_irq(&ciab_base, CIA_ICR_SETCLR | mask);
	} else {
		mask = 1 << (irq - IRQ_AMIGA_CIAA);
		cia_set_irq(&ciaa_base, mask);
		cia_able_irq(&ciaa_base, CIA_ICR_SETCLR | mask);
	}
}