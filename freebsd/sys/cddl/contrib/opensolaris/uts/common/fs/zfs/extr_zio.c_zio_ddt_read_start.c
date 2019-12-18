#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ io_size; scalar_t__ io_child_type; int /*<<< orphan*/  io_bookmark; int /*<<< orphan*/  io_priority; int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_spa; TYPE_4__* io_vsd; scalar_t__* io_child_error; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_17__ {int /*<<< orphan*/  ddt_checksum; } ;
typedef  TYPE_2__ ddt_t ;
struct TYPE_18__ {scalar_t__ ddp_phys_birth; } ;
typedef  TYPE_3__ ddt_phys_t ;
struct TYPE_19__ {int /*<<< orphan*/  dde_key; TYPE_3__* dde_phys; } ;
typedef  TYPE_4__ ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_GET_DEDUP (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int DDT_PHYS_TYPES ; 
 size_t ZIO_CHILD_DDT ; 
 scalar_t__ ZIO_CHILD_LOGICAL ; 
 int ZIO_DDT_CHILD_FLAGS (TYPE_1__*) ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int /*<<< orphan*/  abd_alloc_for_io (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddt_bp_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ddt_phys_select (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ddt_repair_start (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ddt_select (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zio_ddt_child_read_done ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zio_t *
zio_ddt_read_start(zio_t *zio)
{
	blkptr_t *bp = zio->io_bp;

	ASSERT(BP_GET_DEDUP(bp));
	ASSERT(BP_GET_PSIZE(bp) == zio->io_size);
	ASSERT(zio->io_child_type == ZIO_CHILD_LOGICAL);

	if (zio->io_child_error[ZIO_CHILD_DDT]) {
		ddt_t *ddt = ddt_select(zio->io_spa, bp);
		ddt_entry_t *dde = ddt_repair_start(ddt, bp);
		ddt_phys_t *ddp = dde->dde_phys;
		ddt_phys_t *ddp_self = ddt_phys_select(dde, bp);
		blkptr_t blk;

		ASSERT(zio->io_vsd == NULL);
		zio->io_vsd = dde;

		if (ddp_self == NULL)
			return (zio);

		for (int p = 0; p < DDT_PHYS_TYPES; p++, ddp++) {
			if (ddp->ddp_phys_birth == 0 || ddp == ddp_self)
				continue;
			ddt_bp_create(ddt->ddt_checksum, &dde->dde_key, ddp,
			    &blk);
			zio_nowait(zio_read(zio, zio->io_spa, &blk,
			    abd_alloc_for_io(zio->io_size, B_TRUE),
			    zio->io_size, zio_ddt_child_read_done, dde,
			    zio->io_priority, ZIO_DDT_CHILD_FLAGS(zio) |
			    ZIO_FLAG_DONT_PROPAGATE, &zio->io_bookmark));
		}
		return (zio);
	}

	zio_nowait(zio_read(zio, zio->io_spa, bp,
	    zio->io_abd, zio->io_size, NULL, NULL, zio->io_priority,
	    ZIO_DDT_CHILD_FLAGS(zio), &zio->io_bookmark));

	return (zio);
}