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
struct sec_softc {int sc_shutdown; int /*<<< orphan*/  sc_descriptors_lock; int /*<<< orphan*/  sc_controller_lock; int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/  sc_rrid; int /*<<< orphan*/  sc_sec_irid; int /*<<< orphan*/  sc_sec_ihand; int /*<<< orphan*/  sc_sec_ires; int /*<<< orphan*/  sc_pri_irid; int /*<<< orphan*/  sc_pri_ihand; int /*<<< orphan*/  sc_pri_ires; int /*<<< orphan*/  sc_desc_dmem; int /*<<< orphan*/  sc_lt_dmem; int /*<<< orphan*/ * sc_desc; int /*<<< orphan*/  sc_cid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int SEC_CHANNELS ; 
 int SEC_DESCRIPTORS ; 
 int /*<<< orphan*/  SEC_DESC_FREE_POINTERS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEC_IER ; 
 int /*<<< orphan*/  SEC_LOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int SEC_QUEUED_DESC_CNT (struct sec_softc*) ; 
 int SEC_READY_DESC_CNT (struct sec_softc*) ; 
 int SEC_TIMEOUT ; 
 int /*<<< orphan*/  SEC_UNLOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_WRITE (struct sec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  descriptors ; 
 struct sec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_channel_reset (struct sec_softc*,int,int) ; 
 int /*<<< orphan*/  sec_free_dma_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_release_intr (struct sec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
sec_detach(device_t dev)
{
	struct sec_softc *sc = device_get_softc(dev);
	int i, error, timeout = SEC_TIMEOUT;

	/* Prepare driver to shutdown */
	SEC_LOCK(sc, descriptors);
	sc->sc_shutdown = 1;
	SEC_UNLOCK(sc, descriptors);

	/* Wait until all queued processing finishes */
	while (1) {
		SEC_LOCK(sc, descriptors);
		i = SEC_READY_DESC_CNT(sc) + SEC_QUEUED_DESC_CNT(sc);
		SEC_UNLOCK(sc, descriptors);

		if (i == 0)
			break;

		if (timeout < 0) {
			device_printf(dev, "queue flush timeout!\n");

			/* DMA can be still active - stop it */
			for (i = 0; i < SEC_CHANNELS; i++)
				sec_channel_reset(sc, i, 1);

			break;
		}

		timeout -= 1000;
		DELAY(1000);
	}

	/* Disable interrupts */
	SEC_WRITE(sc, SEC_IER, 0);

	/* Unregister from OCF */
	crypto_unregister_all(sc->sc_cid);

	/* Free DMA memory */
	for (i = 0; i < SEC_DESCRIPTORS; i++)
		SEC_DESC_FREE_POINTERS(&(sc->sc_desc[i]));

	sec_free_dma_mem(&(sc->sc_lt_dmem));
	sec_free_dma_mem(&(sc->sc_desc_dmem));

	/* Release interrupts */
	sec_release_intr(sc, sc->sc_pri_ires, sc->sc_pri_ihand,
	    sc->sc_pri_irid, "primary");
	sec_release_intr(sc, sc->sc_sec_ires, sc->sc_sec_ihand,
	    sc->sc_sec_irid, "secondary");

	/* Release memory */
	if (sc->sc_rres) {
		error = bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rrid,
		    sc->sc_rres);
		if (error)
			device_printf(dev, "bus_release_resource() failed for"
			    " I/O memory, error %d\n", error);

		sc->sc_rres = NULL;
	}

	mtx_destroy(&sc->sc_controller_lock);
	mtx_destroy(&sc->sc_descriptors_lock);

	return (0);
}