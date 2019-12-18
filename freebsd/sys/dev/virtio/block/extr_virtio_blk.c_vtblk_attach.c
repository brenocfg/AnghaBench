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
struct vtblk_softc {scalar_t__ vtblk_max_nsegs; int /*<<< orphan*/  vtblk_vq; int /*<<< orphan*/ * vtblk_sglist; int /*<<< orphan*/  vtblk_req_ready; int /*<<< orphan*/  vtblk_req_free; int /*<<< orphan*/  vtblk_dump_queue; int /*<<< orphan*/  vtblk_bioq; int /*<<< orphan*/  vtblk_dev; } ;
struct virtio_blk_config {scalar_t__ size_max; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int INTR_ENTROPY ; 
 int INTR_TYPE_BIO ; 
 scalar_t__ MAXPHYS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIRTIO_BLK_F_SIZE_MAX ; 
 int /*<<< orphan*/  VTBLK_LOCK_INIT (struct vtblk_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ VTBLK_MIN_SEGMENTS ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vtblk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * sglist_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_set_feature_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtio_setup_intr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ virtio_with_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_enable_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_alloc_disk (struct vtblk_softc*,struct virtio_blk_config*) ; 
 int vtblk_alloc_virtqueue (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_create_disk (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_feature_desc ; 
 scalar_t__ vtblk_maximum_segments (struct vtblk_softc*,struct virtio_blk_config*) ; 
 int /*<<< orphan*/  vtblk_read_config (struct vtblk_softc*,struct virtio_blk_config*) ; 
 int vtblk_request_prealloc (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_setup_features (struct vtblk_softc*) ; 
 int /*<<< orphan*/  vtblk_setup_sysctl (struct vtblk_softc*) ; 

__attribute__((used)) static int
vtblk_attach(device_t dev)
{
	struct vtblk_softc *sc;
	struct virtio_blk_config blkcfg;
	int error;

	virtio_set_feature_desc(dev, vtblk_feature_desc);

	sc = device_get_softc(dev);
	sc->vtblk_dev = dev;
	VTBLK_LOCK_INIT(sc, device_get_nameunit(dev));
	bioq_init(&sc->vtblk_bioq);
	TAILQ_INIT(&sc->vtblk_dump_queue);
	TAILQ_INIT(&sc->vtblk_req_free);
	TAILQ_INIT(&sc->vtblk_req_ready);

	vtblk_setup_sysctl(sc);
	vtblk_setup_features(sc);

	vtblk_read_config(sc, &blkcfg);

	/*
	 * With the current sglist(9) implementation, it is not easy
	 * for us to support a maximum segment size as adjacent
	 * segments are coalesced. For now, just make sure it's larger
	 * than the maximum supported transfer size.
	 */
	if (virtio_with_feature(dev, VIRTIO_BLK_F_SIZE_MAX)) {
		if (blkcfg.size_max < MAXPHYS) {
			error = ENOTSUP;
			device_printf(dev, "host requires unsupported "
			    "maximum segment size feature\n");
			goto fail;
		}
	}

	sc->vtblk_max_nsegs = vtblk_maximum_segments(sc, &blkcfg);
	if (sc->vtblk_max_nsegs <= VTBLK_MIN_SEGMENTS) {
		error = EINVAL;
		device_printf(dev, "fewer than minimum number of segments "
		    "allowed: %d\n", sc->vtblk_max_nsegs);
		goto fail;
	}

	sc->vtblk_sglist = sglist_alloc(sc->vtblk_max_nsegs, M_NOWAIT);
	if (sc->vtblk_sglist == NULL) {
		error = ENOMEM;
		device_printf(dev, "cannot allocate sglist\n");
		goto fail;
	}

	error = vtblk_alloc_virtqueue(sc);
	if (error) {
		device_printf(dev, "cannot allocate virtqueue\n");
		goto fail;
	}

	error = vtblk_request_prealloc(sc);
	if (error) {
		device_printf(dev, "cannot preallocate requests\n");
		goto fail;
	}

	vtblk_alloc_disk(sc, &blkcfg);

	error = virtio_setup_intr(dev, INTR_TYPE_BIO | INTR_ENTROPY);
	if (error) {
		device_printf(dev, "cannot setup virtqueue interrupt\n");
		goto fail;
	}

	vtblk_create_disk(sc);

	virtqueue_enable_intr(sc->vtblk_vq);

fail:
	if (error)
		vtblk_detach(dev);

	return (error);
}