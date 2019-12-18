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
struct rbd_device {int dummy; } ;

/* Variables and functions */
 int rbd_object_map_load (struct rbd_device*) ; 
 int rbd_object_map_lock (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_object_map_unlock (struct rbd_device*) ; 

__attribute__((used)) static int rbd_object_map_open(struct rbd_device *rbd_dev)
{
	int ret;

	ret = rbd_object_map_lock(rbd_dev);
	if (ret)
		return ret;

	ret = rbd_object_map_load(rbd_dev);
	if (ret) {
		rbd_object_map_unlock(rbd_dev);
		return ret;
	}

	return 0;
}