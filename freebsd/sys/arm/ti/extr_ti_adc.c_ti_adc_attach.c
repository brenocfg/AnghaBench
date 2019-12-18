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
typedef  int uint32_t ;
struct ti_adc_softc {int sc_tsc_wires; int sc_coord_readouts; int sc_adc_nchannels; int* sc_adc_channels; int sc_x; int sc_y; scalar_t__ sc_pen_down; int /*<<< orphan*/  sc_evdev; void* sc_mem_res; void* sc_irq_res; int /*<<< orphan*/  sc_intrhand; int /*<<< orphan*/  sc_dev; void* sc_charge_delay; void* sc_x_plate_resistance; } ;
typedef  scalar_t__ phandle_t ;
typedef  void* pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ADC_CLKDIV ; 
 int /*<<< orphan*/  ADC_CTRL ; 
 int ADC_CTRL_STEP_ID ; 
 int ADC_CTRL_STEP_WP ; 
 int /*<<< orphan*/  ADC_MAX_VALUE ; 
 int ADC_READ4 (struct ti_adc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_REVISION ; 
 int ADC_REV_CUSTOM_MSK ; 
 int ADC_REV_CUSTOM_SHIFT ; 
 int ADC_REV_FUNC_MSK ; 
 int ADC_REV_FUNC_SHIFT ; 
 int ADC_REV_MAJOR_MSK ; 
 int ADC_REV_MAJOR_SHIFT ; 
 int ADC_REV_MINOR_MSK ; 
 int ADC_REV_RTL_MSK ; 
 int ADC_REV_RTL_SHIFT ; 
 int ADC_REV_SCHEME_MSK ; 
 int ADC_REV_SCHEME_SHIFT ; 
 int /*<<< orphan*/  ADC_WRITE4 (struct ti_adc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  BUS_VIRTUAL ; 
 void* DEFAULT_CHARGE_DELAY ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  EV_ABS ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  INPUT_PROP_DIRECT ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,void**,int) ; 
 void* OF_getencprop_alloc_multi (scalar_t__,char*,int,void**) ; 
 scalar_t__ OF_hasprop (scalar_t__,char*) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_ADC_LOCK (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  TI_ADC_LOCK_INIT (struct ti_adc_softc*) ; 
 int TI_ADC_NPINS ; 
 int /*<<< orphan*/  TI_ADC_UNLOCK (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  TSC_ADC_CLK ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ti_adc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ti_adc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  evdev_alloc () ; 
 int evdev_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_set_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int ti_adc_config_wires (struct ti_adc_softc*,int*,int) ; 
 int /*<<< orphan*/  ti_adc_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_adc_idlestep_init (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  ti_adc_inputs_init (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  ti_adc_intr ; 
 int /*<<< orphan*/  ti_adc_setup (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  ti_adc_sysctl_init (struct ti_adc_softc*) ; 
 int /*<<< orphan*/  ti_adc_tsc_init (struct ti_adc_softc*) ; 
 int ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_adc_attach(device_t dev)
{
	int err, rid, i;
	struct ti_adc_softc *sc;
	uint32_t rev, reg;
	phandle_t node, child;
	pcell_t cell;
	int *channels;
	int nwire_configs;
	int *wire_configs;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	node = ofw_bus_get_node(dev);

	sc->sc_tsc_wires = 0;
	sc->sc_coord_readouts = 1;
	sc->sc_x_plate_resistance = 0;
	sc->sc_charge_delay = DEFAULT_CHARGE_DELAY;
	/* Read "tsc" node properties */
	child = ofw_bus_find_child(node, "tsc");
	if (child != 0 && OF_hasprop(child, "ti,wires")) {
		if ((OF_getencprop(child, "ti,wires", &cell, sizeof(cell))) > 0)
			sc->sc_tsc_wires = cell;
		if ((OF_getencprop(child, "ti,coordinate-readouts", &cell,
		    sizeof(cell))) > 0)
			sc->sc_coord_readouts = cell;
		if ((OF_getencprop(child, "ti,x-plate-resistance", &cell,
		    sizeof(cell))) > 0)
			sc->sc_x_plate_resistance = cell;
		if ((OF_getencprop(child, "ti,charge-delay", &cell,
		    sizeof(cell))) > 0)
			sc->sc_charge_delay = cell;
		nwire_configs = OF_getencprop_alloc_multi(child,
		    "ti,wire-config", sizeof(*wire_configs),
		    (void **)&wire_configs);
		if (nwire_configs != sc->sc_tsc_wires) {
			device_printf(sc->sc_dev,
			    "invalid number of ti,wire-config: %d (should be %d)\n",
			    nwire_configs, sc->sc_tsc_wires);
			OF_prop_free(wire_configs);
			return (EINVAL);
		}
		err = ti_adc_config_wires(sc, wire_configs, nwire_configs);
		OF_prop_free(wire_configs);
		if (err)
			return (EINVAL);
	}

	/* Read "adc" node properties */
	child = ofw_bus_find_child(node, "adc");
	if (child != 0) {
		sc->sc_adc_nchannels = OF_getencprop_alloc_multi(child,
		    "ti,adc-channels", sizeof(*channels), (void **)&channels);
		if (sc->sc_adc_nchannels > 0) {
			for (i = 0; i < sc->sc_adc_nchannels; i++)
				sc->sc_adc_channels[i] = channels[i];
			OF_prop_free(channels);
		}
	}

	/* Sanity check FDT data */
	if (sc->sc_tsc_wires + sc->sc_adc_nchannels > TI_ADC_NPINS) {
		device_printf(dev, "total number of chanels (%d) is larger than %d\n",
		    sc->sc_tsc_wires + sc->sc_adc_nchannels, TI_ADC_NPINS);
		return (ENXIO);
	}

	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->sc_mem_res) {
		device_printf(dev, "cannot allocate memory window\n");
		return (ENXIO);
	}

	/* Activate the ADC_TSC module. */
	err = ti_prcm_clk_enable(TSC_ADC_CLK);
	if (err)
		return (err);

	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (!sc->sc_irq_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		device_printf(dev, "cannot allocate interrupt\n");
		return (ENXIO);
	}

	if (bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, ti_adc_intr, sc, &sc->sc_intrhand) != 0) {
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq_res);
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->sc_mem_res);
		device_printf(dev, "Unable to setup the irq handler.\n");
		return (ENXIO);
	}

	/* Check the ADC revision. */
	rev = ADC_READ4(sc, ADC_REVISION);
	device_printf(dev,
	    "scheme: %#x func: %#x rtl: %d rev: %d.%d custom rev: %d\n",
	    (rev & ADC_REV_SCHEME_MSK) >> ADC_REV_SCHEME_SHIFT,
	    (rev & ADC_REV_FUNC_MSK) >> ADC_REV_FUNC_SHIFT,
	    (rev & ADC_REV_RTL_MSK) >> ADC_REV_RTL_SHIFT,
	    (rev & ADC_REV_MAJOR_MSK) >> ADC_REV_MAJOR_SHIFT,
	    rev & ADC_REV_MINOR_MSK,
	    (rev & ADC_REV_CUSTOM_MSK) >> ADC_REV_CUSTOM_SHIFT);

	reg = ADC_READ4(sc, ADC_CTRL);
	ADC_WRITE4(sc, ADC_CTRL, reg | ADC_CTRL_STEP_WP | ADC_CTRL_STEP_ID);

	/*
	 * Set the ADC prescaler to 2400 if touchscreen is not enabled
	 * and to 24 if it is.  This sets the ADC clock to ~10Khz and
	 * ~1Mhz respectively (CLK_M_OSC / prescaler).
	 */
	if (sc->sc_tsc_wires)
		ADC_WRITE4(sc, ADC_CLKDIV, 24 - 1);
	else
		ADC_WRITE4(sc, ADC_CLKDIV, 2400 - 1);

	TI_ADC_LOCK_INIT(sc);

	ti_adc_idlestep_init(sc);
	ti_adc_inputs_init(sc);
	ti_adc_sysctl_init(sc);
	ti_adc_tsc_init(sc);

	TI_ADC_LOCK(sc);
	ti_adc_setup(sc);
	TI_ADC_UNLOCK(sc);

#ifdef EVDEV_SUPPORT
	if (sc->sc_tsc_wires > 0) {
		sc->sc_evdev = evdev_alloc();
		evdev_set_name(sc->sc_evdev, device_get_desc(dev));
		evdev_set_phys(sc->sc_evdev, device_get_nameunit(dev));
		evdev_set_id(sc->sc_evdev, BUS_VIRTUAL, 0, 0, 0);
		evdev_support_prop(sc->sc_evdev, INPUT_PROP_DIRECT);
		evdev_support_event(sc->sc_evdev, EV_SYN);
		evdev_support_event(sc->sc_evdev, EV_ABS);
		evdev_support_event(sc->sc_evdev, EV_KEY);

		evdev_support_abs(sc->sc_evdev, ABS_X, 0, 0,
		    ADC_MAX_VALUE, 0, 0, 0);
		evdev_support_abs(sc->sc_evdev, ABS_Y, 0, 0,
		    ADC_MAX_VALUE, 0, 0, 0);

		evdev_support_key(sc->sc_evdev, BTN_TOUCH);

		err = evdev_register(sc->sc_evdev);
		if (err) {
			device_printf(dev,
			    "failed to register evdev: error=%d\n", err);
			ti_adc_detach(dev);
			return (err);
		}

		sc->sc_pen_down = 0;
		sc->sc_x = -1;
		sc->sc_y = -1;
	}
#endif /* EVDEV */

	return (0);
}