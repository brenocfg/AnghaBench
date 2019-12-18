#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zp_checksum; } ;
struct TYPE_9__ {scalar_t__ io_error; int /*<<< orphan*/ * io_spa; int /*<<< orphan*/ * io_abd; int /*<<< orphan*/  io_offset; int /*<<< orphan*/  io_size; TYPE_1__ io_prop; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_10__ {int zbc_injected; } ;
typedef  TYPE_3__ zio_bad_cksum_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_GET_CHECKSUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BP_GET_PSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_IS_GANG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECKSUM ; 
 int /*<<< orphan*/  SPA_GANGBLOCKSIZE ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_GANG_HEADER ; 
 int zio_checksum_error_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int zio_handle_fault_injection (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ zio_injection_enabled ; 

int
zio_checksum_error(zio_t *zio, zio_bad_cksum_t *info)
{
	blkptr_t *bp = zio->io_bp;
	uint_t checksum = (bp == NULL ? zio->io_prop.zp_checksum :
	    (BP_IS_GANG(bp) ? ZIO_CHECKSUM_GANG_HEADER : BP_GET_CHECKSUM(bp)));
	int error;
	uint64_t size = (bp == NULL ? zio->io_size :
	    (BP_IS_GANG(bp) ? SPA_GANGBLOCKSIZE : BP_GET_PSIZE(bp)));
	uint64_t offset = zio->io_offset;
	abd_t *data = zio->io_abd;
	spa_t *spa = zio->io_spa;

	error = zio_checksum_error_impl(spa, bp, checksum, data, size,
	    offset, info);

	if (zio_injection_enabled && error == 0 && zio->io_error == 0) {
		error = zio_handle_fault_injection(zio, ECKSUM);
		if (error != 0)
			info->zbc_injected = 1;
	}

	return (error);
}