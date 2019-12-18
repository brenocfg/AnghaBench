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
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;
struct dwmmc_softc {int max_hz; int fifo_depth; int num_slots; scalar_t__ bus_hz; int /*<<< orphan*/  dev; int /*<<< orphan*/ * hwreset; scalar_t__ ciu; scalar_t__ biu; int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; TYPE_1__ host; } ;
typedef  int phandle_t ;
typedef  int pcell_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  MMC_CAP_4_BIT_DATA ; 
 int /*<<< orphan*/  MMC_CAP_8_BIT_DATA ; 
 scalar_t__ OF_getencprop (int,char*,int*,int) ; 
 int OF_getproplen (int,char*) ; 
 int clk_enable (scalar_t__) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  clk_get_freq (scalar_t__,scalar_t__*) ; 
 int clk_set_freq (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hwreset_assert (int /*<<< orphan*/ *) ; 
 int hwreset_deassert (int /*<<< orphan*/ *) ; 
 int hwreset_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parse_fdt(struct dwmmc_softc *sc)
{
	pcell_t dts_value[3];
	phandle_t node;
	uint32_t bus_hz = 0, bus_width;
	int len;
#ifdef EXT_RESOURCES
	int error;
#endif

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (ENXIO);

	/* bus-width */
	if (OF_getencprop(node, "bus-width", &bus_width, sizeof(uint32_t)) <= 0)
		bus_width = 4;
	if (bus_width >= 4)
		sc->host.caps |= MMC_CAP_4_BIT_DATA;
	if (bus_width >= 8)
		sc->host.caps |= MMC_CAP_8_BIT_DATA;

	/* max-frequency */
	if (OF_getencprop(node, "max-frequency", &sc->max_hz, sizeof(uint32_t)) <= 0)
		sc->max_hz = 200000000;

	/* fifo-depth */
	if ((len = OF_getproplen(node, "fifo-depth")) > 0) {
		OF_getencprop(node, "fifo-depth", dts_value, len);
		sc->fifo_depth = dts_value[0];
	}

	/* num-slots (Deprecated) */
	sc->num_slots = 1;
	if ((len = OF_getproplen(node, "num-slots")) > 0) {
		device_printf(sc->dev, "num-slots property is deprecated\n");
		OF_getencprop(node, "num-slots", dts_value, len);
		sc->num_slots = dts_value[0];
	}

	/* clock-frequency */
	if ((len = OF_getproplen(node, "clock-frequency")) > 0) {
		OF_getencprop(node, "clock-frequency", dts_value, len);
		bus_hz = dts_value[0];
	}

#ifdef EXT_RESOURCES

	/* IP block reset is optional */
	error = hwreset_get_by_ofw_name(sc->dev, 0, "reset", &sc->hwreset);
	if (error != 0 &&
	    error != ENOENT &&
	    error != ENODEV) {
		device_printf(sc->dev, "Cannot get reset\n");
		goto fail;
	}

	/* vmmc regulator is optional */
	error = regulator_get_by_ofw_property(sc->dev, 0, "vmmc-supply",
	     &sc->vmmc);
	if (error != 0 &&
	    error != ENOENT &&
	    error != ENODEV) {
		device_printf(sc->dev, "Cannot get regulator 'vmmc-supply'\n");
		goto fail;
	}

	/* vqmmc regulator is optional */
	error = regulator_get_by_ofw_property(sc->dev, 0, "vqmmc-supply",
	     &sc->vqmmc);
	if (error != 0 &&
	    error != ENOENT &&
	    error != ENODEV) {
		device_printf(sc->dev, "Cannot get regulator 'vqmmc-supply'\n");
		goto fail;
	}

	/* Assert reset first */
	if (sc->hwreset != NULL) {
		error = hwreset_assert(sc->hwreset);
		if (error != 0) {
			device_printf(sc->dev, "Cannot assert reset\n");
			goto fail;
		}
	}

	/* BIU (Bus Interface Unit clock) is optional */
	error = clk_get_by_ofw_name(sc->dev, 0, "biu", &sc->biu);
	if (error != 0 &&
	    error != ENOENT &&
	    error != ENODEV) {
		device_printf(sc->dev, "Cannot get 'biu' clock\n");
		goto fail;
	}

	if (sc->biu) {
		error = clk_enable(sc->biu);
		if (error != 0) {
			device_printf(sc->dev, "cannot enable biu clock\n");
			goto fail;
		}
	}

	/*
	 * CIU (Controller Interface Unit clock) is mandatory
	 * if no clock-frequency property is given
	 */
	error = clk_get_by_ofw_name(sc->dev, 0, "ciu", &sc->ciu);
	if (error != 0 &&
	    error != ENOENT &&
	    error != ENODEV) {
		device_printf(sc->dev, "Cannot get 'ciu' clock\n");
		goto fail;
	}

	if (sc->ciu) {
		if (bus_hz != 0) {
			error = clk_set_freq(sc->ciu, bus_hz, 0);
			if (error != 0)
				device_printf(sc->dev,
				    "cannot set ciu clock to %u\n", bus_hz);
		}
		error = clk_enable(sc->ciu);
		if (error != 0) {
			device_printf(sc->dev, "cannot enable ciu clock\n");
			goto fail;
		}
		clk_get_freq(sc->ciu, &sc->bus_hz);
	}

	/* Take dwmmc out of reset */
	if (sc->hwreset != NULL) {
		error = hwreset_deassert(sc->hwreset);
		if (error != 0) {
			device_printf(sc->dev, "Cannot deassert reset\n");
			goto fail;
		}
	}
#endif /* EXT_RESOURCES */

	if (sc->bus_hz == 0) {
		device_printf(sc->dev, "No bus speed provided\n");
		goto fail;
	}

	return (0);

fail:
	return (ENXIO);
}