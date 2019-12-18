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
struct radix_node {int rn_flags; int rn_bit; int /*<<< orphan*/  rn_key; struct radix_node* rn_left; struct radix_node* rn_parent; struct radix_node* rn_right; } ;
struct radix_head {struct radix_node* rnh_treetop; } ;

/* Variables and functions */
 int RNF_ACTIVE ; 
 int RNF_ROOT ; 
 struct radix_node* rn_newpair (int /*<<< orphan*/ ,int,struct radix_node*) ; 
 int /*<<< orphan*/  rn_ones ; 
 int /*<<< orphan*/  rn_zeros ; 

void
rn_inithead_internal(struct radix_head *rh, struct radix_node *base_nodes, int off)
{
	struct radix_node *t, *tt, *ttt;

	t = rn_newpair(rn_zeros, off, base_nodes);
	ttt = base_nodes + 2;
	t->rn_right = ttt;
	t->rn_parent = t;
	tt = t->rn_left;	/* ... which in turn is base_nodes */
	tt->rn_flags = t->rn_flags = RNF_ROOT | RNF_ACTIVE;
	tt->rn_bit = -1 - off;
	*ttt = *tt;
	ttt->rn_key = rn_ones;

	rh->rnh_treetop = t;
}