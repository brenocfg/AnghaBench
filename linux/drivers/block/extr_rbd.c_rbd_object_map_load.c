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
struct rbd_device {int object_map_flags; } ;

/* Variables and functions */
 int RBD_FLAG_OBJECT_MAP_INVALID ; 
 int __rbd_object_map_load (struct rbd_device*) ; 
 int rbd_dev_v2_get_flags (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_object_map_free (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*) ; 

__attribute__((used)) static int rbd_object_map_load(struct rbd_device *rbd_dev)
{
	int ret;

	ret = __rbd_object_map_load(rbd_dev);
	if (ret)
		return ret;

	ret = rbd_dev_v2_get_flags(rbd_dev);
	if (ret) {
		rbd_object_map_free(rbd_dev);
		return ret;
	}

	if (rbd_dev->object_map_flags & RBD_FLAG_OBJECT_MAP_INVALID)
		rbd_warn(rbd_dev, "object map is invalid");

	return 0;
}