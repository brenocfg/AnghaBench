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
typedef  scalar_t__ uint32_t ;
struct sfxge_mcdi {scalar_t__ state; } ;
struct sfxge_softc {int /*<<< orphan*/  enp; struct sfxge_mcdi mcdi; } ;
typedef  int /*<<< orphan*/  efx_mcdi_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_MCDI_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_MCDI_LOCK (struct sfxge_mcdi*) ; 
 int /*<<< orphan*/  SFXGE_MCDI_UNLOCK (struct sfxge_mcdi*) ; 
 int /*<<< orphan*/  efx_mcdi_get_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  efx_mcdi_request_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_mcdi_poll (struct sfxge_softc*,scalar_t__) ; 

__attribute__((used)) static void
sfxge_mcdi_execute(void *arg, efx_mcdi_req_t *emrp)
{
	struct sfxge_softc *sc;
	struct sfxge_mcdi *mcdi;
	uint32_t timeout_us = 0;

	sc = (struct sfxge_softc *)arg;
	mcdi = &sc->mcdi;

	SFXGE_MCDI_LOCK(mcdi);

	KASSERT(mcdi->state == SFXGE_MCDI_INITIALIZED,
	    ("MCDI not initialized"));

	/* Issue request and poll for completion. */
	efx_mcdi_get_timeout(sc->enp, emrp, &timeout_us);
	KASSERT(timeout_us > 0, ("MCDI timeout not initialized"));

	efx_mcdi_request_start(sc->enp, emrp, B_FALSE);
	sfxge_mcdi_poll(sc, timeout_us);

	SFXGE_MCDI_UNLOCK(mcdi);
}