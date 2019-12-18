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
struct irq_data {scalar_t__ hwirq; } ;
struct exynos_wkup_irq {int mask; scalar_t__ hwirq; } ;
struct TYPE_2__ {struct exynos_wkup_irq* wkup_irq; } ;

/* Variables and functions */
 int ENOENT ; 
 int exynos_irqwake_intmask ; 
 TYPE_1__* pm_data ; 

__attribute__((used)) static int exynos_irq_set_wake(struct irq_data *data, unsigned int state)
{
	const struct exynos_wkup_irq *wkup_irq;

	if (!pm_data->wkup_irq)
		return -ENOENT;
	wkup_irq = pm_data->wkup_irq;

	while (wkup_irq->mask) {
		if (wkup_irq->hwirq == data->hwirq) {
			if (!state)
				exynos_irqwake_intmask |= wkup_irq->mask;
			else
				exynos_irqwake_intmask &= ~wkup_irq->mask;
			return 0;
		}
		++wkup_irq;
	}

	return -ENOENT;
}