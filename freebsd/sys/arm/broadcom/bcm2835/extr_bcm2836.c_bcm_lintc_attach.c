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
struct bcm_lintc_softc {int /*<<< orphan*/ * bls_mem; int /*<<< orphan*/  bls_bsh; int /*<<< orphan*/  bls_bst; int /*<<< orphan*/  bls_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_LINTC_CONTROL_REG ; 
 int /*<<< orphan*/  BCM_LINTC_LOCK_INIT (struct bcm_lintc_softc*) ; 
 int /*<<< orphan*/  BCM_LINTC_MBOX_CFG_REG (int) ; 
 int /*<<< orphan*/  BCM_LINTC_MCR_IRQ_EN_MBOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_LINTC_PRESCALER_REG ; 
 int /*<<< orphan*/  BCM_LINTC_PSR_19_2 ; 
 int /*<<< orphan*/  BCM_LINTC_TIMER_CFG_REG (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bcm_lintc_pic_attach (struct bcm_lintc_softc*) ; 
 struct bcm_lintc_softc* bcm_lintc_sc ; 
 int /*<<< orphan*/  bcm_lintc_write_4 (struct bcm_lintc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct bcm_lintc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bcm_lintc_attach(device_t dev)
{
	struct bcm_lintc_softc *sc;
	int cpu, rid;

	sc = device_get_softc(dev);

	sc->bls_dev = dev;
	if (bcm_lintc_sc != NULL)
		return (ENXIO);

	rid = 0;
	sc->bls_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->bls_mem == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	sc->bls_bst = rman_get_bustag(sc->bls_mem);
	sc->bls_bsh = rman_get_bushandle(sc->bls_mem);

	bcm_lintc_write_4(sc, BCM_LINTC_CONTROL_REG, 0);
	bcm_lintc_write_4(sc, BCM_LINTC_PRESCALER_REG, BCM_LINTC_PSR_19_2);

	/* Disable all timers on all cores. */
	for (cpu = 0; cpu < 4; cpu++)
		bcm_lintc_write_4(sc, BCM_LINTC_TIMER_CFG_REG(cpu), 0);

#ifdef SMP
	/* Enable mailbox 0 on all cores used for IPI. */
	for (cpu = 0; cpu < 4; cpu++)
		bcm_lintc_write_4(sc, BCM_LINTC_MBOX_CFG_REG(cpu),
		    BCM_LINTC_MCR_IRQ_EN_MBOX(0));
#endif

	if (bcm_lintc_pic_attach(sc) != 0) {
		device_printf(dev, "could not attach PIC\n");
		return (ENXIO);
	}

	BCM_LINTC_LOCK_INIT(sc);
	bcm_lintc_sc = sc;
	return (0);
}