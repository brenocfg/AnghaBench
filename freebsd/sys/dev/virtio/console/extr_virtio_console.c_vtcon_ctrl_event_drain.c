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
struct vtcon_softc {struct virtqueue* vtcon_ctrl_rxvq; } ;
struct virtqueue {int dummy; } ;
struct virtio_console_control {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  VTCON_LOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  VTCON_UNLOCK (struct vtcon_softc*) ; 
 int /*<<< orphan*/  free (struct virtio_console_control*,int /*<<< orphan*/ ) ; 
 struct virtio_console_control* virtqueue_drain (struct virtqueue*,int*) ; 

__attribute__((used)) static void
vtcon_ctrl_event_drain(struct vtcon_softc *sc)
{
	struct virtio_console_control *control;
	struct virtqueue *vq;
	int last;

	vq = sc->vtcon_ctrl_rxvq;
	last = 0;

	if (vq == NULL)
		return;

	VTCON_LOCK(sc);
	while ((control = virtqueue_drain(vq, &last)) != NULL)
		free(control, M_DEVBUF);
	VTCON_UNLOCK(sc);
}