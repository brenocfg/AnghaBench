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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct local_zones {int /*<<< orphan*/  ztree; } ;
struct local_zone {int /*<<< orphan*/  lock; int /*<<< orphan*/  parent; int /*<<< orphan*/  node; } ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 struct local_zone* local_zone_create (int /*<<< orphan*/ *,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_zone_delete (struct local_zone*) ; 
 int /*<<< orphan*/  local_zones_find (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_kiddo_parents (struct local_zone*,int /*<<< orphan*/ ,struct local_zone*) ; 

struct local_zone* local_zones_add_zone(struct local_zones* zones,
	uint8_t* name, size_t len, int labs, uint16_t dclass,
	enum localzone_type tp)
{
	/* create */
	struct local_zone* z = local_zone_create(name, len, labs, tp, dclass);
	if(!z) {
		free(name);
		return NULL;
	}
	lock_rw_wrlock(&z->lock);

	/* find the closest parent */
	z->parent = local_zones_find(zones, name, len, labs, dclass);

	/* insert into the tree */
	if(!rbtree_insert(&zones->ztree, &z->node)) {
		/* duplicate entry! */
		lock_rw_unlock(&z->lock);
		local_zone_delete(z);
		log_err("internal: duplicate entry in local_zones_add_zone");
		return NULL;
	}

	/* set parent pointers right */
	set_kiddo_parents(z, z->parent, z);

	lock_rw_unlock(&z->lock);
	return z;
}