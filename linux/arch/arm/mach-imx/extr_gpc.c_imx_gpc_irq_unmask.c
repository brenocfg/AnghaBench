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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  imx_gpc_hwirq_unmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_chip_unmask_parent (struct irq_data*) ; 

__attribute__((used)) static void imx_gpc_irq_unmask(struct irq_data *d)
{
	imx_gpc_hwirq_unmask(d->hwirq);
	irq_chip_unmask_parent(d);
}