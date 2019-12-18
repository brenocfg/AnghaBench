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
struct sfxge_intr {scalar_t__ state; int /*<<< orphan*/  status; } ;
struct sfxge_softc {struct sfxge_intr intr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  efsys_mem_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_INTR_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_INTR_INITIALIZED ; 
 scalar_t__ SFXGE_INTR_UNINITIALIZED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int sfxge_dma_alloc (struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sfxge_intr_setup_fixed (struct sfxge_softc*) ; 
 int sfxge_intr_setup_msi (struct sfxge_softc*) ; 
 int sfxge_intr_setup_msix (struct sfxge_softc*) ; 

int
sfxge_intr_init(struct sfxge_softc *sc)
{
	device_t dev;
	struct sfxge_intr *intr;
	efsys_mem_t *esmp;
	int rc;

	dev = sc->dev;
	intr = &sc->intr;
	esmp = &intr->status;

	KASSERT(intr->state == SFXGE_INTR_UNINITIALIZED,
	    ("Interrupts already initialized"));

	/* Try to setup MSI-X or MSI interrupts if available. */
	if ((rc = sfxge_intr_setup_msix(sc)) == 0)
		device_printf(dev, "Using MSI-X interrupts\n");
	else if ((rc = sfxge_intr_setup_msi(sc)) == 0)
		device_printf(dev, "Using MSI interrupts\n");
	else if ((rc = sfxge_intr_setup_fixed(sc)) == 0) {
		device_printf(dev, "Using fixed interrupts\n");
	} else {
		device_printf(dev, "Couldn't setup interrupts\n");
		return (ENOMEM);
	}

	/* Set up DMA for interrupts. */
	if ((rc = sfxge_dma_alloc(sc, EFX_INTR_SIZE, esmp)) != 0)
		return (ENOMEM);

	intr->state = SFXGE_INTR_INITIALIZED;

	return (0);
}