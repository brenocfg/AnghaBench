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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_long ;
struct psycho_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  PSR_CE_AFA ; 
 int /*<<< orphan*/  PSR_CE_AFS ; 
 scalar_t__ PSYCHO_READ8 (struct psycho_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSYCHO_WRITE8 (struct psycho_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
psycho_ce(void *arg)
{
	struct psycho_softc *sc = arg;
	uint64_t afar, afsr;

	mtx_lock_spin(sc->sc_mtx);
	afar = PSYCHO_READ8(sc, PSR_CE_AFA);
	afsr = PSYCHO_READ8(sc, PSR_CE_AFS);
	device_printf(sc->sc_dev, "correctable DMA error AFAR %#lx "
	    "AFSR %#lx\n", (u_long)afar, (u_long)afsr);
	/* Clear the error bits that we caught. */
	PSYCHO_WRITE8(sc, PSR_CE_AFS, afsr);
	mtx_unlock_spin(sc->sc_mtx);
	return (FILTER_HANDLED);
}