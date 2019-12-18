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
struct roce_rescan_work {int /*<<< orphan*/  work; struct ib_device* ib_dev; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct roce_rescan_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roce_gid_mgmt_wq ; 
 int /*<<< orphan*/  roce_rescan_device_handler ; 

int roce_rescan_device(struct ib_device *ib_dev)
{
	struct roce_rescan_work *work = kmalloc(sizeof(*work), GFP_KERNEL);

	if (!work)
		return -ENOMEM;

	work->ib_dev = ib_dev;
	INIT_WORK(&work->work, roce_rescan_device_handler);
	queue_work(roce_gid_mgmt_wq, &work->work);

	return 0;
}