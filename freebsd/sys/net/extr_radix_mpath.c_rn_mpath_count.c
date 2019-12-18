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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtentry {scalar_t__ rt_weight; } ;
struct radix_node {int dummy; } ;

/* Variables and functions */
 struct radix_node* rn_mpath_next (struct radix_node*) ; 

uint32_t
rn_mpath_count(struct radix_node *rn)
{
	uint32_t i = 0;
	struct rtentry *rt;
	
	while (rn != NULL) {
		rt = (struct rtentry *)rn;
		i += rt->rt_weight;
		rn = rn_mpath_next(rn);
	}
	return (i);
}