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
struct local_zones {int /*<<< orphan*/  lock; int /*<<< orphan*/  ztree; } ;
struct local_zone {int /*<<< orphan*/  lock; int /*<<< orphan*/  node; } ;
typedef  enum localzone_type { ____Placeholder_localzone_type } localzone_type ;

/* Variables and functions */
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 struct local_zone* local_zone_create (int /*<<< orphan*/ *,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_zone_delete (struct local_zone*) ; 
 struct local_zone* local_zones_find (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_warn (char*,char*) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct local_zone*
lz_enter_zone_dname(struct local_zones* zones, uint8_t* nm, size_t len, 
	int labs, enum localzone_type t, uint16_t c)
{
	struct local_zone* z = local_zone_create(nm, len, labs, t, c);
	if(!z) {
		free(nm);
		log_err("out of memory");
		return NULL;
	}

	/* add to rbtree */
	lock_rw_wrlock(&zones->lock);
	lock_rw_wrlock(&z->lock);
	if(!rbtree_insert(&zones->ztree, &z->node)) {
		struct local_zone* oldz;
		char str[256];
		dname_str(nm, str);
		log_warn("duplicate local-zone %s", str);
		lock_rw_unlock(&z->lock);
		/* save zone name locally before deallocation,
		 * otherwise, nm is gone if we zone_delete now. */
		oldz = z;
		/* find the correct zone, so not an error for duplicate */
		z = local_zones_find(zones, nm, len, labs, c);
		lock_rw_wrlock(&z->lock);
		lock_rw_unlock(&zones->lock);
		local_zone_delete(oldz);
		return z;
	}
	lock_rw_unlock(&zones->lock);
	return z;
}