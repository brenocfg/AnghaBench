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
struct ipu_irq_map {int irq; } ;
struct TYPE_2__ {unsigned int source; int irq; scalar_t__ bank; } ;

/* Variables and functions */
 int CONFIG_MX3_IPU_IRQS ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bank_lock ; 
 scalar_t__ irq_bank ; 
 TYPE_1__* irq_map ; 
 int /*<<< orphan*/  map_lock ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ipu_irq_map* src2map (unsigned int) ; 

int ipu_irq_map(unsigned int source)
{
	int i, ret = -ENOMEM;
	struct ipu_irq_map *map;

	might_sleep();

	mutex_lock(&map_lock);
	map = src2map(source);
	if (map) {
		pr_err("IPU: Source %u already mapped to IRQ %u\n", source, map->irq);
		ret = -EBUSY;
		goto out;
	}

	for (i = 0; i < CONFIG_MX3_IPU_IRQS; i++) {
		if (irq_map[i].source < 0) {
			unsigned long lock_flags;

			raw_spin_lock_irqsave(&bank_lock, lock_flags);
			irq_map[i].source = source;
			irq_map[i].bank = irq_bank + source / 32;
			raw_spin_unlock_irqrestore(&bank_lock, lock_flags);

			ret = irq_map[i].irq;
			pr_debug("IPU: mapped source %u to IRQ %u\n",
				 source, ret);
			break;
		}
	}
out:
	mutex_unlock(&map_lock);

	if (ret < 0)
		pr_err("IPU: couldn't map source %u: %d\n", source, ret);

	return ret;
}