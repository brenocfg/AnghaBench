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
typedef  scalar_t__ uint16_t ;
struct val_anchors {int /*<<< orphan*/  lock; int /*<<< orphan*/  tree; } ;
struct TYPE_2__ {struct trust_anchor* key; } ;
struct trust_anchor {int namelabs; size_t namelen; scalar_t__ dclass; int /*<<< orphan*/  lock; struct trust_anchor* parent; int /*<<< orphan*/ * name; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ ,struct trust_anchor*,int /*<<< orphan*/ **) ; 

struct trust_anchor* 
anchors_lookup(struct val_anchors* anchors,
        uint8_t* qname, size_t qname_len, uint16_t qclass)
{
	struct trust_anchor key;
	struct trust_anchor* result;
	rbnode_type* res = NULL;
	key.node.key = &key;
	key.name = qname;
	key.namelabs = dname_count_labels(qname);
	key.namelen = qname_len;
	key.dclass = qclass;
	lock_basic_lock(&anchors->lock);
	if(rbtree_find_less_equal(anchors->tree, &key, &res)) {
		/* exact */
		result = (struct trust_anchor*)res;
	} else {
		/* smaller element (or no element) */
		int m;
		result = (struct trust_anchor*)res;
		if(!result || result->dclass != qclass) {
			lock_basic_unlock(&anchors->lock);
			return NULL;
		}
		/* count number of labels matched */
		(void)dname_lab_cmp(result->name, result->namelabs, key.name,
			key.namelabs, &m);
		while(result) { /* go up until qname is subdomain of stub */
			if(result->namelabs <= m)
				break;
			result = result->parent;
		}
	}
	if(result) {
		lock_basic_lock(&result->lock);
	}
	lock_basic_unlock(&anchors->lock);
	return result;
}