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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_dev; } ;
struct virtio_scsi_event {int event; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VIRTIO_SCSI_T_EVENTS_MISSED ; 
#define  VIRTIO_SCSI_T_TRANSPORT_RESET 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int vtscsi_enqueue_event_buf (struct vtscsi_softc*,struct virtio_scsi_event*) ; 
 int /*<<< orphan*/  vtscsi_execute_rescan_bus (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  vtscsi_transport_reset_event (struct vtscsi_softc*,struct virtio_scsi_event*) ; 

__attribute__((used)) static void
vtscsi_handle_event(struct vtscsi_softc *sc, struct virtio_scsi_event *event)
{
	int error;

	if ((event->event & VIRTIO_SCSI_T_EVENTS_MISSED) == 0) {
		switch (event->event) {
		case VIRTIO_SCSI_T_TRANSPORT_RESET:
			vtscsi_transport_reset_event(sc, event);
			break;
		default:
			device_printf(sc->vtscsi_dev,
			    "unhandled event: %d\n", event->event);
			break;
		}
	} else
		vtscsi_execute_rescan_bus(sc);

	/*
	 * This should always be successful since the buffer
	 * was just dequeued.
	 */
	error = vtscsi_enqueue_event_buf(sc, event);
	KASSERT(error == 0,
	    ("cannot requeue event buffer: %d", error));
}