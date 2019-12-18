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
struct rbd_device {int /*<<< orphan*/  lock_rwsem; } ;

/* Variables and functions */
 scalar_t__ __rbd_is_lock_owner (struct rbd_device*) ; 
 int /*<<< orphan*/  __rbd_release_lock (struct rbd_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_dev_image_unlock(struct rbd_device *rbd_dev)
{
	down_write(&rbd_dev->lock_rwsem);
	if (__rbd_is_lock_owner(rbd_dev))
		__rbd_release_lock(rbd_dev);
	up_write(&rbd_dev->lock_rwsem);
}