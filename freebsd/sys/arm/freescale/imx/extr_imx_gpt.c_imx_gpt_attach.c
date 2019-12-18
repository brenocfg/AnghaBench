#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_5__ {char* et_name; int et_flags; int et_quality; int et_frequency; int et_min_period; int et_max_period; struct imx_gpt_softc* et_priv; int /*<<< orphan*/  et_stop; int /*<<< orphan*/  et_start; } ;
struct imx_gpt_softc {int sc_clksrc; int clkfreq; TYPE_3__ et; int /*<<< orphan*/ * res; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_ioh; int /*<<< orphan*/  sc_iot; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int tc_frequency; struct imx_gpt_softc* tc_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int ET_FLAGS_ONESHOT ; 
 int ET_FLAGS_PERIODIC ; 
 int GPT_CR_24MEN ; 
#define  GPT_CR_CLKSRC_24M 133 
#define  GPT_CR_CLKSRC_32K 132 
#define  GPT_CR_CLKSRC_EXT 131 
#define  GPT_CR_CLKSRC_IPG 130 
#define  GPT_CR_CLKSRC_IPG_HIGH 129 
#define  GPT_CR_CLKSRC_NONE 128 
 int GPT_CR_DBGEN ; 
 int GPT_CR_DOZEEN ; 
 int GPT_CR_EN ; 
 int GPT_CR_FRR ; 
 int GPT_CR_STOPEN ; 
 int GPT_CR_SWR ; 
 int GPT_CR_WAITEN ; 
 int GPT_IR_ALL ; 
 int /*<<< orphan*/  IMX_GPT_CNT ; 
 int /*<<< orphan*/  IMX_GPT_CR ; 
 int /*<<< orphan*/  IMX_GPT_IR ; 
 int /*<<< orphan*/  IMX_GPT_OCR3 ; 
 int /*<<< orphan*/  IMX_GPT_PR ; 
 int /*<<< orphan*/  IMX_GPT_SR ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int READ4 (struct imx_gpt_softc*,int /*<<< orphan*/ ) ; 
 int TARGET_FREQUENCY ; 
 int /*<<< orphan*/  WRITE4 (struct imx_gpt_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arm_set_delay (int /*<<< orphan*/ ,struct imx_gpt_softc*) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct imx_gpt_softc*,int /*<<< orphan*/ *) ; 
 struct imx_gpt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  et_register (TYPE_3__*) ; 
 int imx_ccm_ipg_hz () ; 
 int /*<<< orphan*/  imx_gpt_do_delay ; 
 int /*<<< orphan*/  imx_gpt_intr ; 
 int /*<<< orphan*/  imx_gpt_spec ; 
 TYPE_1__ imx_gpt_timecounter ; 
 int /*<<< orphan*/  imx_gpt_timer_start ; 
 int /*<<< orphan*/  imx_gpt_timer_stop ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_init (TYPE_1__*) ; 

__attribute__((used)) static int
imx_gpt_attach(device_t dev)
{
	struct imx_gpt_softc *sc;
	int ctlreg, err;
	uint32_t basefreq, prescale, setup_ticks, t1, t2;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, imx_gpt_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->sc_dev = dev;
	sc->sc_iot = rman_get_bustag(sc->res[0]);
	sc->sc_ioh = rman_get_bushandle(sc->res[0]);

	/*
	 * For now, just automatically choose a good clock for the hardware
	 * we're running on.  Eventually we could allow selection from the fdt;
	 * the code in this driver will cope with any clock frequency.
	 */
	sc->sc_clksrc = GPT_CR_CLKSRC_IPG;

	ctlreg = 0;

	switch (sc->sc_clksrc) {
	case GPT_CR_CLKSRC_32K:
		basefreq = 32768;
		break;
	case GPT_CR_CLKSRC_IPG:
		basefreq = imx_ccm_ipg_hz();
		break;
	case GPT_CR_CLKSRC_IPG_HIGH:
		basefreq = imx_ccm_ipg_hz() * 2;
		break;
	case GPT_CR_CLKSRC_24M:
		ctlreg |= GPT_CR_24MEN;
		basefreq = 24000000;
		break;
	case GPT_CR_CLKSRC_NONE:/* Can't run without a clock. */
	case GPT_CR_CLKSRC_EXT:	/* No way to get the freq of an ext clock. */
	default:
		device_printf(dev, "Unsupported clock source '%d'\n", 
		    sc->sc_clksrc);
		return (EINVAL);
	}

	/*
	 * The following setup sequence is from the I.MX6 reference manual,
	 * "Selecting the clock source".  First, disable the clock and
	 * interrupts.  This also clears input and output mode bits and in
	 * general completes several of the early steps in the procedure.
	 */
	WRITE4(sc, IMX_GPT_CR, 0);
	WRITE4(sc, IMX_GPT_IR, 0);

	/* Choose the clock and the power-saving behaviors. */
	ctlreg |=
	    sc->sc_clksrc |	/* Use selected clock */
	    GPT_CR_FRR |	/* Just count (FreeRunner mode) */
	    GPT_CR_STOPEN |	/* Run in STOP mode */
	    GPT_CR_DOZEEN |	/* Run in DOZE mode */
	    GPT_CR_WAITEN |	/* Run in WAIT mode */
	    GPT_CR_DBGEN;	/* Run in DEBUG mode */
	WRITE4(sc, IMX_GPT_CR, ctlreg);

	/*
	 * The datasheet says to do the software reset after choosing the clock
	 * source.  It says nothing about needing to wait for the reset to
	 * complete, but the register description does document the fact that
	 * the reset isn't complete until the SWR bit reads 0, so let's be safe.
	 * The reset also clears all registers except for a few of the bits in
	 * CR, but we'll rewrite all the CR bits when we start the counter.
	 */
	WRITE4(sc, IMX_GPT_CR, ctlreg | GPT_CR_SWR);
	while (READ4(sc, IMX_GPT_CR) & GPT_CR_SWR)
		continue;

	/* Set a prescaler value that gets us near the target frequency. */
	if (basefreq < TARGET_FREQUENCY) {
		prescale = 0;
		sc->clkfreq = basefreq;
	} else {
		prescale = basefreq / TARGET_FREQUENCY;
		sc->clkfreq = basefreq / prescale;
		prescale -= 1; /* 1..n range is 0..n-1 in hardware. */
	}
	WRITE4(sc, IMX_GPT_PR, prescale);

	/* Clear the status register. */
	WRITE4(sc, IMX_GPT_SR, GPT_IR_ALL);

	/* Start the counter. */
	WRITE4(sc, IMX_GPT_CR, ctlreg | GPT_CR_EN);

	if (bootverbose)
		device_printf(dev, "Running on %dKHz clock, base freq %uHz CR=0x%08x, PR=0x%08x\n",
		    sc->clkfreq / 1000, basefreq, READ4(sc, IMX_GPT_CR), READ4(sc, IMX_GPT_PR));

	/* Setup the timer interrupt. */
	err = bus_setup_intr(dev, sc->res[1], INTR_TYPE_CLK, imx_gpt_intr,
	    NULL, sc, &sc->sc_ih);
	if (err != 0) {
		bus_release_resources(dev, imx_gpt_spec, sc->res);
		device_printf(dev, "Unable to setup the clock irq handler, "
		    "err = %d\n", err);
		return (ENXIO);
	}

	/*
	 * Measure how many clock ticks it takes to setup a one-shot event (it's
	 * longer than you might think, due to wait states in accessing gpt
	 * registers).  Scale up the result by a factor of 1.5 to be safe,
	 * and use that to set the minimum eventtimer period we can schedule. In
	 * the real world, the value works out to about 750ns on imx5 hardware.
	 */
	t1 = READ4(sc, IMX_GPT_CNT);
	WRITE4(sc, IMX_GPT_OCR3, 0);
	t2 = READ4(sc, IMX_GPT_CNT);
	setup_ticks = ((t2 - t1 + 1) * 3) / 2;

	/* Register as an eventtimer. */
	sc->et.et_name = "iMXGPT";
	sc->et.et_flags = ET_FLAGS_ONESHOT | ET_FLAGS_PERIODIC;
	sc->et.et_quality = 800;
	sc->et.et_frequency = sc->clkfreq;
	sc->et.et_min_period = ((uint64_t)setup_ticks << 32) / sc->clkfreq;
	sc->et.et_max_period = ((uint64_t)0xfffffffe  << 32) / sc->clkfreq;
	sc->et.et_start = imx_gpt_timer_start;
	sc->et.et_stop = imx_gpt_timer_stop;
	sc->et.et_priv = sc;
	et_register(&sc->et);

	/* Register as a timecounter. */
	imx_gpt_timecounter.tc_frequency = sc->clkfreq;
	imx_gpt_timecounter.tc_priv = sc;
	tc_init(&imx_gpt_timecounter);

	/* If this is the first unit, store the softc for use in DELAY. */
	if (device_get_unit(dev) == 0) {
		arm_set_delay(imx_gpt_do_delay, sc);
	}

	return (0);
}