#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct rtentry {TYPE_2__* rt_gateway; TYPE_1__* rt_ifa; } ;
struct rib_head {int /*<<< orphan*/  head; struct radix_node* (* rnh_lookup ) (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ;} ;
struct radix_node {int rn_flags; } ;
struct TYPE_5__ {scalar_t__ sa_family; scalar_t__ sa_len; } ;
struct TYPE_4__ {TYPE_2__* ifa_addr; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int EEXIST ; 
 int RNF_ROOT ; 
 scalar_t__ bcmp (TYPE_2__*,TYPE_2__*,scalar_t__) ; 
 struct radix_node* rn_mpath_next (struct radix_node*) ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 struct radix_node* stub1 (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 

int
rt_mpath_conflict(struct rib_head *rnh, struct rtentry *rt,
    struct sockaddr *netmask)
{
	struct radix_node *rn, *rn1;
	struct rtentry *rt1;

	rn = (struct radix_node *)rt;
	rn1 = rnh->rnh_lookup(rt_key(rt), netmask, &rnh->head);
	if (!rn1 || rn1->rn_flags & RNF_ROOT)
		return (0);

	/* key/mask are the same. compare gateway for all multipaths */
	do {
		rt1 = (struct rtentry *)rn1;

		/* sanity: no use in comparing the same thing */
		if (rn1 == rn)
			continue;
        
		if (rt1->rt_gateway->sa_family == AF_LINK) {
			if (rt1->rt_ifa->ifa_addr->sa_len != rt->rt_ifa->ifa_addr->sa_len ||
			    bcmp(rt1->rt_ifa->ifa_addr, rt->rt_ifa->ifa_addr, 
			    rt1->rt_ifa->ifa_addr->sa_len))
				continue;
		} else {
			if (rt1->rt_gateway->sa_len != rt->rt_gateway->sa_len ||
			    bcmp(rt1->rt_gateway, rt->rt_gateway,
			    rt1->rt_gateway->sa_len))
				continue;
		}

		/* all key/mask/gateway are the same.  conflicting entry. */
		return (EEXIST);
	} while ((rn1 = rn_mpath_next(rn1)) != NULL);

	return (0);
}