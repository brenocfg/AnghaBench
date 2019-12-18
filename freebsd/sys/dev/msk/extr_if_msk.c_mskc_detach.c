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
struct msk_softc {int msk_pflags; int /*<<< orphan*/  msk_mtx; int /*<<< orphan*/ * msk_res; int /*<<< orphan*/  msk_res_spec; int /*<<< orphan*/ * msk_irq; int /*<<< orphan*/  msk_irq_spec; int /*<<< orphan*/ * msk_intrhand; int /*<<< orphan*/ ** msk_devs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_HWE_IMSK ; 
 int /*<<< orphan*/  B0_IMSK ; 
 int /*<<< orphan*/  CSR_READ_4 (struct msk_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_RST_SET ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int MSK_FLAG_MSI ; 
 size_t MSK_PORT_A ; 
 size_t MSK_PORT_B ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  Y2_LED_STAT_OFF ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ *) ; 
 struct msk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msk_status_dma_free (struct msk_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mskc_detach(device_t dev)
{
	struct msk_softc *sc;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->msk_mtx), ("msk mutex not initialized"));

	if (device_is_alive(dev)) {
		if (sc->msk_devs[MSK_PORT_A] != NULL) {
			free(device_get_ivars(sc->msk_devs[MSK_PORT_A]),
			    M_DEVBUF);
			device_delete_child(dev, sc->msk_devs[MSK_PORT_A]);
		}
		if (sc->msk_devs[MSK_PORT_B] != NULL) {
			free(device_get_ivars(sc->msk_devs[MSK_PORT_B]),
			    M_DEVBUF);
			device_delete_child(dev, sc->msk_devs[MSK_PORT_B]);
		}
		bus_generic_detach(dev);
	}

	/* Disable all interrupts. */
	CSR_WRITE_4(sc, B0_IMSK, 0);
	CSR_READ_4(sc, B0_IMSK);
	CSR_WRITE_4(sc, B0_HWE_IMSK, 0);
	CSR_READ_4(sc, B0_HWE_IMSK);

	/* LED Off. */
	CSR_WRITE_2(sc, B0_CTST, Y2_LED_STAT_OFF);

	/* Put hardware reset. */
	CSR_WRITE_2(sc, B0_CTST, CS_RST_SET);

	msk_status_dma_free(sc);

	if (sc->msk_intrhand) {
		bus_teardown_intr(dev, sc->msk_irq[0], sc->msk_intrhand);
		sc->msk_intrhand = NULL;
	}
	bus_release_resources(dev, sc->msk_irq_spec, sc->msk_irq);
	if ((sc->msk_pflags & MSK_FLAG_MSI) != 0)
		pci_release_msi(dev);
	bus_release_resources(dev, sc->msk_res_spec, sc->msk_res);
	mtx_destroy(&sc->msk_mtx);

	return (0);
}