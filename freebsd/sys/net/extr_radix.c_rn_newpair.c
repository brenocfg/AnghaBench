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
struct radix_node {int rn_bit; int rn_bmask; int rn_offset; struct radix_node* rn_ybro; struct radix_node* rn_twin; scalar_t__ rn_info; scalar_t__ rn_mklist; int /*<<< orphan*/  rn_flags; struct radix_node* rn_parent; scalar_t__ rn_key; int /*<<< orphan*/ * rn_dupedkey; int /*<<< orphan*/ * rn_mask; int /*<<< orphan*/ * rn_right; struct radix_node* rn_left; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  RNF_ACTIVE ; 
 struct radix_node* rn_clist ; 
 int /*<<< orphan*/  rn_nodenum ; 

__attribute__((used)) static struct radix_node *
rn_newpair(void *v, int b, struct radix_node nodes[2])
{
	struct radix_node *tt = nodes, *t = tt + 1;
	t->rn_bit = b;
	t->rn_bmask = 0x80 >> (b & 7);
	t->rn_left = tt;
	t->rn_offset = b >> 3;

#if 0  /* XXX perhaps we should fill these fields as well. */
	t->rn_parent = t->rn_right = NULL;

	tt->rn_mask = NULL;
	tt->rn_dupedkey = NULL;
	tt->rn_bmask = 0;
#endif
	tt->rn_bit = -1;
	tt->rn_key = (caddr_t)v;
	tt->rn_parent = t;
	tt->rn_flags = t->rn_flags = RNF_ACTIVE;
	tt->rn_mklist = t->rn_mklist = 0;
#ifdef RN_DEBUG
	tt->rn_info = rn_nodenum++; t->rn_info = rn_nodenum++;
	tt->rn_twin = t;
	tt->rn_ybro = rn_clist;
	rn_clist = tt;
#endif
	return (t);
}