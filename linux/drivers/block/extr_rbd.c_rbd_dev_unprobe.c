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
struct rbd_image_header {int /*<<< orphan*/  object_prefix; int /*<<< orphan*/  snap_names; int /*<<< orphan*/  snap_sizes; int /*<<< orphan*/  snapc; } ;
struct rbd_device {struct rbd_image_header header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_put_snap_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rbd_image_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rbd_dev_mapping_clear (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_dev_parent_put (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_object_map_free (struct rbd_device*) ; 

__attribute__((used)) static void rbd_dev_unprobe(struct rbd_device *rbd_dev)
{
	struct rbd_image_header	*header;

	rbd_dev_parent_put(rbd_dev);
	rbd_object_map_free(rbd_dev);
	rbd_dev_mapping_clear(rbd_dev);

	/* Free dynamic fields from the header, then zero it out */

	header = &rbd_dev->header;
	ceph_put_snap_context(header->snapc);
	kfree(header->snap_sizes);
	kfree(header->snap_names);
	kfree(header->object_prefix);
	memset(header, 0, sizeof (*header));
}