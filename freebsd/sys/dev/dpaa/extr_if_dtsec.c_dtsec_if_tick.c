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
struct dtsec_softc {int /*<<< orphan*/  sc_tick_callout; int /*<<< orphan*/  sc_mii; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  DTSEC_UNLOCK (struct dtsec_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct dtsec_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtsec_if_tick(void *arg)
{
	struct dtsec_softc *sc;

	sc = arg;

	/* TODO */
	DTSEC_LOCK(sc);

	mii_tick(sc->sc_mii);
	callout_reset(&sc->sc_tick_callout, hz, dtsec_if_tick, sc);

	DTSEC_UNLOCK(sc);
}