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
struct varent {struct varent* v_parent; struct varent** v_link; struct varent* v_right; struct varent* v_left; int /*<<< orphan*/  vec; int /*<<< orphan*/  v_flags; struct varent* v_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  balance (struct varent*,int,int) ; 
 int /*<<< orphan*/  blkfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct varent*) ; 

__attribute__((used)) static void
unsetv1(struct varent *p)
{
    struct varent *c, *pp;
    int f;

    /*
     * Free associated memory first to avoid complications.
     */
    blkfree(p->vec);
    xfree(p->v_name);
    /*
     * If p is missing one child, then we can move the other into where p is.
     * Otherwise, we find the predecessor of p, which is guaranteed to have no
     * right child, copy it into p, and move it's left child into it.
     */
    if (p->v_right == 0)
	c = p->v_left;
    else if (p->v_left == 0)
	c = p->v_right;
    else {
	for (c = p->v_left; c->v_right; c = c->v_right)
	    continue;
	p->v_name = c->v_name;
	p->v_flags = c->v_flags;
	p->vec = c->vec;
	p = c;
	c = p->v_left;
    }

    /*
     * Move c into where p is.
     */
    pp = p->v_parent;
    f = pp->v_right == p;
    if ((pp->v_link[f] = c) != 0)
	c->v_parent = pp;
    /*
     * Free the deleted node, and rebalance.
     */
    xfree(p);
    balance(pp, f, 1);
}