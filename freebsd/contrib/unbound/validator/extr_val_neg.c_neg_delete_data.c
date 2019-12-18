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
struct TYPE_2__ {scalar_t__ count; } ;
struct val_neg_zone {TYPE_1__ tree; } ;
struct val_neg_data {int in_use; scalar_t__ count; struct val_neg_data* name; scalar_t__ len; int /*<<< orphan*/  node; struct val_neg_data* parent; struct val_neg_zone* zone; } ;
struct val_neg_cache {int /*<<< orphan*/  use; struct val_neg_data* last; struct val_neg_data* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct val_neg_data*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  neg_delete_zone (struct val_neg_cache*,struct val_neg_zone*) ; 
 int /*<<< orphan*/  neg_lru_remove (struct val_neg_cache*,struct val_neg_data*) ; 
 int /*<<< orphan*/  rbtree_delete (TYPE_1__*,int /*<<< orphan*/ *) ; 

void neg_delete_data(struct val_neg_cache* neg, struct val_neg_data* el)
{
	struct val_neg_zone* z;
	struct val_neg_data* p, *np;
	if(!el) return;
	z = el->zone;
	log_assert(el->in_use);
	log_assert(el->count > 0);
	el->in_use = 0;

	/* remove it from the lru list */
	neg_lru_remove(neg, el);
	log_assert(neg->first != el && neg->last != el);
	
	/* go up the tree and reduce counts */
	p = el;
	while(p) {
		log_assert(p->count > 0);
		p->count --;
		p = p->parent;
	}

	/* delete 0 count items from tree */
	p = el;
	while(p && p->count == 0) {
		np = p->parent;
		(void)rbtree_delete(&z->tree, &p->node);
		neg->use -= p->len + sizeof(*p);
		free(p->name);
		free(p);
		p = np;
	}

	/* check if the zone is now unused */
	if(z->tree.count == 0) {
		neg_delete_zone(neg, z);
	}
}