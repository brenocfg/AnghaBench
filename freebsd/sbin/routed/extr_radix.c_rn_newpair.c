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
struct radix_node {int rn_b; int rn_bmask; int rn_off; struct radix_node* rn_ybro; struct radix_node* rn_twin; scalar_t__ rn_info; int /*<<< orphan*/  rn_flags; struct radix_node* rn_p; scalar_t__ rn_key; struct radix_node* rn_l; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  RNF_ACTIVE ; 
 struct radix_node* rn_clist ; 
 int /*<<< orphan*/  rn_nodenum ; 

__attribute__((used)) static struct radix_node *
rn_newpair(void *v, int b, struct radix_node nodes[2])
{
	struct radix_node *tt = nodes, *t = tt + 1;
	t->rn_b = b; t->rn_bmask = 0x80 >> (b & 7);
	t->rn_l = tt; t->rn_off = b >> 3;
	tt->rn_b = -1; tt->rn_key = (caddr_t)v; tt->rn_p = t;
	tt->rn_flags = t->rn_flags = RNF_ACTIVE;
#ifdef RN_DEBUG
	tt->rn_info = rn_nodenum++; t->rn_info = rn_nodenum++;
	tt->rn_twin = t; tt->rn_ybro = rn_clist; rn_clist = tt;
#endif
	return t;
}