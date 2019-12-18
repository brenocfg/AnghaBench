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
struct mlx4_zone_entry {int dummy; } ;
struct mlx4_zone_allocator {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __mlx4_alloc_from_zone (struct mlx4_zone_entry*,int,int,int,int*) ; 
 struct mlx4_zone_entry* __mlx4_find_zone_by_uid (struct mlx4_zone_allocator*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

u32 mlx4_zone_alloc_entries(struct mlx4_zone_allocator *zones, u32 uid, int count,
			    int align, u32 skip_mask, u32 *puid)
{
	struct mlx4_zone_entry *zone;
	int res = -1;

	spin_lock(&zones->lock);

	zone = __mlx4_find_zone_by_uid(zones, uid);

	if (NULL == zone)
		goto out;

	res = __mlx4_alloc_from_zone(zone, count, align, skip_mask, puid);

out:
	spin_unlock(&zones->lock);

	return res;
}