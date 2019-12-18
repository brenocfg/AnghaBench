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
struct beri_vtblk_softc {int /*<<< orphan*/  pio_recv; } ;

/* Variables and functions */
 int PIO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIO_SET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int Q_NOTIFY ; 
 int Q_PFN ; 
 int htobe32 (int) ; 
 int /*<<< orphan*/  vq_init (struct beri_vtblk_softc*) ; 
 int /*<<< orphan*/  wakeup (struct beri_vtblk_softc*) ; 

__attribute__((used)) static void
vtblk_intr(void *arg)
{
	struct beri_vtblk_softc *sc;
	int pending;
	int reg;

	sc = arg;

	reg = PIO_READ(sc->pio_recv);

	/* Ack */
	PIO_SET(sc->pio_recv, reg, 0);

	pending = htobe32(reg);

	if (pending & Q_PFN) {
		vq_init(sc);
	}

	if (pending & Q_NOTIFY) {
		wakeup(sc);
	}
}