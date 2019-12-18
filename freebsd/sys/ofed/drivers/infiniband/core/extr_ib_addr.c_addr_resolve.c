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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; } ;
struct rdma_dev_addr {int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;
struct epoch_tracker {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int MAX_ADDR_LEN ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int addr4_resolve (struct sockaddr_in*,struct sockaddr_in const*,struct rdma_dev_addr*,int /*<<< orphan*/ *,struct net_device**) ; 
 int addr6_resolve (struct sockaddr_in6*,struct sockaddr_in6 const*,struct rdma_dev_addr*,int /*<<< orphan*/ *,struct net_device**) ; 
 int addr_resolve_neigh (struct net_device*,struct sockaddr const*,int /*<<< orphan*/ *,struct rdma_dev_addr*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 

__attribute__((used)) static int addr_resolve(struct sockaddr *src_in,
			const struct sockaddr *dst_in,
			struct rdma_dev_addr *addr)
{
	struct epoch_tracker et;
	struct net_device *ndev = NULL;
	u8 edst[MAX_ADDR_LEN];
	int ret;

	if (dst_in->sa_family != src_in->sa_family)
		return -EINVAL;

	NET_EPOCH_ENTER(et);
	switch (src_in->sa_family) {
	case AF_INET:
		ret = addr4_resolve((struct sockaddr_in *)src_in,
				    (const struct sockaddr_in *)dst_in,
				    addr, edst, &ndev);
		break;
	case AF_INET6:
		ret = addr6_resolve((struct sockaddr_in6 *)src_in,
				    (const struct sockaddr_in6 *)dst_in, addr,
				    edst, &ndev);
		break;
	default:
		ret = -EADDRNOTAVAIL;
		break;
	}
	NET_EPOCH_EXIT(et);

	/* check for error */
	if (ret != 0)
		return ret;

	/* store MAC addresses and check for loopback */
	ret = addr_resolve_neigh(ndev, dst_in, edst, addr);

	/* set belonging VNET, if any */
	addr->net = dev_net(ndev);
	dev_put(ndev);

	return ret;
}