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
struct drbd_request {struct bio* private_bio; struct drbd_device* device; } ;
struct drbd_device {TYPE_1__* ldev; } ;
struct bio {int bi_opf; } ;
struct TYPE_2__ {int /*<<< orphan*/  backing_bdev; } ;

/* Variables and functions */
 unsigned int DRBD_FAULT_DT_RA ; 
 unsigned int DRBD_FAULT_DT_RD ; 
 unsigned int DRBD_FAULT_DT_WR ; 
 int EE_TRIM ; 
 int EE_ZEROOUT ; 
 int REQ_NOUNMAP ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_READ ; 
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ drbd_insert_fault (struct drbd_device*,unsigned int) ; 
 int /*<<< orphan*/  drbd_process_discard_or_zeroes_req (struct drbd_request*,int) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 
 scalar_t__ get_ldev (struct drbd_device*) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 

__attribute__((used)) static void
drbd_submit_req_private_bio(struct drbd_request *req)
{
	struct drbd_device *device = req->device;
	struct bio *bio = req->private_bio;
	unsigned int type;

	if (bio_op(bio) != REQ_OP_READ)
		type = DRBD_FAULT_DT_WR;
	else if (bio->bi_opf & REQ_RAHEAD)
		type = DRBD_FAULT_DT_RA;
	else
		type = DRBD_FAULT_DT_RD;

	bio_set_dev(bio, device->ldev->backing_bdev);

	/* State may have changed since we grabbed our reference on the
	 * ->ldev member. Double check, and short-circuit to endio.
	 * In case the last activity log transaction failed to get on
	 * stable storage, and this is a WRITE, we may not even submit
	 * this bio. */
	if (get_ldev(device)) {
		if (drbd_insert_fault(device, type))
			bio_io_error(bio);
		else if (bio_op(bio) == REQ_OP_WRITE_ZEROES)
			drbd_process_discard_or_zeroes_req(req, EE_ZEROOUT |
			    ((bio->bi_opf & REQ_NOUNMAP) ? 0 : EE_TRIM));
		else if (bio_op(bio) == REQ_OP_DISCARD)
			drbd_process_discard_or_zeroes_req(req, EE_TRIM);
		else
			generic_make_request(bio);
		put_ldev(device);
	} else
		bio_io_error(bio);
}