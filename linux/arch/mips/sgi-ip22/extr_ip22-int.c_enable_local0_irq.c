#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {scalar_t__ irq; } ;
struct TYPE_2__ {int imask0; } ;

/* Variables and functions */
 int SGINT_LOCAL0 ; 
 scalar_t__ SGI_MAP_0_IRQ ; 
 TYPE_1__* sgint ; 

__attribute__((used)) static void enable_local0_irq(struct irq_data *d)
{
	/* don't allow mappable interrupt to be enabled from setup_irq,
	 * we have our own way to do so */
	if (d->irq != SGI_MAP_0_IRQ)
		sgint->imask0 |= (1 << (d->irq - SGINT_LOCAL0));
}