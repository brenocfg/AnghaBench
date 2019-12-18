#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_2__* s_op; } ;
struct request {TYPE_1__* rq_disk; } ;
struct pktcdvd_device {int /*<<< orphan*/  bdev; int /*<<< orphan*/  pkt_dev; } ;
struct packet_data {int sector; int frames; TYPE_4__* bio; struct request* rq; } ;
struct block_device {int dummy; } ;
typedef  void* sector_t ;
struct TYPE_9__ {int bi_size; void* bi_sector; } ;
struct TYPE_10__ {int bi_vcnt; struct packet_data* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_3__ bi_iter; } ;
struct TYPE_8__ {scalar_t__ (* relocate_blocks ) (struct super_block*,unsigned long,unsigned long*) ;} ;
struct TYPE_7__ {struct pktcdvd_device* private_data; } ;

/* Variables and functions */
 int CD_FRAMESIZE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 struct block_device* bdget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 int /*<<< orphan*/  bio_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  bio_set_dev (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_super (struct super_block*) ; 
 struct super_block* get_super (struct block_device*) ; 
 int /*<<< orphan*/  kdev_t_to_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_end_io_packet_write ; 
 scalar_t__ stub1 (struct super_block*,unsigned long,unsigned long*) ; 

__attribute__((used)) static int pkt_start_recovery(struct packet_data *pkt)
{
	/*
	 * FIXME. We need help from the file system to implement
	 * recovery handling.
	 */
	return 0;
#if 0
	struct request *rq = pkt->rq;
	struct pktcdvd_device *pd = rq->rq_disk->private_data;
	struct block_device *pkt_bdev;
	struct super_block *sb = NULL;
	unsigned long old_block, new_block;
	sector_t new_sector;

	pkt_bdev = bdget(kdev_t_to_nr(pd->pkt_dev));
	if (pkt_bdev) {
		sb = get_super(pkt_bdev);
		bdput(pkt_bdev);
	}

	if (!sb)
		return 0;

	if (!sb->s_op->relocate_blocks)
		goto out;

	old_block = pkt->sector / (CD_FRAMESIZE >> 9);
	if (sb->s_op->relocate_blocks(sb, old_block, &new_block))
		goto out;

	new_sector = new_block * (CD_FRAMESIZE >> 9);
	pkt->sector = new_sector;

	bio_reset(pkt->bio);
	bio_set_dev(pkt->bio, pd->bdev);
	bio_set_op_attrs(pkt->bio, REQ_OP_WRITE, 0);
	pkt->bio->bi_iter.bi_sector = new_sector;
	pkt->bio->bi_iter.bi_size = pkt->frames * CD_FRAMESIZE;
	pkt->bio->bi_vcnt = pkt->frames;

	pkt->bio->bi_end_io = pkt_end_io_packet_write;
	pkt->bio->bi_private = pkt;

	drop_super(sb);
	return 1;

out:
	drop_super(sb);
	return 0;
#endif
}