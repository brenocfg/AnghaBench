#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ zp_checksum; } ;
struct TYPE_8__ {int io_error; int io_flags; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_offset; int /*<<< orphan*/ * io_vd; int /*<<< orphan*/  io_spa; TYPE_1__ io_prop; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_2__ zio_t ;
typedef  int /*<<< orphan*/  zio_bad_cksum_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ECKSUM ; 
 scalar_t__ ZIO_CHECKSUM_LABEL ; 
 scalar_t__ ZIO_CHECKSUM_OFF ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  zfs_ereport_start_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zio_checksum_error (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zio_t *
zio_checksum_verify(zio_t *zio)
{
	zio_bad_cksum_t info;
	blkptr_t *bp = zio->io_bp;
	int error;

	ASSERT(zio->io_vd != NULL);

	if (bp == NULL) {
		/*
		 * This is zio_read_phys().
		 * We're either verifying a label checksum, or nothing at all.
		 */
		if (zio->io_prop.zp_checksum == ZIO_CHECKSUM_OFF)
			return (zio);

		ASSERT(zio->io_prop.zp_checksum == ZIO_CHECKSUM_LABEL);
	}

	if ((error = zio_checksum_error(zio, &info)) != 0) {
		zio->io_error = error;
		if (error == ECKSUM &&
		    !(zio->io_flags & ZIO_FLAG_SPECULATIVE)) {
			zfs_ereport_start_checksum(zio->io_spa,
			    zio->io_vd, zio, zio->io_offset,
			    zio->io_size, NULL, &info);
		}
	}

	return (zio);
}