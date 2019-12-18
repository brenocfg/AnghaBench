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
struct TYPE_2__ {int features; int /*<<< orphan*/ * object_prefix; } ;
struct rbd_device {TYPE_1__ header; } ;

/* Variables and functions */
 int RBD_FEATURE_DATA_POOL ; 
 int RBD_FEATURE_STRIPINGV2 ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int rbd_dev_v2_data_pool (struct rbd_device*) ; 
 int rbd_dev_v2_features (struct rbd_device*) ; 
 int rbd_dev_v2_object_prefix (struct rbd_device*) ; 
 int rbd_dev_v2_striping_info (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_init_layout (struct rbd_device*) ; 

__attribute__((used)) static int rbd_dev_v2_header_onetime(struct rbd_device *rbd_dev)
{
	int ret;

	ret = rbd_dev_v2_object_prefix(rbd_dev);
	if (ret)
		goto out_err;

	/*
	 * Get the and check features for the image.  Currently the
	 * features are assumed to never change.
	 */
	ret = rbd_dev_v2_features(rbd_dev);
	if (ret)
		goto out_err;

	/* If the image supports fancy striping, get its parameters */

	if (rbd_dev->header.features & RBD_FEATURE_STRIPINGV2) {
		ret = rbd_dev_v2_striping_info(rbd_dev);
		if (ret < 0)
			goto out_err;
	}

	if (rbd_dev->header.features & RBD_FEATURE_DATA_POOL) {
		ret = rbd_dev_v2_data_pool(rbd_dev);
		if (ret)
			goto out_err;
	}

	rbd_init_layout(rbd_dev);
	return 0;

out_err:
	rbd_dev->header.features = 0;
	kfree(rbd_dev->header.object_prefix);
	rbd_dev->header.object_prefix = NULL;
	return ret;
}