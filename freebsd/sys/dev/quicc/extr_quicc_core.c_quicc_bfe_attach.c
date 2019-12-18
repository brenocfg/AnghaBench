#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource_list_entry {int /*<<< orphan*/ * res; } ;
struct TYPE_3__ {int rm_start; int rm_end; char* rm_descr; int /*<<< orphan*/  rm_type; } ;
struct quicc_softc {int sc_fastintr; int sc_polled; int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/ * sc_ires; int /*<<< orphan*/  sc_rtype; TYPE_1__ sc_rman; struct quicc_device* sc_device; scalar_t__ sc_irid; int /*<<< orphan*/  sc_icookie; scalar_t__ sc_rrid; } ;
struct quicc_device {int /*<<< orphan*/  qd_dev; int /*<<< orphan*/  qd_rlist; TYPE_1__* qd_rman; int /*<<< orphan*/  qd_devtype; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int /*<<< orphan*/  M_QUICC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  QUICC_DEVTYPE_SCC ; 
 int /*<<< orphan*/  QUICC_REG_SIMR_L ; 
 int /*<<< orphan*/  QUICC_REG_SIPNR_H ; 
 int /*<<< orphan*/  QUICC_REG_SIPNR_L ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct quicc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct quicc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_print_prettyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,void*) ; 
 struct quicc_device* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * quicc_bfe_intr ; 
 int /*<<< orphan*/  quicc_write4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 int rman_get_size (int /*<<< orphan*/ *) ; 
 int rman_get_start (int /*<<< orphan*/ *) ; 
 int rman_init (TYPE_1__*) ; 
 int rman_manage_region (TYPE_1__*,int,int) ; 

int
quicc_bfe_attach(device_t dev)
{
	struct quicc_device *qd;
	struct quicc_softc *sc;
	struct resource_list_entry *rle;
	const char *sep;
	rman_res_t size, start;
	int error;

	sc = device_get_softc(dev);

	/*
	 * Re-allocate. We expect that the softc contains the information
	 * collected by quicc_bfe_probe() intact.
	 */
	sc->sc_rres = bus_alloc_resource_any(dev, sc->sc_rtype, &sc->sc_rrid,
	    RF_ACTIVE);
	if (sc->sc_rres == NULL)
		return (ENXIO);

	start = rman_get_start(sc->sc_rres);
	size = rman_get_size(sc->sc_rres);

	sc->sc_rman.rm_start = start;
	sc->sc_rman.rm_end = start + size - 1;
	sc->sc_rman.rm_type = RMAN_ARRAY;
	sc->sc_rman.rm_descr = "QUICC resources";
	error = rman_init(&sc->sc_rman);
	if (!error)
		error = rman_manage_region(&sc->sc_rman, start,
		    start + size - 1);
	if (error) {
		bus_release_resource(dev, sc->sc_rtype, sc->sc_rrid,
		    sc->sc_rres);
		return (error);
	}

	/*
	 * Allocate interrupt resource.
	 */
	sc->sc_irid = 0;
	sc->sc_ires = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->sc_irid,
	    RF_ACTIVE | RF_SHAREABLE);

	if (sc->sc_ires != NULL) {
		error = bus_setup_intr(dev, sc->sc_ires,
		    INTR_TYPE_TTY, quicc_bfe_intr, NULL, sc, &sc->sc_icookie);
		if (error) {
			error = bus_setup_intr(dev, sc->sc_ires,
			    INTR_TYPE_TTY | INTR_MPSAFE, NULL,
			    (driver_intr_t *)quicc_bfe_intr, sc,
			    &sc->sc_icookie);
		} else
			sc->sc_fastintr = 1;
		if (error) {
			device_printf(dev, "could not activate interrupt\n");
			bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irid,
			    sc->sc_ires);
			sc->sc_ires = NULL;
		}
	}

	if (sc->sc_ires == NULL)
		sc->sc_polled = 1;

	if (bootverbose && (sc->sc_fastintr || sc->sc_polled)) {
		sep = "";
		device_print_prettyname(dev);
		if (sc->sc_fastintr) {
			printf("%sfast interrupt", sep);
			sep = ", ";
		}
		if (sc->sc_polled) {
			printf("%spolled mode", sep);
			sep = ", ";
		}
		printf("\n");
	}

	sc->sc_device = qd = malloc(sizeof(struct quicc_device), M_QUICC,
	    M_WAITOK | M_ZERO);

	qd->qd_devtype = QUICC_DEVTYPE_SCC;
	qd->qd_rman = &sc->sc_rman;
	resource_list_init(&qd->qd_rlist);

	resource_list_add(&qd->qd_rlist, sc->sc_rtype, 0, start,
	    start + size - 1, size);

	resource_list_add(&qd->qd_rlist, SYS_RES_IRQ, 0, 0xf00, 0xf00, 1);
	rle = resource_list_find(&qd->qd_rlist, SYS_RES_IRQ, 0);
	rle->res = sc->sc_ires;

	qd->qd_dev = device_add_child(dev, NULL, -1);
	device_set_ivars(qd->qd_dev, (void *)qd);
	error = device_probe_and_attach(qd->qd_dev);

	/* Enable all SCC interrupts. */
	quicc_write4(sc->sc_rres, QUICC_REG_SIMR_L, 0x00f00000);

	/* Clear all pending interrupts. */
	quicc_write4(sc->sc_rres, QUICC_REG_SIPNR_H, ~0);
	quicc_write4(sc->sc_rres, QUICC_REG_SIPNR_L, ~0);
	return (error);
}