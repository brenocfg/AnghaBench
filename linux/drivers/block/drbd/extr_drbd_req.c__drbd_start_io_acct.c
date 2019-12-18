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
struct request_queue {int dummy; } ;
struct TYPE_3__ {int size; } ;
struct drbd_request {TYPE_1__ i; int /*<<< orphan*/  master_bio; } ;
struct drbd_device {TYPE_2__* vdisk; struct request_queue* rq_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_start_io_acct (struct request_queue*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _drbd_start_io_acct(struct drbd_device *device, struct drbd_request *req)
{
	struct request_queue *q = device->rq_queue;

	generic_start_io_acct(q, bio_op(req->master_bio),
				req->i.size >> 9, &device->vdisk->part0);
}