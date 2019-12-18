#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ zp_checksum; scalar_t__ zp_compress; int zp_level; scalar_t__ zp_copies; scalar_t__ zp_dedup_verify; scalar_t__ zp_dedup; int /*<<< orphan*/  zp_type; } ;
struct TYPE_8__ {TYPE_2__ io_prop; int /*<<< orphan*/ * io_physdone; int /*<<< orphan*/ * io_children_ready; int /*<<< orphan*/ * io_ready; } ;
typedef  TYPE_1__ zio_t ;
typedef  TYPE_2__ zio_prop_t ;
typedef  int /*<<< orphan*/  zio_priority_t ;
typedef  int /*<<< orphan*/  zio_done_func_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  enum zio_flag { ____Placeholder_zio_flag } zio_flag ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ DMU_OT_IS_VALID (int /*<<< orphan*/ ) ; 
 scalar_t__ ZIO_CHECKSUM_FUNCTIONS ; 
 scalar_t__ ZIO_CHECKSUM_OFF ; 
 scalar_t__ ZIO_COMPRESS_FUNCTIONS ; 
 scalar_t__ ZIO_COMPRESS_OFF ; 
 int /*<<< orphan*/  ZIO_DDT_CHILD_WRITE_PIPELINE ; 
 int ZIO_FLAG_DDT_CHILD ; 
 int /*<<< orphan*/  ZIO_STAGE_OPEN ; 
 int /*<<< orphan*/  ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  ZIO_WRITE_PIPELINE ; 
 scalar_t__ spa_max_replication (int /*<<< orphan*/ *) ; 
 TYPE_1__* zio_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

zio_t *
zio_write(zio_t *pio, spa_t *spa, uint64_t txg, blkptr_t *bp,
    abd_t *data, uint64_t lsize, uint64_t psize, const zio_prop_t *zp,
    zio_done_func_t *ready, zio_done_func_t *children_ready,
    zio_done_func_t *physdone, zio_done_func_t *done,
    void *private, zio_priority_t priority, enum zio_flag flags,
    const zbookmark_phys_t *zb)
{
	zio_t *zio;

	ASSERT(zp->zp_checksum >= ZIO_CHECKSUM_OFF &&
	    zp->zp_checksum < ZIO_CHECKSUM_FUNCTIONS &&
	    zp->zp_compress >= ZIO_COMPRESS_OFF &&
	    zp->zp_compress < ZIO_COMPRESS_FUNCTIONS &&
	    DMU_OT_IS_VALID(zp->zp_type) &&
	    zp->zp_level < 32 &&
	    zp->zp_copies > 0 &&
	    zp->zp_copies <= spa_max_replication(spa));

	zio = zio_create(pio, spa, txg, bp, data, lsize, psize, done, private,
	    ZIO_TYPE_WRITE, priority, flags, NULL, 0, zb,
	    ZIO_STAGE_OPEN, (flags & ZIO_FLAG_DDT_CHILD) ?
	    ZIO_DDT_CHILD_WRITE_PIPELINE : ZIO_WRITE_PIPELINE);

	zio->io_ready = ready;
	zio->io_children_ready = children_ready;
	zio->io_physdone = physdone;
	zio->io_prop = *zp;

	/*
	 * Data can be NULL if we are going to call zio_write_override() to
	 * provide the already-allocated BP.  But we may need the data to
	 * verify a dedup hit (if requested).  In this case, don't try to
	 * dedup (just take the already-allocated BP verbatim).
	 */
	if (data == NULL && zio->io_prop.zp_dedup_verify) {
		zio->io_prop.zp_dedup = zio->io_prop.zp_dedup_verify = B_FALSE;
	}

	return (zio);
}