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
typedef  union rbd_img_fill_iter {int dummy; } rbd_img_fill_iter ;
typedef  int /*<<< orphan*/  u32 ;
struct rbd_img_request {int dummy; } ;
struct rbd_img_fill_ctx {int /*<<< orphan*/  copy_fn; int /*<<< orphan*/  count_fn; int /*<<< orphan*/  set_pos_fn; union rbd_img_fill_iter* pos; int /*<<< orphan*/  pos_type; } ;
struct ceph_file_extent {int dummy; } ;
struct ceph_bio_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_REQUEST_BIO ; 
 int /*<<< orphan*/  copy_bio_bvecs ; 
 int /*<<< orphan*/  count_bio_bvecs ; 
 int rbd_img_fill_request (struct rbd_img_request*,struct ceph_file_extent*,int /*<<< orphan*/ ,struct rbd_img_fill_ctx*) ; 
 int /*<<< orphan*/  set_bio_pos ; 

__attribute__((used)) static int __rbd_img_fill_from_bio(struct rbd_img_request *img_req,
				   struct ceph_file_extent *img_extents,
				   u32 num_img_extents,
				   struct ceph_bio_iter *bio_pos)
{
	struct rbd_img_fill_ctx fctx = {
		.pos_type = OBJ_REQUEST_BIO,
		.pos = (union rbd_img_fill_iter *)bio_pos,
		.set_pos_fn = set_bio_pos,
		.count_fn = count_bio_bvecs,
		.copy_fn = copy_bio_bvecs,
	};

	return rbd_img_fill_request(img_req, img_extents, num_img_extents,
				    &fctx);
}