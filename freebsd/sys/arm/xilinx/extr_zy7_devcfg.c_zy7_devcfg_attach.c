#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct zy7_devcfg_softc {TYPE_1__* sc_ctl_dev; int /*<<< orphan*/  intrhandle; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  actual_frequency; int /*<<< orphan*/  frequency; int /*<<< orphan*/  source; } ;
struct TYPE_3__ {struct zy7_devcfg_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCFG_SC_LOCK_INIT (struct zy7_devcfg_softc*) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int FCLK_NUM ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int RD4 (struct zy7_devcfg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  WR4 (struct zy7_devcfg_softc*,int /*<<< orphan*/ ,int) ; 
 int ZY7_DEVCFG_INT_ALL ; 
 int /*<<< orphan*/  ZY7_DEVCFG_INT_MASK ; 
 int /*<<< orphan*/  ZY7_DEVCFG_INT_STATUS ; 
 int /*<<< orphan*/  ZY7_DEVCFG_MCTRL ; 
 int ZY7_DEVCFG_MCTRL_PS_VERS_MASK ; 
 int ZY7_DEVCFG_MCTRL_PS_VERS_SHIFT ; 
 int /*<<< orphan*/  ZY7_DEVCFG_UNLOCK ; 
 int ZY7_DEVCFG_UNLOCK_MAGIC ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zy7_devcfg_softc*,int /*<<< orphan*/ *) ; 
 struct zy7_devcfg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* fclk_configs ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  zy7_devcfg_cdevsw ; 
 int /*<<< orphan*/  zy7_devcfg_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ zy7_devcfg_init_fclk_sysctl (struct zy7_devcfg_softc*) ; 
 int /*<<< orphan*/  zy7_devcfg_intr ; 
 struct zy7_devcfg_softc* zy7_devcfg_softc_p ; 
 scalar_t__ zy7_pl_fclk_enabled (int) ; 
 int /*<<< orphan*/  zy7_pl_fclk_get_freq (int) ; 
 int /*<<< orphan*/  zy7_pl_fclk_get_source (int) ; 
 int zy7_ps_vers ; 

__attribute__((used)) static int
zy7_devcfg_attach(device_t dev)
{
	struct zy7_devcfg_softc *sc = device_get_softc(dev);
	int i;
	int rid, err;

	/* Allow only one attach. */
	if (zy7_devcfg_softc_p != NULL)
		return (ENXIO);

	sc->dev = dev;

	DEVCFG_SC_LOCK_INIT(sc);

	/* Get memory resource. */
	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
					     RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "could not allocate memory resources.\n");
		zy7_devcfg_detach(dev);
		return (ENOMEM);
	}

	/* Allocate IRQ. */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
					     RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "cannot allocate IRQ\n");
		zy7_devcfg_detach(dev);
		return (ENOMEM);
	}

	/* Activate the interrupt. */
	err = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
			     NULL, zy7_devcfg_intr, sc, &sc->intrhandle);
	if (err) {
		device_printf(dev, "cannot setup IRQ\n");
		zy7_devcfg_detach(dev);
		return (err);
	}

	/* Create /dev/devcfg */
	sc->sc_ctl_dev = make_dev(&zy7_devcfg_cdevsw, 0,
			  UID_ROOT, GID_WHEEL, 0600, "devcfg");
	if (sc->sc_ctl_dev == NULL) {
		device_printf(dev, "failed to create /dev/devcfg");
		zy7_devcfg_detach(dev);
		return (ENXIO);
	}
	sc->sc_ctl_dev->si_drv1 = sc;

	zy7_devcfg_softc_p = sc;

	/* Unlock devcfg registers. */
	WR4(sc, ZY7_DEVCFG_UNLOCK, ZY7_DEVCFG_UNLOCK_MAGIC);

	/* Make sure interrupts are completely disabled. */
	WR4(sc, ZY7_DEVCFG_INT_STATUS, ZY7_DEVCFG_INT_ALL);
	WR4(sc, ZY7_DEVCFG_INT_MASK, 0xffffffff);

	/* Get PS_VERS for SYSCTL. */
	zy7_ps_vers = (RD4(sc, ZY7_DEVCFG_MCTRL) &
		       ZY7_DEVCFG_MCTRL_PS_VERS_MASK) >>
		ZY7_DEVCFG_MCTRL_PS_VERS_SHIFT;

	for (i = 0; i < FCLK_NUM; i++) {
		fclk_configs[i].source = zy7_pl_fclk_get_source(i);
		fclk_configs[i].actual_frequency = 
			zy7_pl_fclk_enabled(i) ? zy7_pl_fclk_get_freq(i) : 0;
		/* Initially assume actual frequency is the configure one */
		fclk_configs[i].frequency = fclk_configs[i].actual_frequency;
	}

	if (zy7_devcfg_init_fclk_sysctl(sc) < 0)
		device_printf(dev, "failed to initialized sysctl tree\n");

	return (0);
}