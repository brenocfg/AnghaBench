#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pktcdvd_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; } ;
struct page {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  head; } ;
struct packet_data {int frames; int write_size; int cache_valid; TYPE_3__* w_bio; int /*<<< orphan*/  io_wait; scalar_t__ sector; int /*<<< orphan*/  lock; TYPE_2__ orig_bios; struct page** pages; } ;
struct TYPE_9__ {scalar_t__ bi_sector; } ;
struct TYPE_11__ {int /*<<< orphan*/  bi_vcnt; struct packet_data* bi_private; int /*<<< orphan*/  bi_end_io; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int CD_FRAMESIZE ; 
 int /*<<< orphan*/  PACKET_MERGE_SEGS ; 
 int /*<<< orphan*/  PACKET_WRITE_WAIT_STATE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_add_page (TYPE_3__*,struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  bio_list_copy_data (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  bio_set_dev (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*,int,...) ; 
 int /*<<< orphan*/  pkt_end_io_packet_write ; 
 int /*<<< orphan*/  pkt_queue_bio (struct pktcdvd_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  pkt_set_state (struct packet_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_start_write(struct pktcdvd_device *pd, struct packet_data *pkt)
{
	int f;

	bio_reset(pkt->w_bio);
	pkt->w_bio->bi_iter.bi_sector = pkt->sector;
	bio_set_dev(pkt->w_bio, pd->bdev);
	pkt->w_bio->bi_end_io = pkt_end_io_packet_write;
	pkt->w_bio->bi_private = pkt;

	/* XXX: locking? */
	for (f = 0; f < pkt->frames; f++) {
		struct page *page = pkt->pages[(f * CD_FRAMESIZE) / PAGE_SIZE];
		unsigned offset = (f * CD_FRAMESIZE) % PAGE_SIZE;

		if (!bio_add_page(pkt->w_bio, page, CD_FRAMESIZE, offset))
			BUG();
	}
	pkt_dbg(2, pd, "vcnt=%d\n", pkt->w_bio->bi_vcnt);

	/*
	 * Fill-in bvec with data from orig_bios.
	 */
	spin_lock(&pkt->lock);
	bio_list_copy_data(pkt->w_bio, pkt->orig_bios.head);

	pkt_set_state(pkt, PACKET_WRITE_WAIT_STATE);
	spin_unlock(&pkt->lock);

	pkt_dbg(2, pd, "Writing %d frames for zone %llx\n",
		pkt->write_size, (unsigned long long)pkt->sector);

	if (test_bit(PACKET_MERGE_SEGS, &pd->flags) || (pkt->write_size < pkt->frames))
		pkt->cache_valid = 1;
	else
		pkt->cache_valid = 0;

	/* Start the write request */
	atomic_set(&pkt->io_wait, 1);
	bio_set_op_attrs(pkt->w_bio, REQ_OP_WRITE, 0);
	pkt_queue_bio(pd, pkt->w_bio);
}