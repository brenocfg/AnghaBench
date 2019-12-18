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
struct local_zone {scalar_t__ dclass; int /*<<< orphan*/  node; int /*<<< orphan*/  lock; struct local_zone* parent; int /*<<< orphan*/  namelabs; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ RBTREE_NULL ; 
 scalar_t__ dname_strict_subdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rbtree_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_kiddo_parents(struct local_zone* z, struct local_zone* match, 
	struct local_zone* newp)
{
	/* both zones and z are locked already */
	/* in the sorted rbtree, the kiddies of z are located after z */
	/* z must be present in the tree */
	struct local_zone* p = z;
	p = (struct local_zone*)rbtree_next(&p->node);
	while(p!=(struct local_zone*)RBTREE_NULL &&
		p->dclass == z->dclass && dname_strict_subdomain(p->name,
		p->namelabs, z->name, z->namelabs)) {
		/* update parent ptr */
		/* only when matches with existing parent pointer, so that
		 * deeper child structures are not touched, i.e.
		 * update of x, and a.x, b.x, f.b.x, g.b.x, c.x, y
		 * gets to update a.x, b.x and c.x */
		lock_rw_wrlock(&p->lock);
		if(p->parent == match)
			p->parent = newp;
		lock_rw_unlock(&p->lock);
		p = (struct local_zone*)rbtree_next(&p->node);
	}
}