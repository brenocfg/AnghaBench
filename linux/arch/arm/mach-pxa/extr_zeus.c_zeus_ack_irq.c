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
 int /*<<< orphan*/  ZEUS_CPLD_ISA_IRQ ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zeus_irq_to_bitmask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zeus_ack_irq(struct irq_data *d)
{
	__raw_writew(zeus_irq_to_bitmask(d->irq), ZEUS_CPLD_ISA_IRQ);
}