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
struct vtscsi_softc {int vtscsi_flags; int vtscsi_event_buf_size; struct virtio_scsi_event* vtscsi_event_bufs; } ;
struct virtio_scsi_event {int dummy; } ;

/* Variables and functions */
 int VTSCSI_FLAG_HOTPLUG ; 
 int VTSCSI_NUM_EVENT_BUFS ; 
 int vtscsi_enqueue_event_buf (struct vtscsi_softc*,struct virtio_scsi_event*) ; 

__attribute__((used)) static int
vtscsi_init_event_vq(struct vtscsi_softc *sc)
{
	struct virtio_scsi_event *event;
	int i, size, error;

	/*
	 * The first release of QEMU with VirtIO SCSI support would crash
	 * when attempting to notify the event virtqueue. This was fixed
	 * when hotplug support was added.
	 */
	if (sc->vtscsi_flags & VTSCSI_FLAG_HOTPLUG)
		size = sc->vtscsi_event_buf_size;
	else
		size = 0;

	if (size < sizeof(struct virtio_scsi_event))
		return (0);

	for (i = 0; i < VTSCSI_NUM_EVENT_BUFS; i++) {
		event = &sc->vtscsi_event_bufs[i];

		error = vtscsi_enqueue_event_buf(sc, event);
		if (error)
			break;
	}

	/*
	 * Even just one buffer is enough. Missed events are
	 * denoted with the VIRTIO_SCSI_T_EVENTS_MISSED flag.
	 */
	if (i > 0)
		error = 0;

	return (error);
}