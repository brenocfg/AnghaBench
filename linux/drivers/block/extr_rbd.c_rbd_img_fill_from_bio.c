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
typedef  int /*<<< orphan*/  u64 ;
struct rbd_img_request {int dummy; } ;
struct ceph_file_extent {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct ceph_bio_iter {int /*<<< orphan*/  iter; struct bio* bio; } ;
struct bio {int /*<<< orphan*/  bi_iter; } ;

/* Variables and functions */
 int __rbd_img_fill_from_bio (struct rbd_img_request*,struct ceph_file_extent*,int,struct ceph_bio_iter*) ; 

__attribute__((used)) static int rbd_img_fill_from_bio(struct rbd_img_request *img_req,
				 u64 off, u64 len, struct bio *bio)
{
	struct ceph_file_extent ex = { off, len };
	struct ceph_bio_iter it = { .bio = bio, .iter = bio->bi_iter };

	return __rbd_img_fill_from_bio(img_req, &ex, 1, &it);
}