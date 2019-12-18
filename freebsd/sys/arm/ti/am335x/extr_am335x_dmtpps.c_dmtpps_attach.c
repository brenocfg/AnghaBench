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
struct make_dev_args {int mda_mode; struct dmtpps_softc* mda_si_drv1; int /*<<< orphan*/  mda_unit; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_cr; int /*<<< orphan*/ * mda_devsw; int /*<<< orphan*/  mda_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver_mtx; int /*<<< orphan*/  driver_abi; int /*<<< orphan*/  ppscap; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {unsigned int tc_counter_mask; int tc_frequency; int tc_quality; struct dmtpps_softc* tc_priv; int /*<<< orphan*/  tc_get_timecount; int /*<<< orphan*/  tc_name; } ;
struct dmtpps_softc {int tmr_num; int tclr; int /*<<< orphan*/  tmr_name; int /*<<< orphan*/  dev; int /*<<< orphan*/  pps_cdev; TYPE_2__ pps_state; int /*<<< orphan*/  pps_mtx; TYPE_1__ tc; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_ident_t ;

/* Variables and functions */
 int DMTIMER_READ4 (struct dmtpps_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMTIMER_WRITE4 (struct dmtpps_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMT_TCLR ; 
 int DMT_TCLR_AUTOLOAD ; 
 int DMT_TCLR_GPO_CFG ; 
 int DMT_TCLR_START ; 
 int /*<<< orphan*/  DMT_TCRR ; 
 int /*<<< orphan*/  DMT_TIOCP_CFG ; 
 int DMT_TIOCP_RESET ; 
 int /*<<< orphan*/  DMT_TLDR ; 
 int /*<<< orphan*/  DMT_TSICR ; 
 int DMT_TSICR_RESET ; 
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  INVALID_CLK_IDENT ; 
 int /*<<< orphan*/  MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  PPSFLAG_MTX_SPIN ; 
 int /*<<< orphan*/  PPS_ABI_VERSION ; 
 int /*<<< orphan*/  PPS_CAPTUREASSERT ; 
 int /*<<< orphan*/  PPS_CDEV_NAME ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYSCLK_CLK ; 
 int /*<<< orphan*/  SYS_CLK ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dmtpps_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dmtpps_cdevsw ; 
 int /*<<< orphan*/  dmtpps_get_timecount ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pps_init_abi (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  tc_init (TYPE_1__*) ; 
 int /*<<< orphan*/  ti_hwmods_get_clock (int /*<<< orphan*/ ) ; 
 int ti_hwmods_get_unit (int /*<<< orphan*/ ,char*) ; 
 int ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 
 int ti_prcm_clk_get_source_freq (int /*<<< orphan*/ ,int*) ; 
 int ti_prcm_clk_set_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmtpps_attach(device_t dev)
{
	struct dmtpps_softc *sc;
	struct make_dev_args mda;
	clk_ident_t timer_id;
	int err, sysclk_freq;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Get the base clock frequency. */
	err = ti_prcm_clk_get_source_freq(SYS_CLK, &sysclk_freq);

	/* Enable clocks and power on the device. */
	if ((timer_id = ti_hwmods_get_clock(dev)) == INVALID_CLK_IDENT)
		return (ENXIO);
	if ((err = ti_prcm_clk_set_source(timer_id, SYSCLK_CLK)) != 0)
		return (err);
	if ((err = ti_prcm_clk_enable(timer_id)) != 0)
		return (err);

	/* Request the memory resources. */
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->mem_rid, RF_ACTIVE);
	if (sc->mem_res == NULL) {
		return (ENXIO);
	}

	/* Figure out which hardware timer this is and set the name string. */
	sc->tmr_num = ti_hwmods_get_unit(dev, "timer");
	snprintf(sc->tmr_name, sizeof(sc->tmr_name), "DMTimer%d", sc->tmr_num);

	/*
	 * Configure the timer pulse/capture pin to input/capture mode.  This is
	 * required in addition to configuring the pin as input with the pinmux
	 * controller (which was done via fdt data or tunable at probe time).
	 */
	sc->tclr = DMT_TCLR_GPO_CFG;
	DMTIMER_WRITE4(sc, DMT_TCLR, sc->tclr);

	/* Set up timecounter hardware, start it. */
	DMTIMER_WRITE4(sc, DMT_TSICR, DMT_TSICR_RESET);
	while (DMTIMER_READ4(sc, DMT_TIOCP_CFG) & DMT_TIOCP_RESET)
		continue;

	sc->tclr |= DMT_TCLR_START | DMT_TCLR_AUTOLOAD;
	DMTIMER_WRITE4(sc, DMT_TLDR, 0);
	DMTIMER_WRITE4(sc, DMT_TCRR, 0);
	DMTIMER_WRITE4(sc, DMT_TCLR, sc->tclr);

	/* Register the timecounter. */
	sc->tc.tc_name           = sc->tmr_name;
	sc->tc.tc_get_timecount  = dmtpps_get_timecount;
	sc->tc.tc_counter_mask   = ~0u;
	sc->tc.tc_frequency      = sysclk_freq;
	sc->tc.tc_quality        = 1000;
	sc->tc.tc_priv           = sc;

	tc_init(&sc->tc);

	/*
	 * Indicate our PPS capabilities.  Have the kernel init its part of the
	 * pps_state struct and add its capabilities.
	 *
	 * While the hardware has a mode to capture each edge, it's not clear we
	 * can use it that way, because there's only a single interrupt/status
	 * bit to say something was captured, but not which edge it was.  For
	 * now, just say we can only capture assert events (the positive-going
	 * edge of the pulse).
	 */
	mtx_init(&sc->pps_mtx, "dmtpps", NULL, MTX_SPIN);
	sc->pps_state.flags = PPSFLAG_MTX_SPIN;
	sc->pps_state.ppscap = PPS_CAPTUREASSERT;
	sc->pps_state.driver_abi = PPS_ABI_VERSION;
	sc->pps_state.driver_mtx = &sc->pps_mtx;
	pps_init_abi(&sc->pps_state);

	/* Create the PPS cdev. */
	make_dev_args_init(&mda);
	mda.mda_flags = MAKEDEV_WAITOK;
	mda.mda_devsw = &dmtpps_cdevsw;
	mda.mda_cr = NULL;
	mda.mda_uid = UID_ROOT;
	mda.mda_gid = GID_WHEEL;
	mda.mda_mode = 0600;
	mda.mda_unit = device_get_unit(dev);
	mda.mda_si_drv1 = sc;
	if ((err = make_dev_s(&mda, &sc->pps_cdev, PPS_CDEV_NAME)) != 0) {
		device_printf(dev, "Failed to create cdev %s\n", PPS_CDEV_NAME);
		return (err);
	}

	if (bootverbose)
		device_printf(sc->dev, "Using %s for PPS device /dev/%s\n",
		    sc->tmr_name, PPS_CDEV_NAME);

	return (0);
}