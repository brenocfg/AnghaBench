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
struct regmap {int /*<<< orphan*/  spinlock_flags; int /*<<< orphan*/  hwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hwspin_unlock_irqrestore (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void regmap_unlock_hwlock_irqrestore(void *__map)
{
	struct regmap *map = __map;

	hwspin_unlock_irqrestore(map->hwlock, &map->spinlock_flags);
}