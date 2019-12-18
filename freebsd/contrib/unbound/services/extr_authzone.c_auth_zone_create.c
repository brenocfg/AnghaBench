#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct auth_zones {int /*<<< orphan*/  ztree; } ;
struct TYPE_2__ {struct auth_zone* key; } ;
struct auth_zone {size_t namelen; int /*<<< orphan*/  lock; TYPE_1__ node; int /*<<< orphan*/  name; int /*<<< orphan*/  data; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  dclass; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  auth_data_cmp ; 
 int /*<<< orphan*/  auth_zone_delete (struct auth_zone*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct auth_zone*) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

struct auth_zone*
auth_zone_create(struct auth_zones* az, uint8_t* nm, size_t nmlen,
	uint16_t dclass)
{
	struct auth_zone* z = (struct auth_zone*)calloc(1, sizeof(*z));
	if(!z) {
		return NULL;
	}
	z->node.key = z;
	z->dclass = dclass;
	z->namelen = nmlen;
	z->namelabs = dname_count_labels(nm);
	z->name = memdup(nm, nmlen);
	if(!z->name) {
		free(z);
		return NULL;
	}
	rbtree_init(&z->data, &auth_data_cmp);
	lock_rw_init(&z->lock);
	lock_protect(&z->lock, &z->name, sizeof(*z)-sizeof(rbnode_type));
	lock_rw_wrlock(&z->lock);
	/* z lock protects all, except rbtree itself, which is az->lock */
	if(!rbtree_insert(&az->ztree, &z->node)) {
		lock_rw_unlock(&z->lock);
		auth_zone_delete(z);
		log_warn("duplicate auth zone");
		return NULL;
	}
	return z;
}