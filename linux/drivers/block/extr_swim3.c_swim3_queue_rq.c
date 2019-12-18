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
struct request {int dummy; } ;
struct floppy_state {scalar_t__ state; scalar_t__ write_prot; long req_cyl; long secpercyl; unsigned long head; unsigned long secpertrack; unsigned long req_sector; scalar_t__ retries; scalar_t__ ejected; TYPE_2__* mdev; struct request* cur_req; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_4__ {scalar_t__ media_bay; } ;
struct TYPE_3__ {struct floppy_state* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ MB_FD ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  WRITE_PROT ; 
 int /*<<< orphan*/  act (struct floppy_state*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ check_media_bay (scalar_t__) ; 
 scalar_t__ do_transfer ; 
 scalar_t__ idle ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swim3_dbg (char*,char*) ; 
 int /*<<< orphan*/  swim3_end_request (struct floppy_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swim3_lock ; 
 scalar_t__ swim3_readbit (struct floppy_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t swim3_queue_rq(struct blk_mq_hw_ctx *hctx,
				   const struct blk_mq_queue_data *bd)
{
	struct floppy_state *fs = hctx->queue->queuedata;
	struct request *req = bd->rq;
	unsigned long x;

	spin_lock_irq(&swim3_lock);
	if (fs->cur_req || fs->state != idle) {
		spin_unlock_irq(&swim3_lock);
		return BLK_STS_DEV_RESOURCE;
	}
	blk_mq_start_request(req);
	fs->cur_req = req;
	if (fs->mdev->media_bay &&
	    check_media_bay(fs->mdev->media_bay) != MB_FD) {
		swim3_dbg("%s", "  media bay absent, dropping req\n");
		swim3_end_request(fs, BLK_STS_IOERR, 0);
		goto out;
	}
	if (fs->ejected) {
		swim3_dbg("%s", "  disk ejected\n");
		swim3_end_request(fs, BLK_STS_IOERR, 0);
		goto out;
	}
	if (rq_data_dir(req) == WRITE) {
		if (fs->write_prot < 0)
			fs->write_prot = swim3_readbit(fs, WRITE_PROT);
		if (fs->write_prot) {
			swim3_dbg("%s", "  try to write, disk write protected\n");
			swim3_end_request(fs, BLK_STS_IOERR, 0);
			goto out;
		}
	}

	/*
	 * Do not remove the cast. blk_rq_pos(req) is now a sector_t and can be
	 * 64 bits, but it will never go past 32 bits for this driver anyway, so
	 * we can safely cast it down and not have to do a 64/32 division
	 */
	fs->req_cyl = ((long)blk_rq_pos(req)) / fs->secpercyl;
	x = ((long)blk_rq_pos(req)) % fs->secpercyl;
	fs->head = x / fs->secpertrack;
	fs->req_sector = x % fs->secpertrack + 1;
	fs->state = do_transfer;
	fs->retries = 0;

	act(fs);

out:
	spin_unlock_irq(&swim3_lock);
	return BLK_STS_OK;
}