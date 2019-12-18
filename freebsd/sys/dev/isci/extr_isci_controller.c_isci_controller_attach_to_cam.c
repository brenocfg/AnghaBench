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
struct isci_softc {int /*<<< orphan*/  device; } ;
struct cam_devq {int dummy; } ;
struct ISCI_CONTROLLER {int /*<<< orphan*/  lock; int /*<<< orphan*/ * sim; int /*<<< orphan*/  path; int /*<<< orphan*/  index; int /*<<< orphan*/  sim_queue_depth; struct isci_softc* isci; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ISCI_CONTROLLER*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 struct cam_devq* cam_simq_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isci_action ; 
 int /*<<< orphan*/  isci_log_message (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  isci_poll ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int isci_controller_attach_to_cam(struct ISCI_CONTROLLER *controller)
{
	struct isci_softc *isci = controller->isci;
	device_t parent = device_get_parent(isci->device);
	int unit = device_get_unit(isci->device);
	struct cam_devq *isci_devq = cam_simq_alloc(controller->sim_queue_depth);

	if(isci_devq == NULL) {
		isci_log_message(0, "ISCI", "isci_devq is NULL \n");
		return (-1);
	}

	controller->sim = cam_sim_alloc(isci_action, isci_poll, "isci",
	    controller, unit, &controller->lock, controller->sim_queue_depth,
	    controller->sim_queue_depth, isci_devq);

	if(controller->sim == NULL) {
		isci_log_message(0, "ISCI", "cam_sim_alloc... fails\n");
		cam_simq_free(isci_devq);
		return (-1);
	}

	if(xpt_bus_register(controller->sim, parent, controller->index)
	    != CAM_SUCCESS) {
		isci_log_message(0, "ISCI", "xpt_bus_register...fails \n");
		cam_sim_free(controller->sim, TRUE);
		mtx_unlock(&controller->lock);
		return (-1);
	}

	if(xpt_create_path(&controller->path, NULL,
	    cam_sim_path(controller->sim), CAM_TARGET_WILDCARD,
	    CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		isci_log_message(0, "ISCI", "xpt_create_path....fails\n");
		xpt_bus_deregister(cam_sim_path(controller->sim));
		cam_sim_free(controller->sim, TRUE);
		mtx_unlock(&controller->lock);
		return (-1);
	}

	return (0);
}