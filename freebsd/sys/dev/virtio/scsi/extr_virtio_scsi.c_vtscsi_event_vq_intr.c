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
struct vtscsi_softc {struct virtqueue* vtscsi_event_vq; } ;
struct virtqueue {int dummy; } ;
struct virtio_scsi_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_LOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_UNLOCK (struct vtscsi_softc*) ; 
 struct virtio_scsi_event* virtqueue_dequeue (struct virtqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtqueue_disable_intr (struct virtqueue*) ; 
 scalar_t__ virtqueue_enable_intr (struct virtqueue*) ; 
 int /*<<< orphan*/  vtscsi_handle_event (struct vtscsi_softc*,struct virtio_scsi_event*) ; 

__attribute__((used)) static void
vtscsi_event_vq_intr(void *xsc)
{
	struct vtscsi_softc *sc;
	struct virtqueue *vq;
	struct virtio_scsi_event *event;

	sc = xsc;
	vq = sc->vtscsi_event_vq;

again:
	VTSCSI_LOCK(sc);

	while ((event = virtqueue_dequeue(vq, NULL)) != NULL)
		vtscsi_handle_event(sc, event);

	if (virtqueue_enable_intr(vq) != 0) {
		virtqueue_disable_intr(vq);
		VTSCSI_UNLOCK(sc);
		goto again;
	}

	VTSCSI_UNLOCK(sc);
}