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
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct cam_devq {int dummy; } ;
struct aac_sim {TYPE_1__* aac_sc; int /*<<< orphan*/  TargetsPerBus; struct aac_cam* aac_cam; } ;
struct aac_cam {struct cam_path* path; struct cam_sim* sim; struct aac_sim* inf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  cam_rescan_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int EIO ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aac_cam_action ; 
 int /*<<< orphan*/  aac_cam_poll ; 
 int /*<<< orphan*/  aac_cam_rescan ; 
 struct cam_sim* aac_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct aac_cam*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct cam_devq*) ; 
 scalar_t__ aac_xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 struct cam_devq* cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aac_cam_attach(device_t dev)
{
	struct cam_devq *devq;
	struct cam_sim *sim;
	struct cam_path *path;
	struct aac_cam *camsc;
	struct aac_sim *inf;

	camsc = (struct aac_cam *)device_get_softc(dev);
	inf = (struct aac_sim *)device_get_ivars(dev);
	if (!inf)
		return (EIO);
	fwprintf(inf->aac_sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	camsc->inf = inf;
	camsc->inf->aac_cam = camsc;

	devq = cam_simq_alloc(inf->TargetsPerBus);
	if (devq == NULL)
		return (EIO);

	sim = aac_sim_alloc(aac_cam_action, aac_cam_poll, "aacraidp", camsc,
	    device_get_unit(dev), &inf->aac_sc->aac_io_lock, 1, 1, devq);
	if (sim == NULL) {
		cam_simq_free(devq);
		return (EIO);
	}

	/* Since every bus has it's own sim, every bus 'appears' as bus 0 */
	mtx_lock(&inf->aac_sc->aac_io_lock);
	if (aac_xpt_bus_register(sim, dev, 0) != CAM_SUCCESS) {
		cam_sim_free(sim, TRUE);
		mtx_unlock(&inf->aac_sc->aac_io_lock);
		return (EIO);
	}

	if (xpt_create_path(&path, NULL, cam_sim_path(sim),
	    CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		xpt_bus_deregister(cam_sim_path(sim));
		cam_sim_free(sim, TRUE);
		mtx_unlock(&inf->aac_sc->aac_io_lock);
		return (EIO);
	}

#if __FreeBSD_version >= 700000
	inf->aac_sc->cam_rescan_cb = aac_cam_rescan;
#endif
	mtx_unlock(&inf->aac_sc->aac_io_lock);

	camsc->sim = sim;
	camsc->path = path;

	return (0);
}