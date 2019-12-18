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
struct vpo_data {int /*<<< orphan*/ * sim; int /*<<< orphan*/  vpo_io; scalar_t__ vpo_isplus; } ;
struct ppb_data {int /*<<< orphan*/  ppc_lock; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CAM_SUCCESS ; 
 struct vpo_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vpo_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ppb_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int imm_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpo_action ; 
 int /*<<< orphan*/  vpo_poll ; 
 int vpoio_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vpo_attach(device_t dev)
{
	struct vpo_data *vpo = DEVTOSOFTC(dev);
	device_t ppbus = device_get_parent(dev);
	struct ppb_data *ppb = device_get_softc(ppbus);	/* XXX: layering */
	struct cam_devq *devq;
	int error;

	/* low level attachment */
	if (vpo->vpo_isplus) {
		if ((error = imm_attach(&vpo->vpo_io)))
			return (error);
	} else {
		if ((error = vpoio_attach(&vpo->vpo_io)))
			return (error);
	}

	/*
	**	Now tell the generic SCSI layer
	**	about our bus.
	*/
	devq = cam_simq_alloc(/*maxopenings*/1);
	/* XXX What about low-level detach on error? */
	if (devq == NULL)
		return (ENXIO);

	vpo->sim = cam_sim_alloc(vpo_action, vpo_poll, "vpo", vpo,
				 device_get_unit(dev), ppb->ppc_lock,
				 /*untagged*/1, /*tagged*/0, devq);
	if (vpo->sim == NULL) {
		cam_simq_free(devq);
		return (ENXIO);
	}

	ppb_lock(ppbus);
	if (xpt_bus_register(vpo->sim, dev, /*bus*/0) != CAM_SUCCESS) {
		cam_sim_free(vpo->sim, /*free_devq*/TRUE);
		ppb_unlock(ppbus);
		return (ENXIO);
	}
	ppb_unlock(ppbus);

	return (0);
}