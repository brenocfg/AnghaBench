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
struct rtentry {scalar_t__ rt_ifp; scalar_t__ rt_mtu; int rt_flags; } ;
struct radix_node {int dummy; } ;
struct if_mtuinfo {scalar_t__ ifp; scalar_t__ mtu; } ;

/* Variables and functions */
 int RTF_FIXEDMTU ; 
 int RTF_GATEWAY ; 
 int RTF_HOST ; 

__attribute__((used)) static int
if_updatemtu_cb(struct radix_node *rn, void *arg)
{
	struct rtentry *rt;
	struct if_mtuinfo *ifmtu;

	rt = (struct rtentry *)rn;
	ifmtu = (struct if_mtuinfo *)arg;

	if (rt->rt_ifp != ifmtu->ifp)
		return (0);

	if (rt->rt_mtu >= ifmtu->mtu) {
		/* We have to decrease mtu regardless of flags */
		rt->rt_mtu = ifmtu->mtu;
		return (0);
	}

	/*
	 * New MTU is bigger. Check if are allowed to alter it
	 */
	if ((rt->rt_flags & (RTF_FIXEDMTU | RTF_GATEWAY | RTF_HOST)) != 0) {

		/*
		 * Skip routes with user-supplied MTU and
		 * non-interface routes
		 */
		return (0);
	}

	/* We are safe to update route MTU */
	rt->rt_mtu = ifmtu->mtu;

	return (0);
}