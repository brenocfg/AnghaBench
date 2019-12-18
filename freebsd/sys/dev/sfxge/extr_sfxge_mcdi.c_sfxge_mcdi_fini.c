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
struct sfxge_mcdi {scalar_t__ state; int /*<<< orphan*/  mem; int /*<<< orphan*/  transport; } ;
struct sfxge_softc {struct sfxge_mcdi mcdi; int /*<<< orphan*/ * enp; } ;
typedef  int /*<<< orphan*/  efx_nic_t ;
typedef  int /*<<< orphan*/  efx_mcdi_transport_t ;
typedef  int /*<<< orphan*/  efsys_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_MCDI_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_MCDI_LOCK (struct sfxge_mcdi*) ; 
 int /*<<< orphan*/  SFXGE_MCDI_LOCK_DESTROY (struct sfxge_mcdi*) ; 
 int /*<<< orphan*/  SFXGE_MCDI_UNLOCK (struct sfxge_mcdi*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  efx_mcdi_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 

void
sfxge_mcdi_fini(struct sfxge_softc *sc)
{
	struct sfxge_mcdi *mcdi;
	efx_nic_t *enp;
	efx_mcdi_transport_t *emtp;
	efsys_mem_t *esmp;

	enp = sc->enp;
	mcdi = &sc->mcdi;
	emtp = &mcdi->transport;
	esmp = &mcdi->mem;

	SFXGE_MCDI_LOCK(mcdi);
	KASSERT(mcdi->state == SFXGE_MCDI_INITIALIZED,
	    ("MCDI not initialized"));

	efx_mcdi_fini(enp);
	bzero(emtp, sizeof(*emtp));

	SFXGE_MCDI_UNLOCK(mcdi);

	sfxge_dma_free(esmp);

	SFXGE_MCDI_LOCK_DESTROY(mcdi);
}