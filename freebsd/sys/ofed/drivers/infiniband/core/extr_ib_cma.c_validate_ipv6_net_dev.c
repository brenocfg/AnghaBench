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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; } ;
struct sockaddr {int dummy; } ;
struct rtentry {struct net_device* rt_ifp; } ;
struct net_device {int /*<<< orphan*/  if_index; int /*<<< orphan*/  if_vnet; } ;
typedef  int /*<<< orphan*/  src_tmp ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTFREE_LOCKED (struct rtentry*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net_device* ip6_dev_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct rtentry* rtalloc1 (struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa6_embedscope (struct sockaddr_in6*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool validate_ipv6_net_dev(struct net_device *net_dev,
				  const struct sockaddr_in6 *dst_addr,
				  const struct sockaddr_in6 *src_addr)
{
#ifdef INET6
	struct sockaddr_in6 src_tmp = *src_addr;
	struct sockaddr_in6 dst_tmp = *dst_addr;
	struct net_device *dst_dev;
	struct rtentry *rte;
	bool ret;

	dst_dev = ip6_dev_find(net_dev->if_vnet, dst_tmp.sin6_addr,
	    net_dev->if_index);
	if (dst_dev != net_dev) {
		if (dst_dev != NULL)
			dev_put(dst_dev);
		return false;
	}
	dev_put(dst_dev);

	CURVNET_SET(net_dev->if_vnet);

	/*
	 * Make sure the socket address length field
	 * is set, else rtalloc1() will fail.
	 */
	src_tmp.sin6_len = sizeof(src_tmp);

	/*
	 * Make sure the scope ID gets embedded, else rtalloc1() will
	 * resolve to the loopback interface.
	 */
	src_tmp.sin6_scope_id = net_dev->if_index;
	sa6_embedscope(&src_tmp, 0);

	dst_tmp.sin6_scope_id = net_dev->if_index;
	sa6_embedscope(&dst_tmp, 0);

	/*
	 * Check for loopback after scope ID
	 * has been embedded:
	 */
	if (memcmp(&src_tmp.sin6_addr, &dst_tmp.sin6_addr,
	    sizeof(dst_tmp.sin6_addr)) == 0) {
		ret = true;
	} else {
		/* non-loopback case */
		rte = rtalloc1((struct sockaddr *)&src_tmp, 1, 0);
		if (rte != NULL) {
			ret = (rte->rt_ifp == net_dev);
			RTFREE_LOCKED(rte);
		} else {
			ret = false;
		}
	}
	CURVNET_RESTORE();
	return ret;
#else
	return false;
#endif
}