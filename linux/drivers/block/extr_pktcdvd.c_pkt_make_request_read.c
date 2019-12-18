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
struct TYPE_2__ {int /*<<< orphan*/  secs_r; } ;
struct pktcdvd_device {TYPE_1__ stats; int /*<<< orphan*/  bdev; } ;
struct packet_stacked_data {struct bio* bio; struct pktcdvd_device* pd; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct packet_stacked_data* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 struct bio* bio_clone_fast (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 struct packet_stacked_data* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_bio_set ; 
 int /*<<< orphan*/  pkt_end_io_read_cloned ; 
 int /*<<< orphan*/  pkt_queue_bio (struct pktcdvd_device*,struct bio*) ; 
 int /*<<< orphan*/  psd_pool ; 

__attribute__((used)) static void pkt_make_request_read(struct pktcdvd_device *pd, struct bio *bio)
{
	struct bio *cloned_bio = bio_clone_fast(bio, GFP_NOIO, &pkt_bio_set);
	struct packet_stacked_data *psd = mempool_alloc(&psd_pool, GFP_NOIO);

	psd->pd = pd;
	psd->bio = bio;
	bio_set_dev(cloned_bio, pd->bdev);
	cloned_bio->bi_private = psd;
	cloned_bio->bi_end_io = pkt_end_io_read_cloned;
	pd->stats.secs_r += bio_sectors(bio);
	pkt_queue_bio(pd, cloned_bio);
}