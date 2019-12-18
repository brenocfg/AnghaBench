#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int host_ocr; int caps; void* f_max; void* f_min; } ;
struct TYPE_4__ {int pol; int /*<<< orphan*/ * dev; scalar_t__ pin; } ;
struct TYPE_6__ {scalar_t__ pin; int /*<<< orphan*/ * dev; scalar_t__ pol; } ;
struct aml8726_mmc_softc {scalar_t__ ref_freq; int* voltages; int /*<<< orphan*/ * res; scalar_t__ dmatag; scalar_t__ dmamap; scalar_t__ ih_cookie; TYPE_2__ host; int /*<<< orphan*/  mtx; int /*<<< orphan*/  ch; TYPE_1__ vselect; TYPE_3__ pwr_en; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_MMC_ALIGN_DMA ; 
 int /*<<< orphan*/  AML_MMC_LOCK_DESTROY (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  AML_MMC_LOCK_INIT (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  AML_MMC_MAX_DMA ; 
 int /*<<< orphan*/  AML_MMC_MULT_CONFIG_PORT_A ; 
 int /*<<< orphan*/  AML_MMC_MULT_CONFIG_PORT_B ; 
 int /*<<< orphan*/  AML_MMC_MULT_CONFIG_PORT_C ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CALLOUT_RETURNUNLOCKED ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 scalar_t__ GPIO_PIN_SET (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_HSPEED ; 
 int MMC_OCR_320_330 ; 
 int MMC_OCR_330_340 ; 
 int MMC_OCR_LOW_VOLTAGE ; 
 void* OF_device_from_xref (scalar_t__) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_node_from_xref (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 scalar_t__ aml8726_mmc_clk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_mmc_div (struct aml8726_mmc_softc*,int) ; 
 void* aml8726_mmc_freq (struct aml8726_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_mmc_intr ; 
 scalar_t__ aml8726_mmc_power_off (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  aml8726_mmc_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int bus_dmamap_create (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aml8726_mmc_softc*,scalar_t__*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct aml8726_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
aml8726_mmc_attach(device_t dev)
{
	struct aml8726_mmc_softc *sc = device_get_softc(dev);
	char *function_name;
	char *voltages;
	char *voltage;
	int error;
	int nvoltages;
	pcell_t prop[3];
	phandle_t node;
	ssize_t len;
	device_t child;

	sc->dev = dev;

	node = ofw_bus_get_node(dev);

	sc->ref_freq = aml8726_mmc_clk(node);

	if (sc->ref_freq == 0) {
		device_printf(dev, "missing clocks attribute in FDT\n");
		return (ENXIO);
	}

	/*
	 * The pins must be specified as part of the device in order
	 * to know which port to used.
	 */

	len = OF_getencprop(node, "pinctrl-0", prop, sizeof(prop));

	if ((len / sizeof(prop[0])) != 1 || prop[0] == 0) {
		device_printf(dev, "missing pinctrl-0 attribute in FDT\n");
		return (ENXIO);
	}

	len = OF_getprop_alloc(OF_node_from_xref(prop[0]), "amlogic,function",
	    (void **)&function_name);

	if (len < 0) {
		device_printf(dev,
		    "missing amlogic,function attribute in FDT\n");
		return (ENXIO);
	}

	if (strncmp("sdio-a", function_name, len) == 0)
		sc->port = AML_MMC_MULT_CONFIG_PORT_A;
	else if (strncmp("sdio-b", function_name, len) == 0)
		sc->port = AML_MMC_MULT_CONFIG_PORT_B;
	else if (strncmp("sdio-c", function_name, len) == 0)
		sc->port = AML_MMC_MULT_CONFIG_PORT_C;
	else {
		device_printf(dev, "unknown function attribute %.*s in FDT\n",
		    len, function_name);
		OF_prop_free(function_name);
		return (ENXIO);
	}

	OF_prop_free(function_name);

	sc->pwr_en.dev = NULL;

	len = OF_getencprop(node, "mmc-pwr-en", prop, sizeof(prop));
	if (len > 0) {
		if ((len / sizeof(prop[0])) == 3) {
			sc->pwr_en.dev = OF_device_from_xref(prop[0]);
			sc->pwr_en.pin = prop[1];
			sc->pwr_en.pol = prop[2];
		}

		if (sc->pwr_en.dev == NULL) {
			device_printf(dev,
			    "unable to process mmc-pwr-en attribute in FDT\n");
			return (ENXIO);
		}

		/* Turn off power and then configure the output driver. */
		if (aml8726_mmc_power_off(sc) != 0 ||
		    GPIO_PIN_SETFLAGS(sc->pwr_en.dev, sc->pwr_en.pin,
		    GPIO_PIN_OUTPUT) != 0) {
			device_printf(dev,
			    "could not use gpio to control power\n");
			return (ENXIO);
		}
	}

	len = OF_getprop_alloc(node, "mmc-voltages",
	    (void **)&voltages);

	if (len < 0) {
		device_printf(dev, "missing mmc-voltages attribute in FDT\n");
		return (ENXIO);
	}

	sc->voltages[0] = 0;
	sc->voltages[1] = 0;

	voltage = voltages;
	nvoltages = 0;

	while (len && nvoltages < 2) {
		if (strncmp("1.8", voltage, len) == 0)
			sc->voltages[nvoltages] = MMC_OCR_LOW_VOLTAGE;
		else if (strncmp("3.3", voltage, len) == 0)
			sc->voltages[nvoltages] = MMC_OCR_320_330 |
			    MMC_OCR_330_340;
		else {
			device_printf(dev,
			    "unknown voltage attribute %.*s in FDT\n",
			    len, voltage);
			OF_prop_free(voltages);
			return (ENXIO);
		}

		nvoltages++;

		/* queue up next string */
		while (*voltage && len) {
			voltage++;
			len--;
		}
		if (len) {
			voltage++;
			len--;
		}
	}

	OF_prop_free(voltages);

	sc->vselect.dev = NULL;

	len = OF_getencprop(node, "mmc-vselect", prop, sizeof(prop));
	if (len > 0) {
		if ((len / sizeof(prop[0])) == 2) {
			sc->vselect.dev = OF_device_from_xref(prop[0]);
			sc->vselect.pin = prop[1];
			sc->vselect.pol = 1;
		}

		if (sc->vselect.dev == NULL) {
			device_printf(dev,
			  "unable to process mmc-vselect attribute in FDT\n");
			return (ENXIO);
		}

		/*
		 * With the power off select voltage 0 and then
		 * configure the output driver.
		 */
		if (GPIO_PIN_SET(sc->vselect.dev, sc->vselect.pin, 0) != 0 ||
		    GPIO_PIN_SETFLAGS(sc->vselect.dev, sc->vselect.pin,
		    GPIO_PIN_OUTPUT) != 0) {
			device_printf(dev,
			    "could not use gpio to set voltage\n");
			return (ENXIO);
		}
	}

	if (nvoltages == 0) {
		device_printf(dev, "no voltages in FDT\n");
		return (ENXIO);
	} else if (nvoltages == 1 && sc->vselect.dev != NULL) {
		device_printf(dev, "only one voltage in FDT\n");
		return (ENXIO);
	} else if (nvoltages == 2 && sc->vselect.dev == NULL) {
		device_printf(dev, "too many voltages in FDT\n");
		return (ENXIO);
	}

	if (bus_alloc_resources(dev, aml8726_mmc_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	AML_MMC_LOCK_INIT(sc);

	error = bus_dma_tag_create(bus_get_dma_tag(dev), AML_MMC_ALIGN_DMA, 0,
	    BUS_SPACE_MAXADDR_32BIT, BUS_SPACE_MAXADDR, NULL, NULL,
	    AML_MMC_MAX_DMA, 1, AML_MMC_MAX_DMA, 0, NULL, NULL, &sc->dmatag);
	if (error)
		goto fail;

	error = bus_dmamap_create(sc->dmatag, 0, &sc->dmamap);

	if (error)
		goto fail;

	error = bus_setup_intr(dev, sc->res[1], INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, aml8726_mmc_intr, sc, &sc->ih_cookie);
	if (error) {
		device_printf(dev, "could not setup interrupt handler\n");
		goto fail;
	}

	callout_init_mtx(&sc->ch, &sc->mtx, CALLOUT_RETURNUNLOCKED);

	sc->host.f_min = aml8726_mmc_freq(sc, aml8726_mmc_div(sc, 200000));
	sc->host.f_max = aml8726_mmc_freq(sc, aml8726_mmc_div(sc, 50000000));
	sc->host.host_ocr = sc->voltages[0] | sc->voltages[1];
	sc->host.caps = MMC_CAP_4_BIT_DATA | MMC_CAP_HSPEED;

	child = device_add_child(dev, "mmc", -1);

	if (!child) {
		device_printf(dev, "could not add mmc\n");
		error = ENXIO;
		goto fail;
	}

	error = device_probe_and_attach(child);

	if (error) {
		device_printf(dev, "could not attach mmc\n");
		goto fail;
	}

	return (0);

fail:
	if (sc->ih_cookie)
		bus_teardown_intr(dev, sc->res[1], sc->ih_cookie);

	if (sc->dmamap)
		bus_dmamap_destroy(sc->dmatag, sc->dmamap);

	if (sc->dmatag)
		bus_dma_tag_destroy(sc->dmatag);

	AML_MMC_LOCK_DESTROY(sc);

	aml8726_mmc_power_off(sc);

	bus_release_resources(dev, aml8726_mmc_spec, sc->res);

	return (error);
}