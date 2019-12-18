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
struct auth_zones {int /*<<< orphan*/  xtree; int /*<<< orphan*/  lock; int /*<<< orphan*/  ztree; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_xfer_cmp ; 
 int /*<<< orphan*/  auth_zone_cmp ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct auth_zones* auth_zones_create(void)
{
	struct auth_zones* az = (struct auth_zones*)calloc(1, sizeof(*az));
	if(!az) {
		log_err("out of memory");
		return NULL;
	}
	rbtree_init(&az->ztree, &auth_zone_cmp);
	rbtree_init(&az->xtree, &auth_xfer_cmp);
	lock_rw_init(&az->lock);
	lock_protect(&az->lock, &az->ztree, sizeof(az->ztree));
	lock_protect(&az->lock, &az->xtree, sizeof(az->xtree));
	/* also lock protects the rbnode's in struct auth_zone, auth_xfer */
	return az;
}