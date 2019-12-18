#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  int uintmax_t ;
struct rman {char* rm_descr; int /*<<< orphan*/  rm_end; int /*<<< orphan*/  rm_start; int /*<<< orphan*/  rm_type; } ;
struct lbc_softc {int sc_addr_cells; int sc_size_cells; int /*<<< orphan*/ * sc_mres; scalar_t__ sc_mrid; TYPE_1__* sc_banks; struct rman sc_rman; int /*<<< orphan*/  sc_ltesr; int /*<<< orphan*/ * sc_ires; scalar_t__ sc_irid; int /*<<< orphan*/  sc_icookie; int /*<<< orphan*/  sc_bsh; int /*<<< orphan*/  sc_bst; int /*<<< orphan*/ * sc_dev; } ;
struct TYPE_5__ {int obd_name; } ;
struct lbc_devinfo {TYPE_2__ di_ofw; int /*<<< orphan*/  di_res; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {int addr; int size; int width; scalar_t__ wp; int /*<<< orphan*/  atom; int /*<<< orphan*/  decc; int /*<<< orphan*/  msel; } ;

/* Variables and functions */
 int ENXIO ; 
 int ERANGE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  LBC85XX_BR (int) ; 
 int /*<<< orphan*/  LBC85XX_LBCR ; 
 int /*<<< orphan*/  LBC85XX_LCRR ; 
 int /*<<< orphan*/  LBC85XX_LTEDR ; 
 int /*<<< orphan*/  LBC85XX_LTEIR ; 
 int /*<<< orphan*/  LBC85XX_LTESR ; 
 int /*<<< orphan*/  LBC85XX_OR (int) ; 
 int /*<<< orphan*/  LBCRES_ATOM_DISABLED ; 
 int /*<<< orphan*/  LBCRES_DECC_DISABLED ; 
 int /*<<< orphan*/  LBCRES_MSEL_GPCM ; 
 int LBC_DEV_MAX ; 
 int /*<<< orphan*/  M_LBC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OF_child (int /*<<< orphan*/ ) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (int*) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lbc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugf (char*,int,int,...) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct lbc_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct lbc_devinfo*) ; 
 scalar_t__ fdt_addrsize_cells (int /*<<< orphan*/ ,int*,int*) ; 
 int fdt_data_get (void*,int) ; 
 int /*<<< orphan*/  fdt_lbc_fixup (int /*<<< orphan*/ ,struct lbc_softc*,struct lbc_devinfo*) ; 
 scalar_t__ fdt_lbc_reg_decode (int /*<<< orphan*/ ,struct lbc_softc*,struct lbc_devinfo*) ; 
 int fdt_parent_addr_cells (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct lbc_devinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbc_banks_enable (struct lbc_softc*) ; 
 int lbc_banks_map (struct lbc_softc*) ; 
 int /*<<< orphan*/  lbc_intr ; 
 struct lbc_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_2__*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_fini (struct rman*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int rman_init (struct rman*) ; 
 int rman_manage_region (struct rman*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lbc_attach(device_t dev)
{
	struct lbc_softc *sc;
	struct lbc_devinfo *di;
	struct rman *rm;
	uintmax_t offset, size;
	vm_paddr_t start;
	device_t cdev;
	phandle_t node, child;
	pcell_t *ranges, *rangesptr;
	int tuple_size, tuples;
	int par_addr_cells;
	int bank, error, i, j;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	sc->sc_mrid = 0;
	sc->sc_mres = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->sc_mrid,
	    RF_ACTIVE);
	if (sc->sc_mres == NULL)
		return (ENXIO);

	sc->sc_bst = rman_get_bustag(sc->sc_mres);
	sc->sc_bsh = rman_get_bushandle(sc->sc_mres);

	for (bank = 0; bank < LBC_DEV_MAX; bank++) {
		bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_BR(bank), 0);
		bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_OR(bank), 0);
	}

	/*
	 * Initialize configuration register:
	 * - enable Local Bus
	 * - set data buffer control signal function
	 * - disable parity byte select
	 * - set ECC parity type
	 * - set bus monitor timing and timer prescale
	 */
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_LBCR, 0);

	/*
	 * Initialize clock ratio register:
	 * - disable PLL bypass mode
	 * - configure LCLK delay cycles for the assertion of LALE
	 * - set system clock divider
	 */
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_LCRR, 0x00030008);

	bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_LTEDR, 0);
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_LTESR, ~0);
	bus_space_write_4(sc->sc_bst, sc->sc_bsh, LBC85XX_LTEIR, 0x64080001);

	sc->sc_irid = 0;
	sc->sc_ires = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->sc_irid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->sc_ires != NULL) {
		error = bus_setup_intr(dev, sc->sc_ires,
		    INTR_TYPE_MISC | INTR_MPSAFE, NULL, lbc_intr, sc,
		    &sc->sc_icookie);
		if (error) {
			device_printf(dev, "could not activate interrupt\n");
			bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irid,
			    sc->sc_ires);
			sc->sc_ires = NULL;
		}
	}

	sc->sc_ltesr = ~0;

	rangesptr = NULL;

	rm = &sc->sc_rman;
	rm->rm_type = RMAN_ARRAY;
	rm->rm_descr = "Local Bus Space";
	error = rman_init(rm);
	if (error)
		goto fail;

	error = rman_manage_region(rm, rm->rm_start, rm->rm_end);
	if (error) {
		rman_fini(rm);
		goto fail;
	}

	/*
	 * Process 'ranges' property.
	 */
	node = ofw_bus_get_node(dev);
	if ((fdt_addrsize_cells(node, &sc->sc_addr_cells,
	    &sc->sc_size_cells)) != 0) {
		error = ENXIO;
		goto fail;
	}

	par_addr_cells = fdt_parent_addr_cells(node);
	if (par_addr_cells > 2) {
		device_printf(dev, "unsupported parent #addr-cells\n");
		error = ERANGE;
		goto fail;
	}
	tuple_size = sizeof(pcell_t) * (sc->sc_addr_cells + par_addr_cells +
	    sc->sc_size_cells);

	tuples = OF_getencprop_alloc_multi(node, "ranges", tuple_size,
	    (void **)&ranges);
	if (tuples < 0) {
		device_printf(dev, "could not retrieve 'ranges' property\n");
		error = ENXIO;
		goto fail;
	}
	rangesptr = ranges;

	debugf("par addr_cells = %d, addr_cells = %d, size_cells = %d, "
	    "tuple_size = %d, tuples = %d\n", par_addr_cells,
	    sc->sc_addr_cells, sc->sc_size_cells, tuple_size, tuples);

	start = 0;
	size = 0;
	for (i = 0; i < tuples; i++) {

		/* The first cell is the bank (chip select) number. */
		bank = fdt_data_get(ranges, 1);
		if (bank < 0 || bank > LBC_DEV_MAX) {
			device_printf(dev, "bank out of range: %d\n", bank);
			error = ERANGE;
			goto fail;
		}
		ranges += 1;

		/*
		 * Remaining cells of the child address define offset into
		 * this CS.
		 */
		offset = 0;
		for (j = 0; j < sc->sc_addr_cells - 1; j++) {
			offset <<= sizeof(pcell_t) * 8;
			offset |= *ranges;
			ranges++;
		}

		/* Parent bus start address of this bank. */
		start = 0;
		for (j = 0; j < par_addr_cells; j++) {
			start <<= sizeof(pcell_t) * 8;
			start |= *ranges;
			ranges++;
		}

		size = fdt_data_get((void *)ranges, sc->sc_size_cells);
		ranges += sc->sc_size_cells;
		debugf("bank = %d, start = %jx, size = %jx\n", bank,
		    (uintmax_t)start, size);

		sc->sc_banks[bank].addr = start + offset;
		sc->sc_banks[bank].size = size;

		/*
		 * Attributes for the bank.
		 *
		 * XXX Note there are no DT bindings defined for them at the
		 * moment, so we need to provide some defaults.
		 */
		sc->sc_banks[bank].width = 16;
		sc->sc_banks[bank].msel = LBCRES_MSEL_GPCM;
		sc->sc_banks[bank].decc = LBCRES_DECC_DISABLED;
		sc->sc_banks[bank].atom = LBCRES_ATOM_DISABLED;
		sc->sc_banks[bank].wp = 0;
	}

	/*
	 * Initialize mem-mappings for the LBC banks (i.e. chip selects).
	 */
	error = lbc_banks_map(sc);
	if (error)
		goto fail;

	/*
	 * Walk the localbus and add direct subordinates as our children.
	 */
	for (child = OF_child(node); child != 0; child = OF_peer(child)) {

		di = malloc(sizeof(*di), M_LBC, M_WAITOK | M_ZERO);

		if (ofw_bus_gen_setup_devinfo(&di->di_ofw, child) != 0) {
			free(di, M_LBC);
			device_printf(dev, "could not set up devinfo\n");
			continue;
		}

		resource_list_init(&di->di_res);

		if (fdt_lbc_reg_decode(child, sc, di)) {
			device_printf(dev, "could not process 'reg' "
			    "property\n");
			ofw_bus_gen_destroy_devinfo(&di->di_ofw);
			free(di, M_LBC);
			continue;
		}

		fdt_lbc_fixup(child, sc, di);

		/* Add newbus device for this FDT node */
		cdev = device_add_child(dev, NULL, -1);
		if (cdev == NULL) {
			device_printf(dev, "could not add child: %s\n",
			    di->di_ofw.obd_name);
			resource_list_free(&di->di_res);
			ofw_bus_gen_destroy_devinfo(&di->di_ofw);
			free(di, M_LBC);
			continue;
		}
		debugf("added child name='%s', node=%x\n", di->di_ofw.obd_name,
		    child);
		device_set_ivars(cdev, di);
	}

	/*
	 * Enable the LBC.
	 */
	lbc_banks_enable(sc);

	OF_prop_free(rangesptr);
	return (bus_generic_attach(dev));

fail:
	OF_prop_free(rangesptr);
	bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_mrid, sc->sc_mres);
	return (error);
}