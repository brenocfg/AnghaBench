#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ciss_softc {int ciss_max_logical_bus; int ciss_max_physical_bus; int /*<<< orphan*/  ciss_mtx; int /*<<< orphan*/  ciss_dev; int /*<<< orphan*/ ** ciss_cam_sim; int /*<<< orphan*/ * ciss_cam_devq; scalar_t__ ciss_max_requests; TYPE_2__* ciss_controllers; } ;
struct cam_sim {int dummy; } ;
struct TYPE_3__ {scalar_t__ bus; } ;
struct TYPE_4__ {TYPE_1__ physical; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 int CISS_PHYSICAL_BASE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 void* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ciss_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cam_simq_alloc (scalar_t__) ; 
 int /*<<< orphan*/  ciss_cam_action ; 
 int /*<<< orphan*/  ciss_cam_poll ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** malloc (int,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ciss_cam_init(struct ciss_softc *sc)
{
    int			i, maxbus;

    debug_called(1);

    /*
     * Allocate a devq.  We can reuse this for the masked physical
     * devices if we decide to export these as well.
     */
    if ((sc->ciss_cam_devq = cam_simq_alloc(sc->ciss_max_requests - 2)) == NULL) {
	ciss_printf(sc, "can't allocate CAM SIM queue\n");
	return(ENOMEM);
    }

    /*
     * Create a SIM.
     *
     * This naturally wastes a bit of memory.  The alternative is to allocate
     * and register each bus as it is found, and then track them on a linked
     * list.  Unfortunately, the driver has a few places where it needs to
     * look up the SIM based solely on bus number, and it's unclear whether
     * a list traversal would work for these situations.
     */
    maxbus = max(sc->ciss_max_logical_bus, sc->ciss_max_physical_bus +
		 CISS_PHYSICAL_BASE);
    sc->ciss_cam_sim = malloc(maxbus * sizeof(struct cam_sim*),
			      CISS_MALLOC_CLASS, M_NOWAIT | M_ZERO);
    if (sc->ciss_cam_sim == NULL) {
	ciss_printf(sc, "can't allocate memory for controller SIM\n");
	return(ENOMEM);
    }

    for (i = 0; i < sc->ciss_max_logical_bus; i++) {
	if ((sc->ciss_cam_sim[i] = cam_sim_alloc(ciss_cam_action, ciss_cam_poll,
						 "ciss", sc,
						 device_get_unit(sc->ciss_dev),
						 &sc->ciss_mtx,
						 2,
						 sc->ciss_max_requests - 2,
						 sc->ciss_cam_devq)) == NULL) {
	    ciss_printf(sc, "can't allocate CAM SIM for controller %d\n", i);
	    return(ENOMEM);
	}

	/*
	 * Register bus with this SIM.
	 */
	mtx_lock(&sc->ciss_mtx);
	if (i == 0 || sc->ciss_controllers[i].physical.bus != 0) { 
	    if (xpt_bus_register(sc->ciss_cam_sim[i], sc->ciss_dev, i) != 0) {
		ciss_printf(sc, "can't register SCSI bus %d\n", i);
		mtx_unlock(&sc->ciss_mtx);
		return (ENXIO);
	    }
	}
	mtx_unlock(&sc->ciss_mtx);
    }

    for (i = CISS_PHYSICAL_BASE; i < sc->ciss_max_physical_bus +
	 CISS_PHYSICAL_BASE; i++) {
	if ((sc->ciss_cam_sim[i] = cam_sim_alloc(ciss_cam_action, ciss_cam_poll,
						 "ciss", sc,
						 device_get_unit(sc->ciss_dev),
						 &sc->ciss_mtx, 1,
						 sc->ciss_max_requests - 2,
						 sc->ciss_cam_devq)) == NULL) {
	    ciss_printf(sc, "can't allocate CAM SIM for controller %d\n", i);
	    return (ENOMEM);
	}

	mtx_lock(&sc->ciss_mtx);
	if (xpt_bus_register(sc->ciss_cam_sim[i], sc->ciss_dev, i) != 0) {
	    ciss_printf(sc, "can't register SCSI bus %d\n", i);
	    mtx_unlock(&sc->ciss_mtx);
	    return (ENXIO);
	}
	mtx_unlock(&sc->ciss_mtx);
    }

    return(0);
}