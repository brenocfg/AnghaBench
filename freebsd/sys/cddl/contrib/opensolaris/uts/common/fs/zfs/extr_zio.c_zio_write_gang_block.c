#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int zp_copies; int /*<<< orphan*/  zp_checksum; } ;
struct TYPE_29__ {int io_txg; int io_size; int io_flags; scalar_t__ io_priority; size_t io_allocator; int io_error; scalar_t__ io_ready; int /*<<< orphan*/  io_pipeline; int /*<<< orphan*/  io_bookmark; int /*<<< orphan*/  io_abd; TYPE_1__ io_prop; TYPE_5__** io_private; TYPE_5__* io_gang_tree; int /*<<< orphan*/  io_alloc_list; int /*<<< orphan*/ * io_bp; struct TYPE_29__* io_gang_leader; int /*<<< orphan*/ * io_spa; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_30__ {int zp_copies; void* zp_nopwrite; void* zp_dedup_verify; void* zp_dedup; scalar_t__ zp_level; int /*<<< orphan*/  zp_type; int /*<<< orphan*/  zp_compress; int /*<<< orphan*/  zp_checksum; } ;
typedef  TYPE_3__ zio_prop_t ;
struct TYPE_31__ {int /*<<< orphan*/ * zg_blkptr; } ;
typedef  TYPE_4__ zio_gbh_phys_t ;
struct TYPE_32__ {int /*<<< orphan*/ * gn_child; TYPE_4__* gn_gbh; } ;
typedef  TYPE_5__ zio_gang_node_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_33__ {int /*<<< orphan*/ * mc_alloc_slots; } ;
typedef  TYPE_6__ metaslab_class_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int METASLAB_ASYNC_ALLOC ; 
 int METASLAB_GANG_HEADER ; 
 int METASLAB_HINTBP_FAVOR ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int P2ROUNDUP (int,int) ; 
 int /*<<< orphan*/  SPA_GANGBLOCKSIZE ; 
 int SPA_GBH_NBLKPTRS ; 
 int SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_COMPRESS_OFF ; 
 int ZIO_FLAG_IO_ALLOCATING ; 
 int ZIO_FLAG_NODATA ; 
 int /*<<< orphan*/  ZIO_GANG_CHILD_FLAGS (TYPE_2__*) ; 
 int /*<<< orphan*/  ZIO_INTERLOCK_PIPELINE ; 
 scalar_t__ ZIO_PRIORITY_ASYNC_WRITE ; 
 int /*<<< orphan*/ * abd_get_from_buf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * abd_get_offset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int metaslab_alloc (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  metaslab_class_throttle_reserve (TYPE_6__*,int,size_t,TYPE_2__*,int) ; 
 int /*<<< orphan*/  metaslab_class_throttle_unreserve (TYPE_6__*,int,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  spa_max_replication (int /*<<< orphan*/ *) ; 
 TYPE_6__* spa_normal_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_refcount_held (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_5__* zio_gang_node_alloc (TYPE_5__**) ; 
 int /*<<< orphan*/  zio_nowait (TYPE_2__*) ; 
 TYPE_2__* zio_rewrite (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* zio_write (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_write_gang_done ; 
 scalar_t__ zio_write_gang_member_ready ; 

__attribute__((used)) static zio_t *
zio_write_gang_block(zio_t *pio)
{
	spa_t *spa = pio->io_spa;
	metaslab_class_t *mc = spa_normal_class(spa);
	blkptr_t *bp = pio->io_bp;
	zio_t *gio = pio->io_gang_leader;
	zio_t *zio;
	zio_gang_node_t *gn, **gnpp;
	zio_gbh_phys_t *gbh;
	abd_t *gbh_abd;
	uint64_t txg = pio->io_txg;
	uint64_t resid = pio->io_size;
	uint64_t lsize;
	int copies = gio->io_prop.zp_copies;
	int gbh_copies = MIN(copies + 1, spa_max_replication(spa));
	zio_prop_t zp;
	int error;
	boolean_t has_data = !(pio->io_flags & ZIO_FLAG_NODATA);

	int flags = METASLAB_HINTBP_FAVOR | METASLAB_GANG_HEADER;
	if (pio->io_flags & ZIO_FLAG_IO_ALLOCATING) {
		ASSERT(pio->io_priority == ZIO_PRIORITY_ASYNC_WRITE);
		ASSERT(has_data);

		flags |= METASLAB_ASYNC_ALLOC;
		VERIFY(zfs_refcount_held(&mc->mc_alloc_slots[pio->io_allocator],
		    pio));

		/*
		 * The logical zio has already placed a reservation for
		 * 'copies' allocation slots but gang blocks may require
		 * additional copies. These additional copies
		 * (i.e. gbh_copies - copies) are guaranteed to succeed
		 * since metaslab_class_throttle_reserve() always allows
		 * additional reservations for gang blocks.
		 */
		VERIFY(metaslab_class_throttle_reserve(mc, gbh_copies - copies,
		    pio->io_allocator, pio, flags));
	}

	error = metaslab_alloc(spa, mc, SPA_GANGBLOCKSIZE,
	    bp, gbh_copies, txg, pio == gio ? NULL : gio->io_bp, flags,
	    &pio->io_alloc_list, pio, pio->io_allocator);
	if (error) {
		if (pio->io_flags & ZIO_FLAG_IO_ALLOCATING) {
			ASSERT(pio->io_priority == ZIO_PRIORITY_ASYNC_WRITE);
			ASSERT(has_data);

			/*
			 * If we failed to allocate the gang block header then
			 * we remove any additional allocation reservations that
			 * we placed here. The original reservation will
			 * be removed when the logical I/O goes to the ready
			 * stage.
			 */
			metaslab_class_throttle_unreserve(mc,
			    gbh_copies - copies, pio->io_allocator, pio);
		}
		pio->io_error = error;
		return (pio);
	}

	if (pio == gio) {
		gnpp = &gio->io_gang_tree;
	} else {
		gnpp = pio->io_private;
		ASSERT(pio->io_ready == zio_write_gang_member_ready);
	}

	gn = zio_gang_node_alloc(gnpp);
	gbh = gn->gn_gbh;
	bzero(gbh, SPA_GANGBLOCKSIZE);
	gbh_abd = abd_get_from_buf(gbh, SPA_GANGBLOCKSIZE);

	/*
	 * Create the gang header.
	 */
	zio = zio_rewrite(pio, spa, txg, bp, gbh_abd, SPA_GANGBLOCKSIZE,
	    zio_write_gang_done, NULL, pio->io_priority,
	    ZIO_GANG_CHILD_FLAGS(pio), &pio->io_bookmark);

	/*
	 * Create and nowait the gang children.
	 */
	for (int g = 0; resid != 0; resid -= lsize, g++) {
		lsize = P2ROUNDUP(resid / (SPA_GBH_NBLKPTRS - g),
		    SPA_MINBLOCKSIZE);
		ASSERT(lsize >= SPA_MINBLOCKSIZE && lsize <= resid);

		zp.zp_checksum = gio->io_prop.zp_checksum;
		zp.zp_compress = ZIO_COMPRESS_OFF;
		zp.zp_type = DMU_OT_NONE;
		zp.zp_level = 0;
		zp.zp_copies = gio->io_prop.zp_copies;
		zp.zp_dedup = B_FALSE;
		zp.zp_dedup_verify = B_FALSE;
		zp.zp_nopwrite = B_FALSE;

		zio_t *cio = zio_write(zio, spa, txg, &gbh->zg_blkptr[g],
		    has_data ? abd_get_offset(pio->io_abd, pio->io_size -
		    resid) : NULL, lsize, lsize, &zp,
		    zio_write_gang_member_ready, NULL, NULL,
		    zio_write_gang_done, &gn->gn_child[g], pio->io_priority,
		    ZIO_GANG_CHILD_FLAGS(pio), &pio->io_bookmark);

		if (pio->io_flags & ZIO_FLAG_IO_ALLOCATING) {
			ASSERT(pio->io_priority == ZIO_PRIORITY_ASYNC_WRITE);
			ASSERT(has_data);

			/*
			 * Gang children won't throttle but we should
			 * account for their work, so reserve an allocation
			 * slot for them here.
			 */
			VERIFY(metaslab_class_throttle_reserve(mc,
			    zp.zp_copies, cio->io_allocator, cio, flags));
		}
		zio_nowait(cio);
	}

	/*
	 * Set pio's pipeline to just wait for zio to finish.
	 */
	pio->io_pipeline = ZIO_INTERLOCK_PIPELINE;

	zio_nowait(zio);

	return (pio);
}