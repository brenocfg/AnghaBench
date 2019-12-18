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
struct vtscsi_softc {int /*<<< orphan*/ * vtscsi_sglist; int /*<<< orphan*/  vtscsi_max_nsegs; int /*<<< orphan*/  vtscsi_event_buf_size; int /*<<< orphan*/  vtscsi_max_lun; int /*<<< orphan*/  vtscsi_max_target; int /*<<< orphan*/  vtscsi_max_channel; int /*<<< orphan*/  vtscsi_flags; int /*<<< orphan*/  vtscsi_req_free; int /*<<< orphan*/  vtscsi_dev; } ;
struct virtio_scsi_config {int /*<<< orphan*/  seg_max; int /*<<< orphan*/  event_info_size; int /*<<< orphan*/  max_lun; int /*<<< orphan*/  max_target; int /*<<< orphan*/  max_channel; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTR_TYPE_CAM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIRTIO_RING_F_INDIRECT_DESC ; 
 int /*<<< orphan*/  VIRTIO_SCSI_F_HOTPLUG ; 
 int /*<<< orphan*/  VIRTIO_SCSI_F_INOUT ; 
 int /*<<< orphan*/  VTSCSI_FLAG_BIDIRECTIONAL ; 
 int /*<<< orphan*/  VTSCSI_FLAG_HOTPLUG ; 
 int /*<<< orphan*/  VTSCSI_FLAG_INDIRECT ; 
 int /*<<< orphan*/  VTSCSI_LOCK_INIT (struct vtscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vtscsi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * sglist_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_set_feature_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtio_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ virtio_with_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_add_sysctl (struct vtscsi_softc*) ; 
 int vtscsi_alloc_cam (struct vtscsi_softc*) ; 
 int vtscsi_alloc_requests (struct vtscsi_softc*) ; 
 int vtscsi_alloc_virtqueues (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_check_sizes (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_enable_vqs_intr (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_feature_desc ; 
 int /*<<< orphan*/  vtscsi_get_tunables (struct vtscsi_softc*) ; 
 int vtscsi_init_event_vq (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_maximum_segments (struct vtscsi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtscsi_negotiate_features (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_read_config (struct vtscsi_softc*,struct virtio_scsi_config*) ; 
 int vtscsi_register_cam (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_write_device_config (struct vtscsi_softc*) ; 

__attribute__((used)) static int
vtscsi_attach(device_t dev)
{
	struct vtscsi_softc *sc;
	struct virtio_scsi_config scsicfg;
	int error;

	sc = device_get_softc(dev);
	sc->vtscsi_dev = dev;

	VTSCSI_LOCK_INIT(sc, device_get_nameunit(dev));
	TAILQ_INIT(&sc->vtscsi_req_free);

	vtscsi_get_tunables(sc);
	vtscsi_add_sysctl(sc);

	virtio_set_feature_desc(dev, vtscsi_feature_desc);
	vtscsi_negotiate_features(sc);

	if (virtio_with_feature(dev, VIRTIO_RING_F_INDIRECT_DESC))
		sc->vtscsi_flags |= VTSCSI_FLAG_INDIRECT;
	if (virtio_with_feature(dev, VIRTIO_SCSI_F_INOUT))
		sc->vtscsi_flags |= VTSCSI_FLAG_BIDIRECTIONAL;
	if (virtio_with_feature(dev, VIRTIO_SCSI_F_HOTPLUG))
		sc->vtscsi_flags |= VTSCSI_FLAG_HOTPLUG;

	vtscsi_read_config(sc, &scsicfg);

	sc->vtscsi_max_channel = scsicfg.max_channel;
	sc->vtscsi_max_target = scsicfg.max_target;
	sc->vtscsi_max_lun = scsicfg.max_lun;
	sc->vtscsi_event_buf_size = scsicfg.event_info_size;

	vtscsi_write_device_config(sc);

	sc->vtscsi_max_nsegs = vtscsi_maximum_segments(sc, scsicfg.seg_max);
	sc->vtscsi_sglist = sglist_alloc(sc->vtscsi_max_nsegs, M_NOWAIT);
	if (sc->vtscsi_sglist == NULL) {
		error = ENOMEM;
		device_printf(dev, "cannot allocate sglist\n");
		goto fail;
	}

	error = vtscsi_alloc_virtqueues(sc);
	if (error) {
		device_printf(dev, "cannot allocate virtqueues\n");
		goto fail;
	}

	vtscsi_check_sizes(sc);

	error = vtscsi_init_event_vq(sc);
	if (error) {
		device_printf(dev, "cannot populate the eventvq\n");
		goto fail;
	}

	error = vtscsi_alloc_requests(sc);
	if (error) {
		device_printf(dev, "cannot allocate requests\n");
		goto fail;
	}

	error = vtscsi_alloc_cam(sc);
	if (error) {
		device_printf(dev, "cannot allocate CAM structures\n");
		goto fail;
	}

	error = virtio_setup_intr(dev, INTR_TYPE_CAM);
	if (error) {
		device_printf(dev, "cannot setup virtqueue interrupts\n");
		goto fail;
	}

	vtscsi_enable_vqs_intr(sc);

	/*
	 * Register with CAM after interrupts are enabled so we will get
	 * notified of the probe responses.
	 */
	error = vtscsi_register_cam(sc);
	if (error) {
		device_printf(dev, "cannot register with CAM\n");
		goto fail;
	}

fail:
	if (error)
		vtscsi_detach(dev);

	return (error);
}