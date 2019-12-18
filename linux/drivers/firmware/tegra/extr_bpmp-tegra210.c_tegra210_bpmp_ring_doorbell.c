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
struct tegra_bpmp {struct tegra210_bpmp* priv; } ;
struct tegra210_bpmp {struct irq_data* tx_irq_data; } ;
struct irq_data {TYPE_1__* chip; } ;
struct TYPE_2__ {int (* irq_retrigger ) (struct irq_data*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct irq_data*) ; 

__attribute__((used)) static int tegra210_bpmp_ring_doorbell(struct tegra_bpmp *bpmp)
{
	struct tegra210_bpmp *priv = bpmp->priv;
	struct irq_data *irq_data = priv->tx_irq_data;

	/*
	 * Tegra Legacy Interrupt Controller (LIC) is used to notify BPMP of
	 * available messages
	 */
	if (irq_data->chip->irq_retrigger)
		return irq_data->chip->irq_retrigger(irq_data);

	return -EINVAL;
}