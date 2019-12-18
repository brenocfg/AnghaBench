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
struct val_anchors {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct TYPE_2__ {struct trust_anchor* key; } ;
struct trust_anchor {int /*<<< orphan*/  namelen; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  dclass; int /*<<< orphan*/ * name; TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  anchor_new_ta (struct val_anchors*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anchors_init_parents_locked (struct val_anchors*) ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ ,struct trust_anchor*) ; 

int
anchors_add_insecure(struct val_anchors* anchors, uint16_t c, uint8_t* nm)
{
	struct trust_anchor key;
	key.node.key = &key;
	key.name = nm;
	key.namelabs = dname_count_size_labels(nm, &key.namelen);
	key.dclass = c;
	lock_basic_lock(&anchors->lock);
	if(rbtree_search(anchors->tree, &key)) {
		lock_basic_unlock(&anchors->lock);
		/* nothing to do, already an anchor or insecure point */
		return 1;
	}
	if(!anchor_new_ta(anchors, nm, key.namelabs, key.namelen, c, 0)) {
		log_err("out of memory");
		lock_basic_unlock(&anchors->lock);
		return 0;
	}
	/* no other contents in new ta, because it is insecure point */
	anchors_init_parents_locked(anchors);
	lock_basic_unlock(&anchors->lock);
	return 1;
}