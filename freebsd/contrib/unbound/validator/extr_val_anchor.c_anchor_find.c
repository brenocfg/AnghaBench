#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct val_anchors {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct TYPE_4__ {struct trust_anchor* key; } ;
struct trust_anchor {int namelabs; size_t namelen; int /*<<< orphan*/  lock; int /*<<< orphan*/  dclass; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
struct TYPE_5__ {scalar_t__ key; } ;
typedef  TYPE_2__ rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* rbtree_search (int /*<<< orphan*/ ,struct trust_anchor*) ; 

struct trust_anchor*
anchor_find(struct val_anchors* anchors, uint8_t* name, int namelabs,
	size_t namelen, uint16_t dclass)
{
	struct trust_anchor key;
	rbnode_type* n;
	if(!name) return NULL;
	key.node.key = &key;
	key.name = name;
	key.namelabs = namelabs;
	key.namelen = namelen;
	key.dclass = dclass;
	lock_basic_lock(&anchors->lock);
	n = rbtree_search(anchors->tree, &key);
	if(n) {
		lock_basic_lock(&((struct trust_anchor*)n->key)->lock);
	}
	lock_basic_unlock(&anchors->lock);
	if(!n)
		return NULL;
	return (struct trust_anchor*)n->key;
}