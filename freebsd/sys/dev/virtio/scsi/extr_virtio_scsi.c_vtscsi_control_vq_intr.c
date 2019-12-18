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
struct vtscsi_softc {struct virtqueue* vtscsi_control_vq; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTSCSI_LOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  VTSCSI_UNLOCK (struct vtscsi_softc*) ; 
 int /*<<< orphan*/  virtqueue_disable_intr (struct virtqueue*) ; 
 scalar_t__ virtqueue_enable_intr (struct virtqueue*) ; 
 int /*<<< orphan*/  vtscsi_complete_vq (struct vtscsi_softc*,struct virtqueue*) ; 

__attribute__((used)) static void
vtscsi_control_vq_intr(void *xsc)
{
	struct vtscsi_softc *sc;
	struct virtqueue *vq;

	sc = xsc;
	vq = sc->vtscsi_control_vq;

again:
	VTSCSI_LOCK(sc);

	vtscsi_complete_vq(sc, sc->vtscsi_control_vq);

	if (virtqueue_enable_intr(vq) != 0) {
		virtqueue_disable_intr(vq);
		VTSCSI_UNLOCK(sc);
		goto again;
	}

	VTSCSI_UNLOCK(sc);
}