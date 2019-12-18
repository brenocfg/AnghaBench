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
struct request {int dummy; } ;
struct buf {struct request* rq; } ;
struct TYPE_2__ {struct buf* buf; } ;
struct aoedev {int /*<<< orphan*/  bufpool; TYPE_1__ ip; } ;
struct aoe_req {scalar_t__ nr_bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  aoe_end_request (struct aoedev*,struct request*,int /*<<< orphan*/ ) ; 
 struct aoe_req* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  mempool_free (struct buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aoe_end_buf(struct aoedev *d, struct buf *buf)
{
	struct request *rq = buf->rq;
	struct aoe_req *req = blk_mq_rq_to_pdu(rq);

	if (buf == d->ip.buf)
		d->ip.buf = NULL;
	mempool_free(buf, d->bufpool);
	if (--req->nr_bios == 0)
		aoe_end_request(d, rq, 0);
}