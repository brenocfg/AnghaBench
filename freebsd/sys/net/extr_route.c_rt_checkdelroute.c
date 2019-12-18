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
struct rtentry {struct rtentry* rt_chain; int /*<<< orphan*/  rt_gateway; } ;
struct rt_addrinfo {int /*<<< orphan*/ * rti_info; } ;
struct rt_delinfo {struct rtentry* head; int /*<<< orphan*/  rnh; struct rt_addrinfo info; } ;
struct radix_node {int dummy; } ;

/* Variables and functions */
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  rt_key (struct rtentry*) ; 
 int /*<<< orphan*/  rt_mask (struct rtentry*) ; 
 struct rtentry* rt_unlinkrte (int /*<<< orphan*/ ,struct rt_addrinfo*,int*) ; 

__attribute__((used)) static int
rt_checkdelroute(struct radix_node *rn, void *arg)
{
	struct rt_delinfo *di;
	struct rt_addrinfo *info;
	struct rtentry *rt;
	int error;

	di = (struct rt_delinfo *)arg;
	rt = (struct rtentry *)rn;
	info = &di->info;
	error = 0;

	info->rti_info[RTAX_DST] = rt_key(rt);
	info->rti_info[RTAX_NETMASK] = rt_mask(rt);
	info->rti_info[RTAX_GATEWAY] = rt->rt_gateway;

	rt = rt_unlinkrte(di->rnh, info, &error);
	if (rt == NULL) {
		/* Either not allowed or not matched. Skip entry */
		return (0);
	}

	/* Entry was unlinked. Add to the list and return */
	rt->rt_chain = di->head;
	di->head = rt;

	return (0);
}