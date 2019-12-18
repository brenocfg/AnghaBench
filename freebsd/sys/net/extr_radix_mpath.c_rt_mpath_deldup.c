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
struct rtentry {int dummy; } ;
struct radix_node {int /*<<< orphan*/  rn_flags; int /*<<< orphan*/ * rn_dupedkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  RNF_ACTIVE ; 
 struct radix_node* rn_mpath_next (struct radix_node*) ; 

int
rt_mpath_deldup(struct rtentry *headrt, struct rtentry *rt)
{
        struct radix_node *t, *tt;

        if (!headrt || !rt)
            return (0);
        t = (struct radix_node *)headrt;
        tt = rn_mpath_next(t);
        while (tt) {
            if (tt == (struct radix_node *)rt) {
                t->rn_dupedkey = tt->rn_dupedkey;
                tt->rn_dupedkey = NULL;
    	        tt->rn_flags &= ~RNF_ACTIVE;
	        tt[1].rn_flags &= ~RNF_ACTIVE;
                return (1);
            }
            t = tt;
            tt = rn_mpath_next((struct radix_node *)t);
        }
        return (0);
}