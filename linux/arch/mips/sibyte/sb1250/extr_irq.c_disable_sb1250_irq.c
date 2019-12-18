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
 int /*<<< orphan*/ * sb1250_irq_owner ; 
 int /*<<< orphan*/  sb1250_mask_irq (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void disable_sb1250_irq(struct irq_data *d)
{
	unsigned int irq = d->irq;

	sb1250_mask_irq(sb1250_irq_owner[irq], irq);
}