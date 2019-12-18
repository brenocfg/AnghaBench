#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct val_anchors {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct TYPE_3__ {struct trust_anchor* key; } ;
struct trust_anchor {TYPE_1__ node; int /*<<< orphan*/  lock; scalar_t__ numDNSKEY; scalar_t__ numDS; scalar_t__ autr; scalar_t__ keylist; int /*<<< orphan*/  dclass; int /*<<< orphan*/  namelen; int /*<<< orphan*/  namelabs; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  anchors_delfunc (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  anchors_init_parents_locked (struct val_anchors*) ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ rbtree_search (int /*<<< orphan*/ ,struct trust_anchor*) ; 

void
anchors_delete_insecure(struct val_anchors* anchors, uint16_t c,
        uint8_t* nm)
{
	struct trust_anchor key;
	struct trust_anchor* ta;
	key.node.key = &key;
	key.name = nm;
	key.namelabs = dname_count_size_labels(nm, &key.namelen);
	key.dclass = c;
	lock_basic_lock(&anchors->lock);
	if(!(ta=(struct trust_anchor*)rbtree_search(anchors->tree, &key))) {
		lock_basic_unlock(&anchors->lock);
		/* nothing there */
		return;
	}
	/* lock it to drive away other threads that use it */
	lock_basic_lock(&ta->lock);
	/* see if its really an insecure point */
	if(ta->keylist || ta->autr || ta->numDS || ta->numDNSKEY) {
		lock_basic_unlock(&anchors->lock);
		lock_basic_unlock(&ta->lock);
		/* its not an insecure point, do not remove it */
		return;
	}

	/* remove from tree */
	(void)rbtree_delete(anchors->tree, &ta->node);
	anchors_init_parents_locked(anchors);
	lock_basic_unlock(&anchors->lock);

	/* actual free of data */
	lock_basic_unlock(&ta->lock);
	anchors_delfunc(&ta->node, NULL);
}