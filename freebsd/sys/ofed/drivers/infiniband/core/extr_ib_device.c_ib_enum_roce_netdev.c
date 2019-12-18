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
typedef  scalar_t__ u8 ;
struct net_device {int if_flags; } ;
struct ib_device {struct net_device* (* get_netdev ) (struct ib_device*,scalar_t__) ;} ;
typedef  scalar_t__ (* roce_netdev_filter ) (struct ib_device*,scalar_t__,struct net_device*,void*) ;
typedef  int /*<<< orphan*/  (* roce_netdev_callback ) (struct ib_device*,scalar_t__,struct net_device*,void*) ;

/* Variables and functions */
 int IFF_DYING ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 scalar_t__ rdma_end_port (struct ib_device*) ; 
 scalar_t__ rdma_protocol_roce (struct ib_device*,scalar_t__) ; 
 scalar_t__ rdma_start_port (struct ib_device*) ; 
 struct net_device* stub1 (struct ib_device*,scalar_t__) ; 

void ib_enum_roce_netdev(struct ib_device *ib_dev,
			 roce_netdev_filter filter,
			 void *filter_cookie,
			 roce_netdev_callback cb,
			 void *cookie)
{
	u8 port;

	for (port = rdma_start_port(ib_dev); port <= rdma_end_port(ib_dev);
	     port++)
		if (rdma_protocol_roce(ib_dev, port)) {
			struct net_device *idev = NULL;

			if (ib_dev->get_netdev)
				idev = ib_dev->get_netdev(ib_dev, port);

			if (idev && (idev->if_flags & IFF_DYING)) {
				dev_put(idev);
				idev = NULL;
			}

			if (filter(ib_dev, port, idev, filter_cookie))
				cb(ib_dev, port, idev, cookie);

			if (idev)
				dev_put(idev);
		}
}