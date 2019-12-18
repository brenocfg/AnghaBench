#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct aw_ir_softc {int fifo_size; int /*<<< orphan*/ * res; int /*<<< orphan*/ * sc_evdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  intrhand; } ;
typedef  int /*<<< orphan*/ * hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * clk_t ;
struct TYPE_2__ {int ocd_data; } ;

/* Variables and functions */
#define  A10_IR 129 
#define  A13_IR 128 
 int AW_IR_ACTIVE_T ; 
 int AW_IR_ACTIVE_T_C ; 
 int /*<<< orphan*/  AW_IR_BASE_CLK ; 
 int /*<<< orphan*/  AW_IR_CIR ; 
 int /*<<< orphan*/  AW_IR_CTL ; 
 int AW_IR_CTL_GEN ; 
 int AW_IR_CTL_MD ; 
 int AW_IR_CTL_RXEN ; 
 int /*<<< orphan*/  AW_IR_RXCTL ; 
 int AW_IR_RXCTL_RPPI ; 
 int AW_IR_RXFILT_VAL ; 
 int AW_IR_RXIDLE_VAL ; 
 int /*<<< orphan*/  AW_IR_RXINT ; 
 int AW_IR_RXINT_RAI_EN ; 
 int AW_IR_RXINT_RAL (int) ; 
 int AW_IR_RXINT_ROI_EN ; 
 int AW_IR_RXINT_RPEI_EN ; 
 int /*<<< orphan*/  AW_IR_RXSTA ; 
 int AW_IR_RXSTA_CLEARALL ; 
 int AW_IR_SAMPLE_128 ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  EV_SYN ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 int READ (struct aw_ir_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE (struct aw_ir_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aw_ir_buf_reset (struct aw_ir_softc*) ; 
 int /*<<< orphan*/  aw_ir_intr ; 
 int /*<<< orphan*/  aw_ir_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aw_ir_softc*,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ *) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int clk_set_freq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct aw_ir_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * evdev_alloc () ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ *) ; 
 int evdev_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evdev_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_phys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_msc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hwreset_deassert (int /*<<< orphan*/ *) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hwreset_release (int /*<<< orphan*/ *) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_ir_attach(device_t dev)
{
	struct aw_ir_softc *sc;
	hwreset_t rst_apb;
	clk_t clk_ir, clk_gate;
	int err;
	uint32_t val = 0;

	clk_ir = clk_gate = NULL;
	rst_apb = NULL;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, aw_ir_spec, sc->res) != 0) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	switch (ofw_bus_search_compatible(dev, compat_data)->ocd_data) {
	case A10_IR:
		sc->fifo_size = 16;
		break;
	case A13_IR:
		sc->fifo_size = 64;
		break;
	}

	/* De-assert reset */
	if (hwreset_get_by_ofw_idx(dev, 0, 0, &rst_apb) == 0) {
		err = hwreset_deassert(rst_apb);
		if (err != 0) {
			device_printf(dev, "cannot de-assert reset\n");
			goto error;
		}
	}

	/* Reset buffer */
	aw_ir_buf_reset(sc);

	/* Get clocks and enable them */
	err = clk_get_by_ofw_name(dev, 0, "apb", &clk_gate);
	if (err != 0) {
		device_printf(dev, "Cannot get gate clock\n");
		goto error;
	}
	err = clk_get_by_ofw_name(dev, 0, "ir", &clk_ir);
	if (err != 0) {
		device_printf(dev, "Cannot get IR clock\n");
		goto error;
	}
	/* Set clock rate */
	err = clk_set_freq(clk_ir, AW_IR_BASE_CLK, 0);
	if (err != 0) {
		device_printf(dev, "cannot set IR clock rate\n");
		goto error;
	}
	/* Enable clocks */
	err = clk_enable(clk_gate);
	if (err != 0) {
		device_printf(dev, "Cannot enable clk gate\n");
		goto error;
	}
	err = clk_enable(clk_ir);
	if (err != 0) {
		device_printf(dev, "Cannot enable IR clock\n");
		goto error;
	}

	if (bus_setup_intr(dev, sc->res[1],
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, aw_ir_intr, sc,
	    &sc->intrhand)) {
		bus_release_resources(dev, aw_ir_spec, sc->res);
		device_printf(dev, "cannot setup interrupt handler\n");
		return (ENXIO);
	}

	/* Enable CIR Mode */
	WRITE(sc, AW_IR_CTL, AW_IR_CTL_MD);

	/*
	 * Set clock sample, filter, idle thresholds.
	 * Frequency sample = 3MHz/128 = 23437.5Hz (42.7us)
	 */
	val = AW_IR_SAMPLE_128;
	val |= (AW_IR_RXFILT_VAL | AW_IR_RXIDLE_VAL);
	val |= (AW_IR_ACTIVE_T | AW_IR_ACTIVE_T_C);
	WRITE(sc, AW_IR_CIR, val);

	/* Invert Input Signal */
	WRITE(sc, AW_IR_RXCTL, AW_IR_RXCTL_RPPI);

	/* Clear All RX Interrupt Status */
	WRITE(sc, AW_IR_RXSTA, AW_IR_RXSTA_CLEARALL);

	/*
	 * Enable RX interrupt in case of overflow, packet end
	 * and FIFO available.
	 * RX FIFO Threshold = FIFO size / 2
	 */
	WRITE(sc, AW_IR_RXINT, AW_IR_RXINT_ROI_EN | AW_IR_RXINT_RPEI_EN |
	    AW_IR_RXINT_RAI_EN | AW_IR_RXINT_RAL((sc->fifo_size >> 1) - 1));

	/* Enable IR Module */
	val = READ(sc, AW_IR_CTL);
	WRITE(sc, AW_IR_CTL, val | AW_IR_CTL_GEN | AW_IR_CTL_RXEN);

	sc->sc_evdev = evdev_alloc();
	evdev_set_name(sc->sc_evdev, device_get_desc(sc->dev));
	evdev_set_phys(sc->sc_evdev, device_get_nameunit(sc->dev));
	evdev_set_id(sc->sc_evdev, BUS_HOST, 0, 0, 0);
	evdev_support_event(sc->sc_evdev, EV_SYN);
	evdev_support_event(sc->sc_evdev, EV_MSC);
	evdev_support_msc(sc->sc_evdev, MSC_SCAN);

	err = evdev_register(sc->sc_evdev);
	if (err) {
		device_printf(dev,
		    "failed to register evdev: error=%d\n", err);
		goto error;
	}

	return (0);
error:
	if (clk_gate != NULL)
		clk_release(clk_gate);
	if (clk_ir != NULL)
		clk_release(clk_ir);
	if (rst_apb != NULL)
		hwreset_release(rst_apb);
	evdev_free(sc->sc_evdev);
	sc->sc_evdev = NULL;	/* Avoid double free */

	bus_release_resources(dev, aw_ir_spec, sc->res);
	return (ENXIO);
}