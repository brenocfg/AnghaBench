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
struct mlx4_zone_allocator {int flags; scalar_t__ mask; scalar_t__ last_uid; int /*<<< orphan*/  lock; int /*<<< orphan*/  prios; int /*<<< orphan*/  entries; } ;
typedef  enum mlx4_zone_alloc_flags { ____Placeholder_mlx4_zone_alloc_flags } mlx4_zone_alloc_flags ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mlx4_zone_allocator* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct mlx4_zone_allocator *mlx4_zone_allocator_create(enum mlx4_zone_alloc_flags flags)
{
	struct mlx4_zone_allocator *zones = kmalloc(sizeof(*zones), GFP_KERNEL);

	if (NULL == zones)
		return NULL;

	INIT_LIST_HEAD(&zones->entries);
	INIT_LIST_HEAD(&zones->prios);
	spin_lock_init(&zones->lock);
	zones->last_uid = 0;
	zones->mask = 0;
	zones->flags = flags;

	return zones;
}