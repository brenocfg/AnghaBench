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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pl310_softc {int sc_rtl_revision; int sc_io_coherent; int sc_enabled; TYPE_1__* sc_ich; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  cf_l2cache_drain_writebuf; int /*<<< orphan*/  cf_l2cache_wb_range; int /*<<< orphan*/  cf_l2cache_inv_range; int /*<<< orphan*/  cf_l2cache_wbinv_range; int /*<<< orphan*/  (* cf_l2cache_wbinv_all ) () ;} ;
struct TYPE_5__ {struct pl310_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;

/* Variables and functions */
 int CACHE_ID_PARTNUM_MASK ; 
 int CACHE_ID_PARTNUM_SHIFT ; 
 int CACHE_ID_RELEASE_MASK ; 
 int CACHE_ID_RELEASE_SHIFT ; 
 int CTRL_DISABLED ; 
 int CTRL_ENABLED ; 
 int DEBUG_CTRL_DISABLE_LINEFILL ; 
 int DEBUG_CTRL_DISABLE_WRITEBACK ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PL310_CACHE_ID ; 
 int /*<<< orphan*/  PL310_CTRL ; 
 int /*<<< orphan*/  PL310_DEBUG_CTRL ; 
 int /*<<< orphan*/  PL310_INV_WAY ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 TYPE_3__ cpufuncs ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct pl310_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_l2cache_line_size ; 
 int g_l2cache_size ; 
 int /*<<< orphan*/  g_ways_assoc ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl310_config_intr ; 
 int /*<<< orphan*/  pl310_drain_writebuf ; 
 int pl310_enabled ; 
 int /*<<< orphan*/  pl310_inv_range ; 
 int /*<<< orphan*/  pl310_print_config (struct pl310_softc*) ; 
 int pl310_read4 (struct pl310_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl310_set_way_sizes (struct pl310_softc*) ; 
 struct pl310_softc* pl310_softc ; 
 int /*<<< orphan*/  pl310_wait_background_op (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pl310_wb_range ; 
 int /*<<< orphan*/  pl310_wbinv_all () ; 
 int /*<<< orphan*/  pl310_wbinv_range ; 
 int /*<<< orphan*/  pl310_write4 (struct pl310_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_pl310_init (struct pl310_softc*) ; 
 int /*<<< orphan*/  platform_pl310_write_ctrl (struct pl310_softc*,int) ; 
 int /*<<< orphan*/  platform_pl310_write_debug (struct pl310_softc*,int) ; 

__attribute__((used)) static int
pl310_attach(device_t dev)
{
	struct pl310_softc *sc = device_get_softc(dev);
	int rid;
	uint32_t cache_id, debug_ctrl;
	phandle_t node;

	sc->sc_dev = dev;
	rid = 0;
	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_mem_res == NULL)
		panic("%s: Cannot map registers", device_get_name(dev));

	/* Allocate an IRQ resource */
	rid = 0;
	sc->sc_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	                                        RF_ACTIVE | RF_SHAREABLE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "cannot allocate IRQ, not using interrupt\n");
	}

	pl310_softc = sc;
	mtx_init(&sc->sc_mtx, "pl310lock", NULL, MTX_SPIN);

	cache_id = pl310_read4(sc, PL310_CACHE_ID);
	sc->sc_rtl_revision = (cache_id >> CACHE_ID_RELEASE_SHIFT) &
	    CACHE_ID_RELEASE_MASK;
	device_printf(dev, "Part number: 0x%x, release: 0x%x\n",
	    (cache_id >> CACHE_ID_PARTNUM_SHIFT) & CACHE_ID_PARTNUM_MASK,
	    (cache_id >> CACHE_ID_RELEASE_SHIFT) & CACHE_ID_RELEASE_MASK);

	/*
	 * Test for "arm,io-coherent" property and disable sync operation if
	 * platform is I/O coherent. Outer sync operations are not needed
	 * on coherent platform and may be harmful in certain situations.
	 */
	node = ofw_bus_get_node(dev);
	if (OF_hasprop(node, "arm,io-coherent"))
		sc->sc_io_coherent = true;

	/*
	 * If L2 cache is already enabled then something has violated the rules,
	 * because caches are supposed to be off at kernel entry.  The cache
	 * must be disabled to write the configuration registers without
	 * triggering an access error (SLVERR), but there's no documented safe
	 * procedure for disabling the L2 cache in the manual.  So we'll try to
	 * invent one:
	 *  - Use the debug register to force write-through mode and prevent
	 *    linefills (allocation of new lines on read); now anything we do
	 *    will not cause new data to come into the L2 cache.
	 *  - Writeback and invalidate the current contents.
	 *  - Disable the controller.
	 *  - Restore the original debug settings.
	 */
	if (pl310_read4(sc, PL310_CTRL) & CTRL_ENABLED) {
		device_printf(dev, "Warning: L2 Cache should not already be "
		    "active; trying to de-activate and re-initialize...\n");
		sc->sc_enabled = 1;
		debug_ctrl = pl310_read4(sc, PL310_DEBUG_CTRL);
		platform_pl310_write_debug(sc, debug_ctrl |
		    DEBUG_CTRL_DISABLE_WRITEBACK | DEBUG_CTRL_DISABLE_LINEFILL);
		pl310_set_way_sizes(sc);
		pl310_wbinv_all();
		platform_pl310_write_ctrl(sc, CTRL_DISABLED);
		platform_pl310_write_debug(sc, debug_ctrl);
	}
	sc->sc_enabled = pl310_enabled;

	if (sc->sc_enabled) {
		platform_pl310_init(sc);
		pl310_set_way_sizes(sc); /* platform init might change these */
		pl310_write4(pl310_softc, PL310_INV_WAY, 0xffff);
		pl310_wait_background_op(PL310_INV_WAY, 0xffff);
		platform_pl310_write_ctrl(sc, CTRL_ENABLED);
		device_printf(dev, "L2 Cache enabled: %uKB/%dB %d ways\n",
		    (g_l2cache_size / 1024), g_l2cache_line_size, g_ways_assoc);
		if (bootverbose)
			pl310_print_config(sc);
	} else {
		if (sc->sc_irq_res != NULL) {
			sc->sc_ich = malloc(sizeof(*sc->sc_ich), M_DEVBUF, M_WAITOK);
			sc->sc_ich->ich_func = pl310_config_intr;
			sc->sc_ich->ich_arg = sc;
			if (config_intrhook_establish(sc->sc_ich) != 0) {
				device_printf(dev,
				    "config_intrhook_establish failed\n");
				free(sc->sc_ich, M_DEVBUF);
				return(ENXIO);
			}
		}

		device_printf(dev, "L2 Cache disabled\n");
	}

	/* Set the l2 functions in the set of cpufuncs */
	cpufuncs.cf_l2cache_wbinv_all = pl310_wbinv_all;
	cpufuncs.cf_l2cache_wbinv_range = pl310_wbinv_range;
	cpufuncs.cf_l2cache_inv_range = pl310_inv_range;
	cpufuncs.cf_l2cache_wb_range = pl310_wb_range;
	cpufuncs.cf_l2cache_drain_writebuf = pl310_drain_writebuf;

	return (0);
}