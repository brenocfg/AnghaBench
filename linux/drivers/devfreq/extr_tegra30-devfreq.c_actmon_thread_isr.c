#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_devfreq {TYPE_2__* devfreq; TYPE_3__* devices; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {TYPE_1__* config; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTMON_GLB_STATUS ; 
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  actmon_isr_device (struct tegra_devfreq*,TYPE_3__*) ; 
 int actmon_readl (struct tegra_devfreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_devfreq (TYPE_2__*) ; 

__attribute__((used)) static irqreturn_t actmon_thread_isr(int irq, void *data)
{
	struct tegra_devfreq *tegra = data;
	bool handled = false;
	unsigned int i;
	u32 val;

	mutex_lock(&tegra->devfreq->lock);

	val = actmon_readl(tegra, ACTMON_GLB_STATUS);
	for (i = 0; i < ARRAY_SIZE(tegra->devices); i++) {
		if (val & tegra->devices[i].config->irq_mask) {
			actmon_isr_device(tegra, tegra->devices + i);
			handled = true;
		}
	}

	if (handled)
		update_devfreq(tegra->devfreq);

	mutex_unlock(&tegra->devfreq->lock);

	return handled ? IRQ_HANDLED : IRQ_NONE;
}