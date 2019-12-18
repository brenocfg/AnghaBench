#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  v_psize; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_13__ {int /*<<< orphan*/  blk_cksum; } ;
typedef  TYPE_2__ blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_IDENTITY (TYPE_2__*) ; 
 int /*<<< orphan*/  BP_SET_CHECKSUM (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_COMPRESS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LSIZE (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  BP_SET_PSIZE (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  BP_ZERO (TYPE_2__*) ; 
 int /*<<< orphan*/  DVA_SET_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_LABEL ; 
 int /*<<< orphan*/  ZIO_COMPRESS_OFF ; 
 int /*<<< orphan*/  ZIO_SET_CHECKSUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_offset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int vdev_read_phys (TYPE_1__*,TYPE_2__*,void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
vdev_label_read(vdev_t *vd, int l, void *buf, uint64_t offset,
    size_t size)
{
	blkptr_t bp;
	off_t off;

	off = vdev_label_offset(vd->v_psize, l, offset);

	BP_ZERO(&bp);
	BP_SET_LSIZE(&bp, size);
	BP_SET_PSIZE(&bp, size);
	BP_SET_CHECKSUM(&bp, ZIO_CHECKSUM_LABEL);
	BP_SET_COMPRESS(&bp, ZIO_COMPRESS_OFF);
	DVA_SET_OFFSET(BP_IDENTITY(&bp), off);
	ZIO_SET_CHECKSUM(&bp.blk_cksum, off, 0, 0, 0);

	return (vdev_read_phys(vd, &bp, buf, off, size));
}