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
typedef  int (* walktree_f_t ) (struct radix_node*,void*) ;
struct radix_node {scalar_t__ rn_bit; int rn_flags; struct radix_node* rn_dupedkey; struct radix_node* rn_left; struct radix_node* rn_right; struct radix_node* rn_parent; } ;
struct radix_head {struct radix_node* rnh_treetop; } ;

/* Variables and functions */
 int RNF_ROOT ; 
 int stub1 (struct radix_node*,void*) ; 

int
rn_walktree(struct radix_head *h, walktree_f_t *f, void *w)
{
	int error;
	struct radix_node *base, *next;
	struct radix_node *rn = h->rnh_treetop;
	/*
	 * This gets complicated because we may delete the node
	 * while applying the function f to it, so we need to calculate
	 * the successor node in advance.
	 */

	/* First time through node, go left */
	while (rn->rn_bit >= 0)
		rn = rn->rn_left;
	for (;;) {
		base = rn;
		/* If at right child go back up, otherwise, go right */
		while (rn->rn_parent->rn_right == rn
		       && (rn->rn_flags & RNF_ROOT) == 0)
			rn = rn->rn_parent;
		/* Find the next *leaf* since next node might vanish, too */
		for (rn = rn->rn_parent->rn_right; rn->rn_bit >= 0;)
			rn = rn->rn_left;
		next = rn;
		/* Process leaves */
		while ((rn = base)) {
			base = rn->rn_dupedkey;
			if (!(rn->rn_flags & RNF_ROOT)
			    && (error = (*f)(rn, w)))
				return (error);
		}
		rn = next;
		if (rn->rn_flags & RNF_ROOT)
			return (0);
	}
	/* NOTREACHED */
}