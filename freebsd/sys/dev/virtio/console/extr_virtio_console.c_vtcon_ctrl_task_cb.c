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
typedef  int uint32_t ;
struct vtcon_softc {int vtcon_flags; int /*<<< orphan*/  vtcon_ctrl_task; struct virtqueue* vtcon_ctrl_rxvq; } ;
struct virtqueue {int dummy; } ;
struct virtio_console_control {int dummy; } ;

/* Variables and functions */
 int VTCON_FLAG_DETACHED ; 
 int /*<<< orphan*/  VTCON_LOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  VTCON_UNLOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 struct virtio_console_control* virtqueue_dequeue (struct virtqueue*,int*) ; 
 scalar_t__ virtqueue_enable_intr (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_notify (struct virtqueue*) ; 
 int /*<<< orphan*/  vtcon_ctrl_event_requeue (struct vtcon_softc*,struct virtio_console_control*) ; 
 int /*<<< orphan*/  vtcon_ctrl_process_event (struct vtcon_softc*,struct virtio_console_control*,void*,size_t) ; 

__attribute__((used)) static void
vtcon_ctrl_task_cb(void *xsc, int pending)
{
	struct vtcon_softc *sc;
	struct virtqueue *vq;
	struct virtio_console_control *control;
	void *data;
	size_t data_len;
	int detached;
	uint32_t len;

	sc = xsc;
	vq = sc->vtcon_ctrl_rxvq;

	VTCON_LOCK(sc);

	while ((detached = (sc->vtcon_flags & VTCON_FLAG_DETACHED)) == 0) {
		control = virtqueue_dequeue(vq, &len);
		if (control == NULL)
			break;

		if (len > sizeof(struct virtio_console_control)) {
			data = (void *) &control[1];
			data_len = len - sizeof(struct virtio_console_control);
		} else {
			data = NULL;
			data_len = 0;
		}

		VTCON_UNLOCK(sc);
		vtcon_ctrl_process_event(sc, control, data, data_len);
		VTCON_LOCK(sc);
		vtcon_ctrl_event_requeue(sc, control);
	}

	if (!detached) {
		virtqueue_notify(vq);
		if (virtqueue_enable_intr(vq) != 0)
			taskqueue_enqueue(taskqueue_thread,
			    &sc->vtcon_ctrl_task);
	}

	VTCON_UNLOCK(sc);
}