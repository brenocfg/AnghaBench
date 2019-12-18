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
struct simdisk {int /*<<< orphan*/  lock; int /*<<< orphan*/  users; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct simdisk* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int simdisk_open(struct block_device *bdev, fmode_t mode)
{
	struct simdisk *dev = bdev->bd_disk->private_data;

	spin_lock(&dev->lock);
	if (!dev->users)
		check_disk_change(bdev);
	++dev->users;
	spin_unlock(&dev->lock);
	return 0;
}