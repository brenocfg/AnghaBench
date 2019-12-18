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
struct iter_forwards {int /*<<< orphan*/  tree; } ;
struct TYPE_2__ {struct iter_forward_zone* key; } ;
struct iter_forward_zone {scalar_t__ dclass; int namelen; int /*<<< orphan*/ * name; scalar_t__ namelabs; TYPE_1__ node; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/ * RBTREE_NULL ; 
 scalar_t__ dname_is_root (int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_find_less_equal (int /*<<< orphan*/ ,struct iter_forward_zone*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * rbtree_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rbtree_next (int /*<<< orphan*/ *) ; 

int
forwards_next_root(struct iter_forwards* fwd, uint16_t* dclass)
{
	struct iter_forward_zone key;
	rbnode_type* n;
	struct iter_forward_zone* p;
	if(*dclass == 0) {
		/* first root item is first item in tree */
		n = rbtree_first(fwd->tree);
		if(n == RBTREE_NULL)
			return 0;
		p = (struct iter_forward_zone*)n;
		if(dname_is_root(p->name)) {
			*dclass = p->dclass;
			return 1;
		}
		/* root not first item? search for higher items */
		*dclass = p->dclass + 1;
		return forwards_next_root(fwd, dclass);
	}
	/* find class n in tree, we may get a direct hit, or if we don't
	 * this is the last item of the previous class so rbtree_next() takes
	 * us to the next root (if any) */
	key.node.key = &key;
	key.name = (uint8_t*)"\000";
	key.namelen = 1;
	key.namelabs = 0;
	key.dclass = *dclass;
	n = NULL;
	if(rbtree_find_less_equal(fwd->tree, &key, &n)) {
		/* exact */
		return 1;
	} else {
		/* smaller element */
		if(!n || n == RBTREE_NULL)
			return 0; /* nothing found */
		n = rbtree_next(n);
		if(n == RBTREE_NULL)
			return 0; /* no higher */
		p = (struct iter_forward_zone*)n;
		if(dname_is_root(p->name)) {
			*dclass = p->dclass;
			return 1;
		}
		/* not a root node, return next higher item */
		*dclass = p->dclass+1;
		return forwards_next_root(fwd, dclass);
	}
}