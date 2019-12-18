#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vtblk_softc {int vtblk_flags; int vtblk_max_nsegs; int /*<<< orphan*/  vtblk_write_cache; struct disk* vtblk_disk; int /*<<< orphan*/  vtblk_dev; } ;
struct TYPE_4__ {int physical_block_exp; int alignment_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  heads; int /*<<< orphan*/  sectors; } ;
struct virtio_blk_config {int capacity; int blk_size; TYPE_2__ topology; TYPE_1__ geometry; } ;
struct disk {int d_flags; int d_mediasize; int d_sectorsize; int d_maxsize; int d_stripesize; int d_stripeoffset; int /*<<< orphan*/  d_fwheads; int /*<<< orphan*/  d_fwsectors; int /*<<< orphan*/  d_dump; int /*<<< orphan*/  d_hba_subdevice; int /*<<< orphan*/  d_hba_subvendor; int /*<<< orphan*/  d_hba_device; int /*<<< orphan*/  d_hba_vendor; struct vtblk_softc* d_drv1; int /*<<< orphan*/  d_unit; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_strategy; int /*<<< orphan*/  d_ioctl; int /*<<< orphan*/  d_close; int /*<<< orphan*/  d_open; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DISKFLAG_CANFLUSHCACHE ; 
 int DISKFLAG_DIRECT_COMPLETION ; 
 int DISKFLAG_UNMAPPED_BIO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VIRTIO_BLK_F_BLK_SIZE ; 
 int /*<<< orphan*/  VIRTIO_BLK_F_GEOMETRY ; 
 int /*<<< orphan*/  VIRTIO_BLK_F_TOPOLOGY ; 
 int /*<<< orphan*/  VTBLK_CACHE_WRITEBACK ; 
 int /*<<< orphan*/  VTBLK_CACHE_WRITETHROUGH ; 
 int /*<<< orphan*/  VTBLK_DISK_NAME ; 
 int VTBLK_FLAG_READONLY ; 
 int VTBLK_MIN_SEGMENTS ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 struct disk* disk_alloc () ; 
 int /*<<< orphan*/  virtio_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ virtio_with_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_close ; 
 int /*<<< orphan*/  vtblk_dump ; 
 int /*<<< orphan*/  vtblk_ioctl ; 
 int /*<<< orphan*/  vtblk_open ; 
 int /*<<< orphan*/  vtblk_strategy ; 
 scalar_t__ vtblk_write_cache_enabled (struct vtblk_softc*,struct virtio_blk_config*) ; 

__attribute__((used)) static void
vtblk_alloc_disk(struct vtblk_softc *sc, struct virtio_blk_config *blkcfg)
{
	device_t dev;
	struct disk *dp;

	dev = sc->vtblk_dev;

	sc->vtblk_disk = dp = disk_alloc();
	dp->d_open = vtblk_open;
	dp->d_close = vtblk_close;
	dp->d_ioctl = vtblk_ioctl;
	dp->d_strategy = vtblk_strategy;
	dp->d_name = VTBLK_DISK_NAME;
	dp->d_unit = device_get_unit(dev);
	dp->d_drv1 = sc;
	dp->d_flags = DISKFLAG_CANFLUSHCACHE | DISKFLAG_UNMAPPED_BIO |
	    DISKFLAG_DIRECT_COMPLETION;
	dp->d_hba_vendor = virtio_get_vendor(dev);
	dp->d_hba_device = virtio_get_device(dev);
	dp->d_hba_subvendor = virtio_get_subvendor(dev);
	dp->d_hba_subdevice = virtio_get_subdevice(dev);

	if ((sc->vtblk_flags & VTBLK_FLAG_READONLY) == 0)
		dp->d_dump = vtblk_dump;

	/* Capacity is always in 512-byte units. */
	dp->d_mediasize = blkcfg->capacity * 512;

	if (virtio_with_feature(dev, VIRTIO_BLK_F_BLK_SIZE))
		dp->d_sectorsize = blkcfg->blk_size;
	else
		dp->d_sectorsize = 512;

	/*
	 * The VirtIO maximum I/O size is given in terms of segments.
	 * However, FreeBSD limits I/O size by logical buffer size, not
	 * by physically contiguous pages. Therefore, we have to assume
	 * no pages are contiguous. This may impose an artificially low
	 * maximum I/O size. But in practice, since QEMU advertises 128
	 * segments, this gives us a maximum IO size of 125 * PAGE_SIZE,
	 * which is typically greater than MAXPHYS. Eventually we should
	 * just advertise MAXPHYS and split buffers that are too big.
	 *
	 * Note we must subtract one additional segment in case of non
	 * page aligned buffers.
	 */
	dp->d_maxsize = (sc->vtblk_max_nsegs - VTBLK_MIN_SEGMENTS - 1) *
	    PAGE_SIZE;
	if (dp->d_maxsize < PAGE_SIZE)
		dp->d_maxsize = PAGE_SIZE; /* XXX */

	if (virtio_with_feature(dev, VIRTIO_BLK_F_GEOMETRY)) {
		dp->d_fwsectors = blkcfg->geometry.sectors;
		dp->d_fwheads = blkcfg->geometry.heads;
	}

	if (virtio_with_feature(dev, VIRTIO_BLK_F_TOPOLOGY) &&
	    blkcfg->topology.physical_block_exp > 0) {
		dp->d_stripesize = dp->d_sectorsize *
		    (1 << blkcfg->topology.physical_block_exp);
		dp->d_stripeoffset = (dp->d_stripesize -
		    blkcfg->topology.alignment_offset * dp->d_sectorsize) %
		    dp->d_stripesize;
	}

	if (vtblk_write_cache_enabled(sc, blkcfg) != 0)
		sc->vtblk_write_cache = VTBLK_CACHE_WRITEBACK;
	else
		sc->vtblk_write_cache = VTBLK_CACHE_WRITETHROUGH;
}