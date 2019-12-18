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
struct roce_netdev_event_work {int /*<<< orphan*/  work; struct net_device* ndev; } ;
struct net_device {int if_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  IFT_ETHER 129 
#define  IFT_L2VLAN 128 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct roce_netdev_event_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net_device* rdma_vlan_dev_real_dev (struct net_device*) ; 
 int /*<<< orphan*/  roce_gid_mgmt_wq ; 
 int /*<<< orphan*/  roce_gid_queue_scan_event_handler ; 

__attribute__((used)) static void
roce_gid_queue_scan_event(struct net_device *ndev)
{
	struct roce_netdev_event_work *work;

retry:
	switch (ndev->if_type) {
	case IFT_ETHER:
		break;
	case IFT_L2VLAN:
		ndev = rdma_vlan_dev_real_dev(ndev);
		if (ndev != NULL)
			goto retry;
		/* FALLTHROUGH */
	default:
		return;
	}

	work = kmalloc(sizeof(*work), GFP_ATOMIC);
	if (!work) {
		pr_warn("roce_gid_mgmt: Couldn't allocate work for addr_event\n");
		return;
	}

	INIT_WORK(&work->work, roce_gid_queue_scan_event_handler);
	dev_hold(ndev);

	work->ndev = ndev;

	queue_work(roce_gid_mgmt_wq, &work->work);
}