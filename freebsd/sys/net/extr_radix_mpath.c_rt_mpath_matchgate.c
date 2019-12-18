#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_len; } ;
struct rtentry {TYPE_2__* rt_gateway; TYPE_1__* rt_ifa; } ;
struct radix_node {int dummy; } ;
struct TYPE_4__ {scalar_t__ sa_family; scalar_t__ sa_len; } ;
struct TYPE_3__ {TYPE_2__* ifa_addr; } ;

/* Variables and functions */
 scalar_t__ AF_LINK ; 
 int /*<<< orphan*/  memcmp (TYPE_2__*,struct sockaddr*,scalar_t__) ; 
 struct radix_node* rn_mpath_next (struct radix_node*) ; 

struct rtentry *
rt_mpath_matchgate(struct rtentry *rt, struct sockaddr *gate)
{
	struct radix_node *rn;

	if (!gate || !rt->rt_gateway)
		return NULL;

	/* beyond here, we use rn as the master copy */
	rn = (struct radix_node *)rt;
	do {
		rt = (struct rtentry *)rn;
		/*
		 * we are removing an address alias that has 
		 * the same prefix as another address
		 * we need to compare the interface address because
		 * rt_gateway is a special sockadd_dl structure
		 */
		if (rt->rt_gateway->sa_family == AF_LINK) {
			if (!memcmp(rt->rt_ifa->ifa_addr, gate, gate->sa_len))
				break;
		}

		/*
		 * Check for other options:
		 * 1) Routes with 'real' IPv4/IPv6 gateway
		 * 2) Loopback host routes (another AF_LINK/sockadd_dl check)
		 * */
		if (rt->rt_gateway->sa_len == gate->sa_len &&
		    !memcmp(rt->rt_gateway, gate, gate->sa_len))
			break;
	} while ((rn = rn_mpath_next(rn)) != NULL);

	return (struct rtentry *)rn;
}