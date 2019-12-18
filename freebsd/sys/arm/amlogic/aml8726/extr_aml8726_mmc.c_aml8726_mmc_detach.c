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
struct aml8726_mmc_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  dmatag; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  ih_cookie; int /*<<< orphan*/  ch; int /*<<< orphan*/ * cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_MMC_IRQ_STATUS_CLEAR_IRQ ; 
 int /*<<< orphan*/  AML_MMC_IRQ_STATUS_REG ; 
 int /*<<< orphan*/  AML_MMC_LOCK (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  AML_MMC_LOCK_DESTROY (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  AML_MMC_UNLOCK (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_mmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  aml8726_mmc_power_off (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  aml8726_mmc_soft_reset (struct aml8726_mmc_softc*,int) ; 
 int /*<<< orphan*/  aml8726_mmc_spec ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct aml8726_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_mmc_detach(device_t dev)
{
	struct aml8726_mmc_softc *sc = device_get_softc(dev);

	AML_MMC_LOCK(sc);

	if (sc->cmd != NULL) {
		AML_MMC_UNLOCK(sc);
		return (EBUSY);
	}

	/*
	 * Turn off the power, reset the hardware state machine,
	 * disable the interrupts, and clear the interrupts.
	 */
	(void)aml8726_mmc_power_off(sc);
	aml8726_mmc_soft_reset(sc, false);
	CSR_WRITE_4(sc, AML_MMC_IRQ_STATUS_REG, AML_MMC_IRQ_STATUS_CLEAR_IRQ);

	/* This should be a NOP since no command was in flight. */
	callout_stop(&sc->ch);

	AML_MMC_UNLOCK(sc);

	bus_generic_detach(dev);

	bus_teardown_intr(dev, sc->res[1], sc->ih_cookie);

	bus_dmamap_destroy(sc->dmatag, sc->dmamap);

	bus_dma_tag_destroy(sc->dmatag);

	AML_MMC_LOCK_DESTROY(sc);

	bus_release_resources(dev, aml8726_mmc_spec, sc->res);

	return (0);
}