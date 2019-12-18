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
typedef  int u32 ;
struct reset_controller_dev {int dummy; } ;
struct ccu_reset_map {int bit; scalar_t__ reg; } ;
struct ccu_reset {int /*<<< orphan*/  lock; scalar_t__ base; struct ccu_reset_map* reset_map; } ;

/* Variables and functions */
 struct ccu_reset* rcdev_to_ccu_reset (struct reset_controller_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ccu_reset_deassert(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	struct ccu_reset *ccu = rcdev_to_ccu_reset(rcdev);
	const struct ccu_reset_map *map = &ccu->reset_map[id];
	unsigned long flags;
	u32 reg;

	spin_lock_irqsave(ccu->lock, flags);

	reg = readl(ccu->base + map->reg);
	writel(reg | map->bit, ccu->base + map->reg);

	spin_unlock_irqrestore(ccu->lock, flags);

	return 0;
}