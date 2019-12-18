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
struct swim_priv {int /*<<< orphan*/  lock; } ;
struct request {int /*<<< orphan*/  bio; } ;
struct floppy_state {int /*<<< orphan*/  disk_in; struct swim_priv* swd; } ;
struct blk_mq_queue_data {struct request* rq; } ;
struct blk_mq_hw_ctx {TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {struct floppy_state* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DEV_RESOURCE ; 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  __blk_mq_end_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_cur_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_cur_sectors (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 scalar_t__ blk_update_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floppy_read_sectors (struct floppy_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 int /*<<< orphan*/  spin_trylock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t swim_queue_rq(struct blk_mq_hw_ctx *hctx,
				  const struct blk_mq_queue_data *bd)
{
	struct floppy_state *fs = hctx->queue->queuedata;
	struct swim_priv *swd = fs->swd;
	struct request *req = bd->rq;
	blk_status_t err;

	if (!spin_trylock_irq(&swd->lock))
		return BLK_STS_DEV_RESOURCE;

	blk_mq_start_request(req);

	if (!fs->disk_in || rq_data_dir(req) == WRITE) {
		err = BLK_STS_IOERR;
		goto out;
	}

	do {
		err = floppy_read_sectors(fs, blk_rq_pos(req),
					  blk_rq_cur_sectors(req),
					  bio_data(req->bio));
	} while (blk_update_request(req, err, blk_rq_cur_bytes(req)));
	__blk_mq_end_request(req, err);

	err = BLK_STS_OK;
out:
	spin_unlock_irq(&swd->lock);
	return err;

}