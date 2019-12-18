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
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int local; int waiting; int /*<<< orphan*/  size; int /*<<< orphan*/  sector; } ;
struct drbd_request {int rq_state; int /*<<< orphan*/  kref; int /*<<< orphan*/  completion_ref; int /*<<< orphan*/  req_pending_local; int /*<<< orphan*/  req_pending_master_completion; TYPE_2__ w; int /*<<< orphan*/  tl_requests; TYPE_3__ i; scalar_t__ epoch; struct bio* master_bio; struct drbd_device* device; } ;
struct drbd_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bi_size; int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_WRITE_SAME ; 
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 int RQ_UNMAP ; 
 int RQ_WRITE ; 
 int RQ_WSAME ; 
 int RQ_ZEROES ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  drbd_clear_interval (TYPE_3__*) ; 
 int /*<<< orphan*/  drbd_req_make_private_bio (struct drbd_request*,struct bio*) ; 
 int /*<<< orphan*/  drbd_request_mempool ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct drbd_request* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct drbd_request*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct drbd_request *drbd_req_new(struct drbd_device *device, struct bio *bio_src)
{
	struct drbd_request *req;

	req = mempool_alloc(&drbd_request_mempool, GFP_NOIO);
	if (!req)
		return NULL;
	memset(req, 0, sizeof(*req));

	drbd_req_make_private_bio(req, bio_src);
	req->rq_state = (bio_data_dir(bio_src) == WRITE ? RQ_WRITE : 0)
		      | (bio_op(bio_src) == REQ_OP_WRITE_SAME ? RQ_WSAME : 0)
		      | (bio_op(bio_src) == REQ_OP_WRITE_ZEROES ? RQ_ZEROES : 0)
		      | (bio_op(bio_src) == REQ_OP_DISCARD ? RQ_UNMAP : 0);
	req->device = device;
	req->master_bio = bio_src;
	req->epoch = 0;

	drbd_clear_interval(&req->i);
	req->i.sector     = bio_src->bi_iter.bi_sector;
	req->i.size      = bio_src->bi_iter.bi_size;
	req->i.local = true;
	req->i.waiting = false;

	INIT_LIST_HEAD(&req->tl_requests);
	INIT_LIST_HEAD(&req->w.list);
	INIT_LIST_HEAD(&req->req_pending_master_completion);
	INIT_LIST_HEAD(&req->req_pending_local);

	/* one reference to be put by __drbd_make_request */
	atomic_set(&req->completion_ref, 1);
	/* one kref as long as completion_ref > 0 */
	kref_init(&req->kref);
	return req;
}