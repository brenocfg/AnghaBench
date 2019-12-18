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
struct request_queue {struct pktcdvd_device* queuedata; } ;
struct TYPE_3__ {scalar_t__ size; } ;
struct pktcdvd_device {TYPE_1__ settings; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {scalar_t__ bi_sector; int bi_size; } ;
struct bio {TYPE_2__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  BLK_QC_T_NONE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CD_FRAMESIZE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  PACKET_WRITABLE ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  bio_chain (struct bio*,struct bio*) ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  bio_devname (struct bio*,char*) ; 
 scalar_t__ bio_end_sector (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 struct bio* bio_split (struct bio*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_split (struct request_queue*,struct bio**) ; 
 scalar_t__ get_zone (scalar_t__,struct pktcdvd_device*) ; 
 int /*<<< orphan*/  pkt_bio_set ; 
 int /*<<< orphan*/  pkt_dbg (int,struct pktcdvd_device*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  pkt_err (struct pktcdvd_device*,char*) ; 
 int /*<<< orphan*/  pkt_make_request_read (struct pktcdvd_device*,struct bio*) ; 
 int /*<<< orphan*/  pkt_make_request_write (struct request_queue*,struct bio*) ; 
 int /*<<< orphan*/  pkt_notice (struct pktcdvd_device*,char*,unsigned long long) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_qc_t pkt_make_request(struct request_queue *q, struct bio *bio)
{
	struct pktcdvd_device *pd;
	char b[BDEVNAME_SIZE];
	struct bio *split;

	blk_queue_split(q, &bio);

	pd = q->queuedata;
	if (!pd) {
		pr_err("%s incorrect request queue\n", bio_devname(bio, b));
		goto end_io;
	}

	pkt_dbg(2, pd, "start = %6llx stop = %6llx\n",
		(unsigned long long)bio->bi_iter.bi_sector,
		(unsigned long long)bio_end_sector(bio));

	/*
	 * Clone READ bios so we can have our own bi_end_io callback.
	 */
	if (bio_data_dir(bio) == READ) {
		pkt_make_request_read(pd, bio);
		return BLK_QC_T_NONE;
	}

	if (!test_bit(PACKET_WRITABLE, &pd->flags)) {
		pkt_notice(pd, "WRITE for ro device (%llu)\n",
			   (unsigned long long)bio->bi_iter.bi_sector);
		goto end_io;
	}

	if (!bio->bi_iter.bi_size || (bio->bi_iter.bi_size % CD_FRAMESIZE)) {
		pkt_err(pd, "wrong bio size\n");
		goto end_io;
	}

	do {
		sector_t zone = get_zone(bio->bi_iter.bi_sector, pd);
		sector_t last_zone = get_zone(bio_end_sector(bio) - 1, pd);

		if (last_zone != zone) {
			BUG_ON(last_zone != zone + pd->settings.size);

			split = bio_split(bio, last_zone -
					  bio->bi_iter.bi_sector,
					  GFP_NOIO, &pkt_bio_set);
			bio_chain(split, bio);
		} else {
			split = bio;
		}

		pkt_make_request_write(q, split);
	} while (split != bio);

	return BLK_QC_T_NONE;
end_io:
	bio_io_error(bio);
	return BLK_QC_T_NONE;
}