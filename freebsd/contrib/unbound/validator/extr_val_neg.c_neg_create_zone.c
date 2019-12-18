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
struct val_neg_zone {scalar_t__ count; struct val_neg_zone* parent; int /*<<< orphan*/  node; scalar_t__ len; int /*<<< orphan*/  name; } ;
struct val_neg_cache {int /*<<< orphan*/  tree; int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 struct val_neg_zone* neg_closest_zone_parent (struct val_neg_cache*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 struct val_neg_zone* neg_zone_chain (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,struct val_neg_zone*) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct val_neg_zone* neg_create_zone(struct val_neg_cache* neg,
	uint8_t* nm, size_t nm_len, uint16_t dclass)
{
	struct val_neg_zone* zone;
	struct val_neg_zone* parent;
	struct val_neg_zone* p, *np;
	int labs = dname_count_labels(nm);

	/* find closest enclosing parent zone that (still) exists */
	parent = neg_closest_zone_parent(neg, nm, nm_len, labs, dclass);
	if(parent && query_dname_compare(parent->name, nm) == 0)
		return parent; /* already exists, weird */
	/* if parent exists, it is in use */
	log_assert(!parent || parent->count > 0);
	zone = neg_zone_chain(nm, nm_len, labs, dclass, parent);
	if(!zone) {
		return NULL;
	}

	/* insert the list of zones into the tree */
	p = zone;
	while(p) {
		np = p->parent;
		/* mem use */
		neg->use += sizeof(struct val_neg_zone) + p->len;
		/* insert in tree */
		(void)rbtree_insert(&neg->tree, &p->node);
		/* last one needs proper parent pointer */
		if(np == NULL)
			p->parent = parent;
		p = np;
	}
	return zone;
}