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
struct rbd_device {int /*<<< orphan*/  name; int /*<<< orphan*/  major; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBD_DEV_FLAG_EXISTS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_free_disk (struct rbd_device*) ; 
 int /*<<< orphan*/  single_major ; 
 int /*<<< orphan*/  unregister_blkdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbd_dev_device_release(struct rbd_device *rbd_dev)
{
	clear_bit(RBD_DEV_FLAG_EXISTS, &rbd_dev->flags);
	rbd_free_disk(rbd_dev);
	if (!single_major)
		unregister_blkdev(rbd_dev->major, rbd_dev->name);
}