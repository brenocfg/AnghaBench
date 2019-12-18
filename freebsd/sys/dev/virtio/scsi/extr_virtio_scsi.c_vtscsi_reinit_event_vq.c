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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VTSCSI_FLAG_HOTPLUG ; 
 int VTSCSI_NUM_EVENT_BUFS ; 
 int vtscsi_enqueue_event_buf (struct vtscsi_softc*,struct virtio_scsi_event*) ; 

__attribute__((used)) static void
vtscsi_reinit_event_vq(struct vtscsi_softc *sc)
{
	struct virtio_scsi_event *event;
	int i, error;

	if ((sc->vtscsi_flags & VTSCSI_FLAG_HOTPLUG) == 0 ||
	    sc->vtscsi_event_buf_size < sizeof(struct virtio_scsi_event))
		return;

	for (i = 0; i < VTSCSI_NUM_EVENT_BUFS; i++) {
		event = &sc->vtscsi_event_bufs[i];

		error = vtscsi_enqueue_event_buf(sc, event);
		if (error)
			break;
	}

	KASSERT(i > 0, ("cannot reinit event vq: %d", error));
}