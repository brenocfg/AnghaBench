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
typedef  int /*<<< orphan*/  uint32_t ;
struct vtbe_softc {int /*<<< orphan*/  vs_curq; int /*<<< orphan*/  pio_recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIO_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Q_NOTIFY ; 
 int Q_NOTIFY1 ; 
 int Q_PFN ; 
 int Q_SEL ; 
 int /*<<< orphan*/  READ4 (struct vtbe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_SEL ; 
 int /*<<< orphan*/  VTBE_LOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  VTBE_UNLOCK (struct vtbe_softc*) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 
 int htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_init (struct vtbe_softc*) ; 
 int /*<<< orphan*/  vtbe_rxfinish_locked (struct vtbe_softc*) ; 
 int /*<<< orphan*/  vtbe_txfinish_locked (struct vtbe_softc*) ; 

__attribute__((used)) static void
vtbe_intr(void *arg)
{
	struct vtbe_softc *sc;
	int pending;
	uint32_t reg;

	sc = arg;

	VTBE_LOCK(sc);

	reg = PIO_READ(sc->pio_recv);

	/* Ack */
	PIO_SET(sc->pio_recv, reg, 0);

	pending = htobe32(reg);
	if (pending & Q_SEL) {
		reg = READ4(sc, VIRTIO_MMIO_QUEUE_SEL);
		sc->vs_curq = be32toh(reg);
	}

	if (pending & Q_PFN) {
		vq_init(sc);
	}

	if (pending & Q_NOTIFY) {
		/* beri rx / arm tx notify */
		vtbe_txfinish_locked(sc);
	}

	if (pending & Q_NOTIFY1) {
		vtbe_rxfinish_locked(sc);
	}

	VTBE_UNLOCK(sc);
}