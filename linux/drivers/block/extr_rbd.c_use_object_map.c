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
struct rbd_device {int object_map_flags; TYPE_1__ header; } ;

/* Variables and functions */
 int RBD_FEATURE_OBJECT_MAP ; 
 int RBD_FLAG_OBJECT_MAP_INVALID ; 

__attribute__((used)) static bool use_object_map(struct rbd_device *rbd_dev)
{
	return ((rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP) &&
		!(rbd_dev->object_map_flags & RBD_FLAG_OBJECT_MAP_INVALID));
}