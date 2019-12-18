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
struct rbd_img_request {int op_type; int /*<<< orphan*/  kref; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  object_extents; int /*<<< orphan*/  lock_item; struct ceph_snap_context* snapc; int /*<<< orphan*/  snap_id; struct rbd_device* rbd_dev; } ;
struct rbd_device {TYPE_1__* spec; } ;
struct ceph_snap_context {int dummy; } ;
typedef  enum obj_operation_type { ____Placeholder_obj_operation_type } obj_operation_type ;
struct TYPE_2__ {int /*<<< orphan*/  snap_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  img_request_layered_set (struct rbd_img_request*) ; 
 struct rbd_img_request* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ rbd_dev_parent_get (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_img_is_write (struct rbd_img_request*) ; 
 int /*<<< orphan*/  rbd_img_request_cache ; 

__attribute__((used)) static struct rbd_img_request *rbd_img_request_create(
					struct rbd_device *rbd_dev,
					enum obj_operation_type op_type,
					struct ceph_snap_context *snapc)
{
	struct rbd_img_request *img_request;

	img_request = kmem_cache_zalloc(rbd_img_request_cache, GFP_NOIO);
	if (!img_request)
		return NULL;

	img_request->rbd_dev = rbd_dev;
	img_request->op_type = op_type;
	if (!rbd_img_is_write(img_request))
		img_request->snap_id = rbd_dev->spec->snap_id;
	else
		img_request->snapc = snapc;

	if (rbd_dev_parent_get(rbd_dev))
		img_request_layered_set(img_request);

	INIT_LIST_HEAD(&img_request->lock_item);
	INIT_LIST_HEAD(&img_request->object_extents);
	mutex_init(&img_request->state_mutex);
	kref_init(&img_request->kref);

	return img_request;
}