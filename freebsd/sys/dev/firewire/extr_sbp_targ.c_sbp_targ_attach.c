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
struct TYPE_4__ {int /*<<< orphan*/  xferlist; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {void* post_busreset; void* post_explore; int /*<<< orphan*/  dev; struct firewire_comm* fc; } ;
struct sbp_targ_softc {int /*<<< orphan*/ * sim; TYPE_2__ fwb; int /*<<< orphan*/  path; int /*<<< orphan*/  mtx; TYPE_1__ fd; } ;
struct firewire_comm {int dummy; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int ENXIO ; 
 int MAX_INITIATORS ; 
 int MAX_LUN ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_SBP_TARG ; 
 int /*<<< orphan*/  SBP_LOCK (struct sbp_targ_softc*) ; 
 int /*<<< orphan*/  SBP_TARG_BIND_END ; 
 int /*<<< orphan*/  SBP_TARG_BIND_START ; 
 int /*<<< orphan*/  SBP_TARG_RECV_LEN ; 
 int /*<<< orphan*/  SBP_UNLOCK (struct sbp_targ_softc*) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct sbp_targ_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 struct firewire_comm* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_bindadd (struct firewire_comm*,TYPE_2__*) ; 
 int /*<<< orphan*/  fw_xferlist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct firewire_comm*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp_targ_action ; 
 int /*<<< orphan*/  sbp_targ_poll ; 
 scalar_t__ sbp_targ_post_busreset ; 
 scalar_t__ sbp_targ_post_explore ; 
 int /*<<< orphan*/  sbp_targ_recv ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbp_targ_attach(device_t dev)
{
	struct sbp_targ_softc *sc;
	struct cam_devq *devq;
	struct firewire_comm *fc;

        sc = (struct sbp_targ_softc *) device_get_softc(dev);
	bzero((void *)sc, sizeof(struct sbp_targ_softc));

	mtx_init(&sc->mtx, "sbp_targ", NULL, MTX_DEF);
	sc->fd.fc = fc = device_get_ivars(dev);
	sc->fd.dev = dev;
	sc->fd.post_explore = (void *) sbp_targ_post_explore;
	sc->fd.post_busreset = (void *) sbp_targ_post_busreset;

        devq = cam_simq_alloc(/*maxopenings*/MAX_LUN*MAX_INITIATORS);
	if (devq == NULL)
		return (ENXIO);

	sc->sim = cam_sim_alloc(sbp_targ_action, sbp_targ_poll,
	    "sbp_targ", sc, device_get_unit(dev), &sc->mtx,
	    /*untagged*/ 1, /*tagged*/ 1, devq);
	if (sc->sim == NULL) {
		cam_simq_free(devq);
		return (ENXIO);
	}

	SBP_LOCK(sc);
	if (xpt_bus_register(sc->sim, dev, /*bus*/0) != CAM_SUCCESS)
		goto fail;

	if (xpt_create_path(&sc->path, /*periph*/ NULL, cam_sim_path(sc->sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_bus_deregister(cam_sim_path(sc->sim));
		goto fail;
	}
	SBP_UNLOCK(sc);

	sc->fwb.start = SBP_TARG_BIND_START;
	sc->fwb.end = SBP_TARG_BIND_END;

	/* pre-allocate xfer */
	STAILQ_INIT(&sc->fwb.xferlist);
	fw_xferlist_add(&sc->fwb.xferlist, M_SBP_TARG,
	    /*send*/ 0, /*recv*/ SBP_TARG_RECV_LEN, MAX_LUN /* XXX */,
	    fc, (void *)sc, sbp_targ_recv);
	fw_bindadd(fc, &sc->fwb);
	return 0;

fail:
	SBP_UNLOCK(sc);
	cam_sim_free(sc->sim, /*free_devq*/TRUE);
	return (ENXIO);
}