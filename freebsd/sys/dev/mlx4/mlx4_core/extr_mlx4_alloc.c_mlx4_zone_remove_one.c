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
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_zone_entry {int dummy; } ;
struct mlx4_zone_allocator {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct mlx4_zone_entry* __mlx4_find_zone_by_uid (struct mlx4_zone_allocator*,int /*<<< orphan*/ ) ; 
 int __mlx4_zone_remove_one_entry (struct mlx4_zone_entry*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_zone_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mlx4_zone_remove_one(struct mlx4_zone_allocator *zones, u32 uid)
{
	struct mlx4_zone_entry *zone;
	int res;

	spin_lock(&zones->lock);

	zone = __mlx4_find_zone_by_uid(zones, uid);

	if (NULL == zone) {
		res = -1;
		goto out;
	}

	res = __mlx4_zone_remove_one_entry(zone);

out:
	spin_unlock(&zones->lock);
	kfree(zone);

	return res;
}