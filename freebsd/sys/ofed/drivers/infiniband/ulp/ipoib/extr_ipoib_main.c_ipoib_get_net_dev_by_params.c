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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sockaddr {int dummy; } ;
struct net_device {int dummy; } ;
struct list_head {int dummy; } ;
struct ib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __ipoib_get_net_dev_by_params (struct list_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ib_gid const*,struct sockaddr const*,struct net_device**) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*) ; 
 int ib_find_cached_pkey (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_protocol_ib (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *
ipoib_get_net_dev_by_params(struct ib_device *dev, u8 port, u16 pkey,
    const union ib_gid *gid, const struct sockaddr *addr, void *client_data)
{
	struct net_device *net_dev;
	struct list_head *dev_list = client_data;
	u16 pkey_index;
	int matches;
	int ret;

	if (!rdma_protocol_ib(dev, port))
		return NULL;

	ret = ib_find_cached_pkey(dev, port, pkey, &pkey_index);
	if (ret)
		return NULL;

	if (!dev_list)
		return NULL;

	/* See if we can find a unique device matching the L2 parameters */
	matches = __ipoib_get_net_dev_by_params(dev_list, port, pkey_index,
						gid, NULL, &net_dev);

	switch (matches) {
	case 0:
		return NULL;
	case 1:
		return net_dev;
	}

	dev_put(net_dev);

	/* Couldn't find a unique device with L2 parameters only. Use L3
	 * address to uniquely match the net device */
	matches = __ipoib_get_net_dev_by_params(dev_list, port, pkey_index,
						gid, addr, &net_dev);
	switch (matches) {
	case 0:
		return NULL;
	default:
		dev_warn_ratelimited(&dev->dev,
				     "duplicate IP address detected\n");
		/* Fall through */
	case 1:
		return net_dev;
	}
}