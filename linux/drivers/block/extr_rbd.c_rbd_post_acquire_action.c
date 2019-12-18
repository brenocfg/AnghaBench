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
struct TYPE_2__ {int features; } ;
struct rbd_device {TYPE_1__ header; } ;

/* Variables and functions */
 int RBD_FEATURE_OBJECT_MAP ; 
 int rbd_object_map_open (struct rbd_device*) ; 

__attribute__((used)) static int rbd_post_acquire_action(struct rbd_device *rbd_dev)
{
	int ret;

	if (rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP) {
		ret = rbd_object_map_open(rbd_dev);
		if (ret)
			return ret;
	}

	return 0;
}