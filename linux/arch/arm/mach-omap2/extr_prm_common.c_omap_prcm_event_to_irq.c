#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr_irqs; int base_irq; TYPE_1__* irqs; } ;
struct TYPE_3__ {int offset; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_2__* prcm_irq_setup ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int omap_prcm_event_to_irq(const char *name)
{
	int i;

	if (!prcm_irq_setup || !name)
		return -ENOENT;

	for (i = 0; i < prcm_irq_setup->nr_irqs; i++)
		if (!strcmp(prcm_irq_setup->irqs[i].name, name))
			return prcm_irq_setup->base_irq +
				prcm_irq_setup->irqs[i].offset;

	return -ENOENT;
}