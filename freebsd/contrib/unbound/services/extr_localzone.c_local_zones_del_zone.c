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
struct local_zones {int /*<<< orphan*/  ztree; } ;
struct local_zone {int /*<<< orphan*/  lock; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_zone_delete (struct local_zone*) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ *,struct local_zone*) ; 
 int /*<<< orphan*/  set_kiddo_parents (struct local_zone*,struct local_zone*,int /*<<< orphan*/ ) ; 

void local_zones_del_zone(struct local_zones* zones, struct local_zone* z)
{
	/* fix up parents in tree */
	lock_rw_wrlock(&z->lock);
	set_kiddo_parents(z, z, z->parent);

	/* remove from tree */
	(void)rbtree_delete(&zones->ztree, z);

	/* delete the zone */
	lock_rw_unlock(&z->lock);
	local_zone_delete(z);
}