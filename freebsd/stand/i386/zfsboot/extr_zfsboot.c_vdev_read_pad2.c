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
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_IDENTITY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BP_SET_CHECKSUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_COMPRESS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LSIZE (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  BP_SET_PSIZE (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  BP_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DVA_SET_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 size_t VDEV_PAD_SIZE ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_LABEL ; 
 int /*<<< orphan*/  ZIO_COMPRESS_OFF ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_t ; 
 scalar_t__ vdev_read_phys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vl_pad2 ; 
 char* zap_scratch ; 

__attribute__((used)) static int
vdev_read_pad2(vdev_t *vdev, char *buf, size_t size)
{
	blkptr_t bp;
	char *tmp = zap_scratch;
	off_t off = offsetof(vdev_label_t, vl_pad2);

	if (size > VDEV_PAD_SIZE)
		size = VDEV_PAD_SIZE;

	BP_ZERO(&bp);
	BP_SET_LSIZE(&bp, VDEV_PAD_SIZE);
	BP_SET_PSIZE(&bp, VDEV_PAD_SIZE);
	BP_SET_CHECKSUM(&bp, ZIO_CHECKSUM_LABEL);
	BP_SET_COMPRESS(&bp, ZIO_COMPRESS_OFF);
	DVA_SET_OFFSET(BP_IDENTITY(&bp), off);
	if (vdev_read_phys(vdev, &bp, tmp, off, 0))
		return (EIO);
	memcpy(buf, tmp, size);
	return (0);
}