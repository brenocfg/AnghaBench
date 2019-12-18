#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct rdma_dev_addr {int /*<<< orphan*/  net; scalar_t__ bound_dev_if; } ;
struct net_device {int if_flags; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int ENODEV ; 
 int IFF_LOOPBACK ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net_device* ip6_dev_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* ip_dev_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_copy_addr (struct rdma_dev_addr*,struct net_device*,int /*<<< orphan*/ *) ; 

int rdma_translate_ip(const struct sockaddr *addr,
		      struct rdma_dev_addr *dev_addr)
{
	struct net_device *dev;
	int ret;

	if (dev_addr->bound_dev_if) {
		dev = dev_get_by_index(dev_addr->net, dev_addr->bound_dev_if);
	} else switch (addr->sa_family) {
#ifdef INET
	case AF_INET:
		dev = ip_dev_find(dev_addr->net,
			((const struct sockaddr_in *)addr)->sin_addr.s_addr);
		break;
#endif
#ifdef INET6
	case AF_INET6:
		dev = ip6_dev_find(dev_addr->net,
			((const struct sockaddr_in6 *)addr)->sin6_addr, 0);
		break;
#endif
	default:
		dev = NULL;
		break;
	}

	if (dev != NULL) {
		/* disallow connections through 127.0.0.1 itself */
		if (dev->if_flags & IFF_LOOPBACK)
			ret = -EINVAL;
		else
			ret = rdma_copy_addr(dev_addr, dev, NULL);
		dev_put(dev);
	} else {
		ret = -ENODEV;
	}
	return ret;
}