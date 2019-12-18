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
struct radix_node_head {struct radix_node* rnh_treetop; int /*<<< orphan*/  rnh_walktree; int /*<<< orphan*/  rnh_lookup; int /*<<< orphan*/  rnh_matchaddr; int /*<<< orphan*/  rnh_deladdr; int /*<<< orphan*/  rnh_addaddr; struct radix_node* rnh_nodes; } ;
struct radix_node {int rn_flags; int rn_b; int /*<<< orphan*/  rn_key; struct radix_node* rn_l; struct radix_node* rn_p; struct radix_node* rn_r; } ;

/* Variables and functions */
 int /*<<< orphan*/  Bzero (struct radix_node_head*,int) ; 
 int RNF_ACTIVE ; 
 int RNF_ROOT ; 
 int /*<<< orphan*/  rn_addroute ; 
 int /*<<< orphan*/  rn_delete ; 
 int /*<<< orphan*/  rn_lookup ; 
 int /*<<< orphan*/  rn_match ; 
 struct radix_node* rn_newpair (int /*<<< orphan*/ ,int,struct radix_node*) ; 
 int /*<<< orphan*/  rn_ones ; 
 int /*<<< orphan*/  rn_walktree ; 
 int /*<<< orphan*/  rn_zeros ; 
 scalar_t__ rtmalloc (int,char*) ; 

int
rn_inithead(struct radix_node_head **head, int off)
{
	struct radix_node_head *rnh;
	struct radix_node *t, *tt, *ttt;
	if (*head)
		return (1);
	rnh = (struct radix_node_head *)rtmalloc(sizeof(*rnh), "rn_inithead");
	Bzero(rnh, sizeof (*rnh));
	*head = rnh;
	t = rn_newpair(rn_zeros, off, rnh->rnh_nodes);
	ttt = rnh->rnh_nodes + 2;
	t->rn_r = ttt;
	t->rn_p = t;
	tt = t->rn_l;
	tt->rn_flags = t->rn_flags = RNF_ROOT | RNF_ACTIVE;
	tt->rn_b = -1 - off;
	*ttt = *tt;
	ttt->rn_key = rn_ones;
	rnh->rnh_addaddr = rn_addroute;
	rnh->rnh_deladdr = rn_delete;
	rnh->rnh_matchaddr = rn_match;
	rnh->rnh_lookup = rn_lookup;
	rnh->rnh_walktree = rn_walktree;
	rnh->rnh_treetop = t;
	return (1);
}