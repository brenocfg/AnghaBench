#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct blkfront_info {unsigned int nr_rings; int /*<<< orphan*/ * rinfo; scalar_t__ rq; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKIF_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  BLKIF_STATE_SUSPENDED ; 
 int /*<<< orphan*/  blk_mq_stop_hw_queues (scalar_t__) ; 
 int /*<<< orphan*/  blkif_free_ring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blkif_free(struct blkfront_info *info, int suspend)
{
	unsigned int i;

	/* Prevent new requests being issued until we fix things up. */
	info->connected = suspend ?
		BLKIF_STATE_SUSPENDED : BLKIF_STATE_DISCONNECTED;
	/* No more blkif_request(). */
	if (info->rq)
		blk_mq_stop_hw_queues(info->rq);

	for (i = 0; i < info->nr_rings; i++)
		blkif_free_ring(&info->rinfo[i]);

	kvfree(info->rinfo);
	info->rinfo = NULL;
	info->nr_rings = 0;
}