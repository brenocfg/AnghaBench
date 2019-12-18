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
struct sfxge_mcdi {scalar_t__ state; } ;
struct sfxge_softc {struct sfxge_mcdi mcdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_MCDI_INITIALIZED ; 

__attribute__((used)) static void
sfxge_mcdi_ev_cpl(void *arg)
{
	struct sfxge_softc *sc;
	struct sfxge_mcdi *mcdi;

	sc = (struct sfxge_softc *)arg;
	mcdi = &sc->mcdi;

	KASSERT(mcdi->state == SFXGE_MCDI_INITIALIZED,
	    ("MCDI not initialized"));

	/* We do not use MCDI completion, MCDI is simply polled */
}