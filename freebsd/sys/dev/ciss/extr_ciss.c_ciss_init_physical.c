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
typedef  union ciss_device_address {int dummy; } ciss_device_address ;
struct ciss_softc {int ciss_max_logical_bus; int ciss_max_physical_bus; int /*<<< orphan*/ ** ciss_physical; TYPE_3__* ciss_controllers; TYPE_1__* ciss_cfg; } ;
struct ciss_pdrive {int dummy; } ;
struct ciss_lun_report {TYPE_3__* lun; int /*<<< orphan*/  list_size; } ;
struct TYPE_5__ {scalar_t__ extra_address; int bus; } ;
struct TYPE_6__ {TYPE_2__ physical; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_physical_supported; } ;

/* Variables and functions */
 int CISS_EXTRA_BUS2 (scalar_t__) ; 
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 int CISS_MAX_PHYSTGT ; 
 int /*<<< orphan*/  CISS_OPCODE_REPORT_PHYSICAL_LUNS ; 
 int ENOMEM ; 
 int ENXIO ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  ciss_filter_physical (struct ciss_softc*,struct ciss_lun_report*) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,...) ; 
 struct ciss_lun_report* ciss_report_luns (struct ciss_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (struct ciss_lun_report*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 void* max (int,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ciss_init_physical(struct ciss_softc *sc)
{
    struct ciss_lun_report	*cll;
    int				error = 0, i;
    int				nphys;
    int				bus, target;

    debug_called(1);

    bus = 0;
    target = 0;

    cll = ciss_report_luns(sc, CISS_OPCODE_REPORT_PHYSICAL_LUNS,
			   sc->ciss_cfg->max_physical_supported);
    if (cll == NULL) {
	error = ENXIO;
	goto out;
    }

    nphys = (ntohl(cll->list_size) / sizeof(union ciss_device_address));

    if (bootverbose) {
	ciss_printf(sc, "%d physical device%s\n",
	    nphys, (nphys > 1 || nphys == 0) ? "s" : "");
    }

    /*
     * Figure out the bus mapping.
     * Logical buses include both the local logical bus for local arrays and
     * proxy buses for remote arrays.  Physical buses are numbered by the
     * controller and represent physical buses that hold physical devices.
     * We shift these bus numbers so that everything fits into a single flat
     * numbering space for CAM.  Logical buses occupy the first 32 CAM bus
     * numbers, and the physical bus numbers are shifted to be above that.
     * This results in the various driver arrays being indexed as follows:
     *
     * ciss_controllers[] - indexed by logical bus
     * ciss_cam_sim[]     - indexed by both logical and physical, with physical
     *                      being shifted by 32.
     * ciss_logical[][]   - indexed by logical bus
     * ciss_physical[][]  - indexed by physical bus
     *
     * XXX This is getting more and more hackish.  CISS really doesn't play
     *     well with a standard SCSI model; devices are addressed via magic
     *     cookies, not via b/t/l addresses.  Since there is no way to store
     *     the cookie in the CAM device object, we have to keep these lookup
     *     tables handy so that the devices can be found quickly at the cost
     *     of wasting memory and having a convoluted lookup scheme.  This
     *     driver should probably be converted to block interface.
     */
    /*
     * If the L2 and L3 SCSI addresses are 0, this signifies a proxy
     * controller. A proxy controller is another physical controller
     * behind the primary PCI controller. We need to know about this
     * so that BMIC commands can be properly targeted.  There can be
     * proxy controllers attached to a single PCI controller, so
     * find the highest numbered one so the array can be properly
     * sized.
     */
    sc->ciss_max_logical_bus = 1;
    for (i = 0; i < nphys; i++) {
	if (cll->lun[i].physical.extra_address == 0) {
	    bus = cll->lun[i].physical.bus;
	    sc->ciss_max_logical_bus = max(sc->ciss_max_logical_bus, bus) + 1;
	} else {
	    bus = CISS_EXTRA_BUS2(cll->lun[i].physical.extra_address);
	    sc->ciss_max_physical_bus = max(sc->ciss_max_physical_bus, bus);
	}
    }

    sc->ciss_controllers =
	malloc(sc->ciss_max_logical_bus * sizeof (union ciss_device_address),
	       CISS_MALLOC_CLASS, M_NOWAIT | M_ZERO);

    if (sc->ciss_controllers == NULL) {
	ciss_printf(sc, "Could not allocate memory for controller map\n");
	error = ENOMEM;
	goto out;
    }

    /* setup a map of controller addresses */
    for (i = 0; i < nphys; i++) {
	if (cll->lun[i].physical.extra_address == 0) {
	    sc->ciss_controllers[cll->lun[i].physical.bus] = cll->lun[i];
	}
    }

    sc->ciss_physical =
	malloc(sc->ciss_max_physical_bus * sizeof(struct ciss_pdrive *),
	       CISS_MALLOC_CLASS, M_NOWAIT | M_ZERO);
    if (sc->ciss_physical == NULL) {
	ciss_printf(sc, "Could not allocate memory for physical device map\n");
	error = ENOMEM;
	goto out;
    }

    for (i = 0; i < sc->ciss_max_physical_bus; i++) {
	sc->ciss_physical[i] =
	    malloc(sizeof(struct ciss_pdrive) * CISS_MAX_PHYSTGT,
		   CISS_MALLOC_CLASS, M_NOWAIT | M_ZERO);
	if (sc->ciss_physical[i] == NULL) {
	    ciss_printf(sc, "Could not allocate memory for target map\n");
	    error = ENOMEM;
	    goto out;
	}
    }

    ciss_filter_physical(sc, cll);

out:
    if (cll != NULL)
	free(cll, CISS_MALLOC_CLASS);

    return(error);
}