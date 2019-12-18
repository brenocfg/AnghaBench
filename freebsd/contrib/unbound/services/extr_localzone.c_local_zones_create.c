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
struct local_zones {int /*<<< orphan*/  ztree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  local_zone_cmp ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct local_zones* 
local_zones_create(void)
{
	struct local_zones* zones = (struct local_zones*)calloc(1, 
		sizeof(*zones));
	if(!zones)
		return NULL;
	rbtree_init(&zones->ztree, &local_zone_cmp);
	lock_rw_init(&zones->lock);
	lock_protect(&zones->lock, &zones->ztree, sizeof(zones->ztree));
	/* also lock protects the rbnode's in struct local_zone */
	return zones;
}