#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sio_cksum; int /*<<< orphan*/  sio_birth; int /*<<< orphan*/  sio_phys_birth; int /*<<< orphan*/  sio_blk_prop; int /*<<< orphan*/  sio_asize; int /*<<< orphan*/  sio_offset; } ;
typedef  TYPE_1__ scan_io_t ;
struct TYPE_6__ {int /*<<< orphan*/  blk_cksum; int /*<<< orphan*/  blk_birth; int /*<<< orphan*/  blk_phys_birth; int /*<<< orphan*/  blk_prop; int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DVA_GET_ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DVA_GET_OFFSET (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
bp2sio(const blkptr_t *bp, scan_io_t *sio, int dva_i)
{
	/* we discard the vdev id, since we can deduce it from the queue */
	sio->sio_offset = DVA_GET_OFFSET(&bp->blk_dva[dva_i]);
	sio->sio_asize = DVA_GET_ASIZE(&bp->blk_dva[dva_i]);
	sio->sio_blk_prop = bp->blk_prop;
	sio->sio_phys_birth = bp->blk_phys_birth;
	sio->sio_birth = bp->blk_birth;
	sio->sio_cksum = bp->blk_cksum;
}