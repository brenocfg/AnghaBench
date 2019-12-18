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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct roce_netdev_event_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roce_gid_delete_all_event_handler ; 
 int /*<<< orphan*/  roce_gid_mgmt_wq ; 

__attribute__((used)) static void
roce_gid_delete_all_event(struct net_device *ndev)
{
	struct roce_netdev_event_work *work;

	work = kmalloc(sizeof(*work), GFP_ATOMIC);
	if (!work) {
		pr_warn("roce_gid_mgmt: Couldn't allocate work for addr_event\n");
		return;
	}

	INIT_WORK(&work->work, roce_gid_delete_all_event_handler);
	dev_hold(ndev);
	work->ndev = ndev;
	queue_work(roce_gid_mgmt_wq, &work->work);

	/* make sure job is complete before returning */
	flush_workqueue(roce_gid_mgmt_wq);
}