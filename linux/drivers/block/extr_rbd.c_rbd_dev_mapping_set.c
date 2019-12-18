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
typedef  void* u64 ;
struct TYPE_4__ {void* features; void* size; } ;
struct rbd_device {TYPE_2__ mapping; TYPE_1__* spec; } ;
struct TYPE_3__ {void* snap_id; } ;

/* Variables and functions */
 int rbd_snap_features (struct rbd_device*,void*,void**) ; 
 int rbd_snap_size (struct rbd_device*,void*,void**) ; 

__attribute__((used)) static int rbd_dev_mapping_set(struct rbd_device *rbd_dev)
{
	u64 snap_id = rbd_dev->spec->snap_id;
	u64 size = 0;
	u64 features = 0;
	int ret;

	ret = rbd_snap_size(rbd_dev, snap_id, &size);
	if (ret)
		return ret;
	ret = rbd_snap_features(rbd_dev, snap_id, &features);
	if (ret)
		return ret;

	rbd_dev->mapping.size = size;
	rbd_dev->mapping.features = features;

	return 0;
}