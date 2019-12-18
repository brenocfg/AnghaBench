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
struct irq_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_get_irq_data (unsigned int) ; 
 struct irq_cfg* irqd_cfg (int /*<<< orphan*/ ) ; 

struct irq_cfg *irq_cfg(unsigned int irq)
{
	return irqd_cfg(irq_get_irq_data(irq));
}