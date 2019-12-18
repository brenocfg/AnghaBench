#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct ib_uverbs_device {scalar_t__ devnum; int /*<<< orphan*/  kobj; int /*<<< orphan*/  comp; int /*<<< orphan*/  refcount; int /*<<< orphan*/  ib_dev; TYPE_2__ cdev; TYPE_1__* dev; } ;
struct ib_device {scalar_t__ disassociate_ucontext; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ IB_UVERBS_MAX_DEVICES ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_map ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_group ; 
 int /*<<< orphan*/  ib_uverbs_comp_dev (struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  ib_uverbs_free_hw_resources (struct ib_uverbs_device*,struct ib_device*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  overflow_map ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_class ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_uverbs_remove_one(struct ib_device *device, void *client_data)
{
	struct ib_uverbs_device *uverbs_dev = client_data;
	int wait_clients = 1;

	if (!uverbs_dev)
		return;

	sysfs_remove_group(&uverbs_dev->dev->kobj, &device_group);
	dev_set_drvdata(uverbs_dev->dev, NULL);
	device_destroy(uverbs_class, uverbs_dev->cdev.dev);
	cdev_del(&uverbs_dev->cdev);

	if (uverbs_dev->devnum < IB_UVERBS_MAX_DEVICES)
		clear_bit(uverbs_dev->devnum, dev_map);
	else
		clear_bit(uverbs_dev->devnum - IB_UVERBS_MAX_DEVICES, overflow_map);

	if (device->disassociate_ucontext) {
		/* We disassociate HW resources and immediately return.
		 * Userspace will see a EIO errno for all future access.
		 * Upon returning, ib_device may be freed internally and is not
		 * valid any more.
		 * uverbs_device is still available until all clients close
		 * their files, then the uverbs device ref count will be zero
		 * and its resources will be freed.
		 * Note: At this point no more files can be opened since the
		 * cdev was deleted, however active clients can still issue
		 * commands and close their open files.
		 */
		rcu_assign_pointer(uverbs_dev->ib_dev, NULL);
		ib_uverbs_free_hw_resources(uverbs_dev, device);
		wait_clients = 0;
	}

	if (atomic_dec_and_test(&uverbs_dev->refcount))
		ib_uverbs_comp_dev(uverbs_dev);
	if (wait_clients)
		wait_for_completion(&uverbs_dev->comp);
	kobject_put(&uverbs_dev->kobj);
}