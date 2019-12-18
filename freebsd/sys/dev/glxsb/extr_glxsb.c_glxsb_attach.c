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
typedef  int uint64_t ;
struct glxsb_softc {int sc_rnghz; int /*<<< orphan*/ * sc_sr; int /*<<< orphan*/  sc_rid; int /*<<< orphan*/ * sc_tq; int /*<<< orphan*/  sc_rngco; int /*<<< orphan*/  sc_cryptotask; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SB_AES_INT ; 
 int /*<<< orphan*/  SB_AI_CLEAR_INTR ; 
 int /*<<< orphan*/  SB_GLD_MSR_CAP ; 
 int /*<<< orphan*/  SB_GLD_MSR_CTRL ; 
 int SB_GMC_SBI ; 
 int SB_GMC_SBY ; 
 int SB_GMC_T_NE ; 
 int SB_GMC_T_SEL3 ; 
 int SB_GMC_T_SEL_MASK ; 
 int SB_GMC_T_TM ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct glxsb_softc*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct glxsb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ glxsb_crypto_setup (struct glxsb_softc*) ; 
 int /*<<< orphan*/  glxsb_crypto_task ; 
 scalar_t__ glxsb_dma_alloc (struct glxsb_softc*) ; 
 int /*<<< orphan*/  glxsb_rnd (struct glxsb_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int rdmsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taskqueue_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 scalar_t__ taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
glxsb_attach(device_t dev)
{
	struct glxsb_softc *sc = device_get_softc(dev);
	uint64_t msr;

	sc->sc_dev = dev;
	msr = rdmsr(SB_GLD_MSR_CAP);

	if ((msr & 0xFFFF00) != 0x130400) {
		device_printf(dev, "unknown ID 0x%x\n",
		    (int)((msr & 0xFFFF00) >> 16));
		return (ENXIO);
	}

	pci_enable_busmaster(dev);

	/* Map in the security block configuration/control registers */
	sc->sc_rid = PCIR_BAR(0);
	sc->sc_sr = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_rid,
	    RF_ACTIVE);
	if (sc->sc_sr == NULL) {
		device_printf(dev, "cannot map register space\n");
		return (ENXIO);
	}

	/*
	 * Configure the Security Block.
	 *
	 * We want to enable the noise generator (T_NE), and enable the
	 * linear feedback shift register and whitener post-processing
	 * (T_SEL = 3).  Also ensure that test mode (deterministic values)
	 * is disabled.
	 */
	msr = rdmsr(SB_GLD_MSR_CTRL);
	msr &= ~(SB_GMC_T_TM | SB_GMC_T_SEL_MASK);
	msr |= SB_GMC_T_NE | SB_GMC_T_SEL3;
#if 0
	msr |= SB_GMC_SBI | SB_GMC_SBY;		/* for AES, if necessary */
#endif
	wrmsr(SB_GLD_MSR_CTRL, msr);

	/* Disable interrupts */
	bus_write_4(sc->sc_sr, SB_AES_INT, SB_AI_CLEAR_INTR);

	/* Allocate a contiguous DMA-able buffer to work in */
	if (glxsb_dma_alloc(sc) != 0)
		goto fail0;

	/* Initialize our task queue */
	sc->sc_tq = taskqueue_create("glxsb_taskq", M_NOWAIT | M_ZERO,
	    taskqueue_thread_enqueue, &sc->sc_tq);
	if (sc->sc_tq == NULL) {
		device_printf(dev, "cannot create task queue\n");
		goto fail0;
	}
	if (taskqueue_start_threads(&sc->sc_tq, 1, PI_NET, "%s taskq",
	    device_get_nameunit(dev)) != 0) {
		device_printf(dev, "cannot start task queue\n");
		goto fail1;
	}
	TASK_INIT(&sc->sc_cryptotask, 0, glxsb_crypto_task, sc);

	/* Initialize crypto */
	if (glxsb_crypto_setup(sc) != 0)
		goto fail1;

	/* Install a periodic collector for the "true" (AMD's word) RNG */
	if (hz > 100)
		sc->sc_rnghz = hz / 100;
	else
		sc->sc_rnghz = 1;
	callout_init(&sc->sc_rngco, 1);
	glxsb_rnd(sc);

	return (0);

fail1:
	taskqueue_free(sc->sc_tq);
fail0:
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rid, sc->sc_sr);
	return (ENXIO);
}