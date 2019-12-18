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
struct virtio_mmio_platform_softc {int /*<<< orphan*/  ih_user; int /*<<< orphan*/  (* intr_handler ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  pio_recv; scalar_t__ use_pio; } ;

/* Variables and functions */
 int PIO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIO_SET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_dcache_wbinv_all () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
platform_intr(void *arg)
{
	struct virtio_mmio_platform_softc *sc;
	int reg;

	sc = arg;

	if (sc->use_pio) {
		/* Read pending */
		reg = PIO_READ(sc->pio_recv);

		/* Ack */
		PIO_SET(sc->pio_recv, reg, 0);
	}

	/* Writeback, invalidate cache */
	mips_dcache_wbinv_all();

	if (sc->intr_handler != NULL)
		sc->intr_handler(sc->ih_user);
}