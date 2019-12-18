#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vtbe_softc {int /*<<< orphan*/  pio_send; struct vqueue_info* vs_queues; } ;
struct vqueue_info {TYPE_1__* vq_used; int /*<<< orphan*/  vq_save_used; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIO_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_INTR ; 
 int /*<<< orphan*/  VIRTIO_MMIO_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  VIRTIO_MMIO_INT_VRING ; 
 int /*<<< orphan*/  WRITE4 (struct vtbe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int htobe32 (int /*<<< orphan*/ ) ; 
 scalar_t__ vq_has_descs (struct vqueue_info*) ; 
 int /*<<< orphan*/  vq_ring_ready (struct vqueue_info*) ; 
 int /*<<< orphan*/  vtbe_proc_rx (struct vtbe_softc*,struct vqueue_info*) ; 

__attribute__((used)) static void
vtbe_rxfinish_locked(struct vtbe_softc *sc)
{
	struct vqueue_info *vq;
	int reg;

	/* TX queue */
	vq = &sc->vs_queues[1];
	if (!vq_ring_ready(vq))
		return;

	/* Process new descriptors */
	vq->vq_save_used = be16toh(vq->vq_used->idx);

	while (vq_has_descs(vq)) {
		vtbe_proc_rx(sc, vq);
	}

	/* Interrupt the other side */
	reg = htobe32(VIRTIO_MMIO_INT_VRING);
	WRITE4(sc, VIRTIO_MMIO_INTERRUPT_STATUS, reg);

	PIO_SET(sc->pio_send, Q_INTR, 1);
}