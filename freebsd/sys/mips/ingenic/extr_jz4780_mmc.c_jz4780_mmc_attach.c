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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_2__ {int f_max; int f_min; int host_ocr; int caps; int /*<<< orphan*/  mode; } ;
struct jz4780_mmc_softc {int sc_timeout; int /*<<< orphan*/ * sc_clk; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_intrhand; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_timeoutc; TYPE_1__ sc_host; int /*<<< orphan*/ * sc_dev; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; int /*<<< orphan*/ * sc_req; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 size_t JZ_MSC_IRQRES ; 
 size_t JZ_MSC_MEMRES ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_HSPEED ; 
 int MMC_OCR_320_330 ; 
 int MMC_OCR_330_340 ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct jz4780_mmc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct jz4780_mmc_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ jz4780_mmc_enable_clock (struct jz4780_mmc_softc*) ; 
 int /*<<< orphan*/  jz4780_mmc_intr ; 
 int jz4780_mmc_pio_mode ; 
 int /*<<< orphan*/  jz4780_mmc_res_spec ; 
 scalar_t__ jz4780_mmc_reset (struct jz4780_mmc_softc*) ; 
 scalar_t__ jz4780_mmc_setup_dma (struct jz4780_mmc_softc*) ; 
 int /*<<< orphan*/  mode_sd ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_mmc_attach(device_t dev)
{
	struct jz4780_mmc_softc *sc;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *tree;
	device_t child;
	ssize_t len;
	pcell_t prop;
	phandle_t node;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_req = NULL;
	if (bus_alloc_resources(dev, jz4780_mmc_res_spec, sc->sc_res) != 0) {
		device_printf(dev, "cannot allocate device resources\n");
		return (ENXIO);
	}
	sc->sc_bst = rman_get_bustag(sc->sc_res[JZ_MSC_MEMRES]);
	sc->sc_bsh = rman_get_bushandle(sc->sc_res[JZ_MSC_MEMRES]);
	if (bus_setup_intr(dev, sc->sc_res[JZ_MSC_IRQRES],
	    INTR_TYPE_MISC | INTR_MPSAFE, NULL, jz4780_mmc_intr, sc,
	    &sc->sc_intrhand)) {
		bus_release_resources(dev, jz4780_mmc_res_spec, sc->sc_res);
		device_printf(dev, "cannot setup interrupt handler\n");
		return (ENXIO);
	}
	sc->sc_timeout = 10;
	ctx = device_get_sysctl_ctx(dev);
	tree = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));
	SYSCTL_ADD_INT(ctx, tree, OID_AUTO, "req_timeout", CTLFLAG_RW,
	    &sc->sc_timeout, 0, "Request timeout in seconds");
	mtx_init(&sc->sc_mtx, device_get_nameunit(sc->sc_dev), "jz4780_mmc",
	    MTX_DEF);
	callout_init_mtx(&sc->sc_timeoutc, &sc->sc_mtx, 0);

	/* Reset controller. */
	if (jz4780_mmc_reset(sc) != 0) {
		device_printf(dev, "cannot reset the controller\n");
		goto fail;
	}
	if (jz4780_mmc_pio_mode == 0 && jz4780_mmc_setup_dma(sc) != 0) {
		device_printf(sc->sc_dev, "Couldn't setup DMA!\n");
		jz4780_mmc_pio_mode = 1;
	}
	if (bootverbose)
		device_printf(sc->sc_dev, "DMA status: %s\n",
		    jz4780_mmc_pio_mode ? "disabled" : "enabled");

	node = ofw_bus_get_node(dev);
	/* Determine max operating frequency */
	sc->sc_host.f_max = 24000000;
	len = OF_getencprop(node, "max-frequency", &prop, sizeof(prop));
	if (len / sizeof(prop) == 1)
		sc->sc_host.f_max = prop;
	sc->sc_host.f_min = sc->sc_host.f_max / 128;

	sc->sc_host.host_ocr = MMC_OCR_320_330 | MMC_OCR_330_340;
	sc->sc_host.caps = MMC_CAP_HSPEED;
	sc->sc_host.mode = mode_sd;
	/*
	 * Check for bus-width property, default to both 4 and 8 bit
	 * if no bus width is specified.
	 */
	len = OF_getencprop(node, "bus-width", &prop, sizeof(prop));
	if (len / sizeof(prop) != 1)
		sc->sc_host.caps |= MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA;
	else if (prop == 8)
		sc->sc_host.caps |= MMC_CAP_8_BIT_DATA;
	else if (prop == 4)
		sc->sc_host.caps |= MMC_CAP_4_BIT_DATA;
	/* Activate the module clock. */
	if (jz4780_mmc_enable_clock(sc) != 0) {
		device_printf(dev, "cannot activate mmc clock\n");
		goto fail;
	}

	child = device_add_child(dev, "mmc", -1);
	if (child == NULL) {
		device_printf(dev, "attaching MMC bus failed!\n");
		goto fail;
	}
	if (device_probe_and_attach(child) != 0) {
		device_printf(dev, "attaching MMC child failed!\n");
		device_delete_child(dev, child);
		goto fail;
	}

	return (0);

fail:
	callout_drain(&sc->sc_timeoutc);
	mtx_destroy(&sc->sc_mtx);
	bus_teardown_intr(dev, sc->sc_res[JZ_MSC_IRQRES], sc->sc_intrhand);
	bus_release_resources(dev, jz4780_mmc_res_spec, sc->sc_res);
	if (sc->sc_clk != NULL)
		clk_release(sc->sc_clk);
	return (ENXIO);
}