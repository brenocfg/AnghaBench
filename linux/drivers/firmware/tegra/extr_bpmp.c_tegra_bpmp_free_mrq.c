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
struct tegra_bpmp_mrq {int /*<<< orphan*/  list; } ;
struct tegra_bpmp {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct tegra_bpmp_mrq*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tegra_bpmp_mrq* tegra_bpmp_find_mrq (struct tegra_bpmp*,unsigned int) ; 

void tegra_bpmp_free_mrq(struct tegra_bpmp *bpmp, unsigned int mrq, void *data)
{
	struct tegra_bpmp_mrq *entry;
	unsigned long flags;

	spin_lock_irqsave(&bpmp->lock, flags);

	entry = tegra_bpmp_find_mrq(bpmp, mrq);
	if (!entry)
		goto unlock;

	list_del(&entry->list);
	devm_kfree(bpmp->dev, entry);

unlock:
	spin_unlock_irqrestore(&bpmp->lock, flags);
}