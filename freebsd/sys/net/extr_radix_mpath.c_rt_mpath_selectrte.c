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
typedef  scalar_t__ uint32_t ;
struct rtentry {scalar_t__ rt_weight; } ;
struct radix_node {scalar_t__ rn_mask; struct radix_node* rn_dupedkey; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 scalar_t__ hashjitter ; 
 scalar_t__ rn_mpath_count (struct radix_node*) ; 

__attribute__((used)) static struct rtentry *
rt_mpath_selectrte(struct rtentry *rte, uint32_t hash)
{
	struct radix_node *rn0, *rn;
	uint32_t total_weight;
	struct rtentry *rt;
	int64_t weight;

	/* beyond here, we use rn as the master copy */
	rn0 = rn = (struct radix_node *)rte;
	rt = rte;

	/* gw selection by Modulo-N Hash (RFC2991) XXX need improvement? */
	total_weight = rn_mpath_count(rn0);
	hash += hashjitter;
	hash %= total_weight;
	for (weight = abs((int32_t)hash);
	     rt != NULL && weight >= rt->rt_weight; 
	     weight -= (rt == NULL) ? 0 : rt->rt_weight) {
		
		/* stay within the multipath routes */
		if (rn->rn_dupedkey && rn->rn_mask != rn->rn_dupedkey->rn_mask)
			break;
		rn = rn->rn_dupedkey;
		rt = (struct rtentry *)rn;
	}

	return (rt);
}