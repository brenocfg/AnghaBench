#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int features; } ;
struct rbd_device {TYPE_3__* spec; scalar_t__ image_format; TYPE_2__ header_oid; TYPE_1__ header; } ;
struct TYPE_6__ {scalar_t__ snap_id; int /*<<< orphan*/ * image_id; int /*<<< orphan*/  snap_name; int /*<<< orphan*/  image_name; scalar_t__ pool_ns; int /*<<< orphan*/  pool_name; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int ENOENT ; 
 int RBD_FEATURE_LAYERING ; 
 int RBD_FEATURE_OBJECT_MAP ; 
 int /*<<< orphan*/  dout (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 int rbd_dev_header_info (struct rbd_device*) ; 
 int rbd_dev_header_name (struct rbd_device*) ; 
 int rbd_dev_image_id (struct rbd_device*) ; 
 int rbd_dev_mapping_set (struct rbd_device*) ; 
 int rbd_dev_probe_parent (struct rbd_device*,int) ; 
 int /*<<< orphan*/  rbd_dev_unprobe (struct rbd_device*) ; 
 int rbd_dev_v2_parent_info (struct rbd_device*) ; 
 int rbd_object_map_load (struct rbd_device*) ; 
 int rbd_register_watch (struct rbd_device*) ; 
 int rbd_spec_fill_names (struct rbd_device*) ; 
 int rbd_spec_fill_snap_id (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_unregister_watch (struct rbd_device*) ; 

__attribute__((used)) static int rbd_dev_image_probe(struct rbd_device *rbd_dev, int depth)
{
	int ret;

	/*
	 * Get the id from the image id object.  Unless there's an
	 * error, rbd_dev->spec->image_id will be filled in with
	 * a dynamically-allocated string, and rbd_dev->image_format
	 * will be set to either 1 or 2.
	 */
	ret = rbd_dev_image_id(rbd_dev);
	if (ret)
		return ret;

	ret = rbd_dev_header_name(rbd_dev);
	if (ret)
		goto err_out_format;

	if (!depth) {
		ret = rbd_register_watch(rbd_dev);
		if (ret) {
			if (ret == -ENOENT)
				pr_info("image %s/%s%s%s does not exist\n",
					rbd_dev->spec->pool_name,
					rbd_dev->spec->pool_ns ?: "",
					rbd_dev->spec->pool_ns ? "/" : "",
					rbd_dev->spec->image_name);
			goto err_out_format;
		}
	}

	ret = rbd_dev_header_info(rbd_dev);
	if (ret)
		goto err_out_watch;

	/*
	 * If this image is the one being mapped, we have pool name and
	 * id, image name and id, and snap name - need to fill snap id.
	 * Otherwise this is a parent image, identified by pool, image
	 * and snap ids - need to fill in names for those ids.
	 */
	if (!depth)
		ret = rbd_spec_fill_snap_id(rbd_dev);
	else
		ret = rbd_spec_fill_names(rbd_dev);
	if (ret) {
		if (ret == -ENOENT)
			pr_info("snap %s/%s%s%s@%s does not exist\n",
				rbd_dev->spec->pool_name,
				rbd_dev->spec->pool_ns ?: "",
				rbd_dev->spec->pool_ns ? "/" : "",
				rbd_dev->spec->image_name,
				rbd_dev->spec->snap_name);
		goto err_out_probe;
	}

	ret = rbd_dev_mapping_set(rbd_dev);
	if (ret)
		goto err_out_probe;

	if (rbd_dev->spec->snap_id != CEPH_NOSNAP &&
	    (rbd_dev->header.features & RBD_FEATURE_OBJECT_MAP)) {
		ret = rbd_object_map_load(rbd_dev);
		if (ret)
			goto err_out_probe;
	}

	if (rbd_dev->header.features & RBD_FEATURE_LAYERING) {
		ret = rbd_dev_v2_parent_info(rbd_dev);
		if (ret)
			goto err_out_probe;
	}

	ret = rbd_dev_probe_parent(rbd_dev, depth);
	if (ret)
		goto err_out_probe;

	dout("discovered format %u image, header name is %s\n",
		rbd_dev->image_format, rbd_dev->header_oid.name);
	return 0;

err_out_probe:
	rbd_dev_unprobe(rbd_dev);
err_out_watch:
	if (!depth)
		rbd_unregister_watch(rbd_dev);
err_out_format:
	rbd_dev->image_format = 0;
	kfree(rbd_dev->spec->image_id);
	rbd_dev->spec->image_id = NULL;
	return ret;
}