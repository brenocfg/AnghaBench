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
struct rdma_dev_addr {int dev_type; int /*<<< orphan*/  bound_dev_if; int /*<<< orphan*/  net; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int const ARPHRD_ETHER ; 
 int const ARPHRD_INFINIBAND ; 
 int ENODEV ; 
 int IB_GID_TYPE_IB ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int ib_find_cached_gid_by_port (struct ib_device*,union ib_gid*,int,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_protocol_ib (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_protocol_roce (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cma_validate_port(struct ib_device *device, u8 port,
				    enum ib_gid_type gid_type,
				    union ib_gid *gid,
				    const struct rdma_dev_addr *dev_addr)
{
	const int dev_type = dev_addr->dev_type;
	struct net_device *ndev;
	int ret = -ENODEV;

	if ((dev_type == ARPHRD_INFINIBAND) && !rdma_protocol_ib(device, port))
		return ret;

	if ((dev_type != ARPHRD_INFINIBAND) && rdma_protocol_ib(device, port))
		return ret;

	if (dev_type == ARPHRD_ETHER && rdma_protocol_roce(device, port)) {
		ndev = dev_get_by_index(dev_addr->net, dev_addr->bound_dev_if);
	} else {
		ndev = NULL;
		gid_type = IB_GID_TYPE_IB;
	}

	ret = ib_find_cached_gid_by_port(device, gid, gid_type, port,
					 ndev, NULL);

	if (ndev)
		dev_put(ndev);

	return ret;
}