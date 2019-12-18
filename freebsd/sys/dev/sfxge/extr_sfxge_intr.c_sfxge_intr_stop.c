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
struct sfxge_intr {scalar_t__ state; } ;
struct sfxge_softc {int /*<<< orphan*/  enp; struct sfxge_intr intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_INTR_INITIALIZED ; 
 scalar_t__ SFXGE_INTR_STARTED ; 
 int /*<<< orphan*/  efx_intr_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_intr_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_intr_bus_disable (struct sfxge_softc*) ; 

void
sfxge_intr_stop(struct sfxge_softc *sc)
{
	struct sfxge_intr *intr;

	intr = &sc->intr;

	KASSERT(intr->state == SFXGE_INTR_STARTED,
	    ("Interrupts not started"));

	intr->state = SFXGE_INTR_INITIALIZED;

	/* Disable interrupts at the NIC */
	efx_intr_disable(sc->enp);

	/* Disable interrupts at the bus */
	sfxge_intr_bus_disable(sc);

	/* Tear down common code interrupt bits. */
	efx_intr_fini(sc->enp);
}