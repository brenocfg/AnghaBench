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
union blkif_back_rings {int /*<<< orphan*/  common; } ;
struct xen_blkif_ring {union blkif_back_rings blk_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_REQUESTS (int /*<<< orphan*/ *,int) ; 
 int __do_block_io_op (struct xen_blkif_ring*) ; 

__attribute__((used)) static int
do_block_io_op(struct xen_blkif_ring *ring)
{
	union blkif_back_rings *blk_rings = &ring->blk_rings;
	int more_to_do;

	do {
		more_to_do = __do_block_io_op(ring);
		if (more_to_do)
			break;

		RING_FINAL_CHECK_FOR_REQUESTS(&blk_rings->common, more_to_do);
	} while (more_to_do);

	return more_to_do;
}