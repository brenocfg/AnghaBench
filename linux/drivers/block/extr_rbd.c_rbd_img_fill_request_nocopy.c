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
typedef  size_t u32 ;
struct rbd_img_request {int /*<<< orphan*/  object_extents; TYPE_1__* rbd_dev; int /*<<< orphan*/  data_type; } ;
struct rbd_img_fill_ctx {int /*<<< orphan*/  iter; int /*<<< orphan*/  set_pos_fn; int /*<<< orphan*/ * pos; int /*<<< orphan*/  pos_type; } ;
struct ceph_file_extent {int /*<<< orphan*/  fe_len; int /*<<< orphan*/  fe_off; } ;
struct TYPE_2__ {int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 int __rbd_img_fill_request (struct rbd_img_request*) ; 
 int /*<<< orphan*/  alloc_object_extent ; 
 int ceph_file_to_extents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rbd_img_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rbd_img_fill_request_nocopy(struct rbd_img_request *img_req,
				       struct ceph_file_extent *img_extents,
				       u32 num_img_extents,
				       struct rbd_img_fill_ctx *fctx)
{
	u32 i;
	int ret;

	img_req->data_type = fctx->pos_type;

	/*
	 * Create object requests and set each object request's starting
	 * position in the provided bio (list) or bio_vec array.
	 */
	fctx->iter = *fctx->pos;
	for (i = 0; i < num_img_extents; i++) {
		ret = ceph_file_to_extents(&img_req->rbd_dev->layout,
					   img_extents[i].fe_off,
					   img_extents[i].fe_len,
					   &img_req->object_extents,
					   alloc_object_extent, img_req,
					   fctx->set_pos_fn, &fctx->iter);
		if (ret)
			return ret;
	}

	return __rbd_img_fill_request(img_req);
}