#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct ISCI_CONTROLLER {int queue_depth; int sim_queue_depth; int fail_on_task_timeout; int index; int /*<<< orphan*/  scif_controller_handle; TYPE_7__* phys; int /*<<< orphan*/  lock; int /*<<< orphan*/  sim; int /*<<< orphan*/  has_been_scanned; scalar_t__ oem_parameters_version; int /*<<< orphan*/  oem_parameters; TYPE_1__* isci; } ;
struct TYPE_12__ {int index; void* cdev_locate; scalar_t__ led_locate; void* cdev_fault; scalar_t__ led_fault; int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {TYPE_2__* phys; void* stp_inactivity_timeout; void* ssp_inactivity_timeout; void* stp_max_occupancy_timeout; void* ssp_max_occupancy_timeout; void* no_outbound_task_timeout; } ;
struct TYPE_11__ {TYPE_3__ sds1; } ;
struct TYPE_9__ {void* max_speed_generation; } ;
struct TYPE_8__ {scalar_t__ oem_parameters_found; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_4__ SCIC_USER_PARAMETERS_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SCI_MAX_DOMAINS ; 
 int SCI_MAX_IO_REQUESTS ; 
 int SCI_MAX_PHYS ; 
 scalar_t__ TRUE ; 
 scalar_t__ TUNABLE_INT_FETCH (char*,int*) ; 
 scalar_t__ TUNABLE_ULONG_FETCH (char*,unsigned long*) ; 
 int /*<<< orphan*/  isci_controller_attach_to_cam (struct ISCI_CONTROLLER*) ; 
 int /*<<< orphan*/  isci_led_fault_func ; 
 int /*<<< orphan*/  isci_led_locate_func ; 
 void* led_create (int /*<<< orphan*/ ,TYPE_7__*,char*) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_oem_parameters_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  scic_user_parameters_get (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  scic_user_parameters_set (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  scif_controller_get_scic_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

SCI_STATUS isci_controller_initialize(struct ISCI_CONTROLLER *controller)
{
	SCIC_USER_PARAMETERS_T scic_user_parameters;
	SCI_CONTROLLER_HANDLE_T scic_controller_handle;
	char led_name[64];
	unsigned long tunable;
	uint32_t io_shortage;
	uint32_t fail_on_timeout;
	int i;

	scic_controller_handle =
	    scif_controller_get_scic_handle(controller->scif_controller_handle);

	if (controller->isci->oem_parameters_found == TRUE)
	{
		scic_oem_parameters_set(
		    scic_controller_handle,
		    &controller->oem_parameters,
		    (uint8_t)(controller->oem_parameters_version));
	}

	scic_user_parameters_get(scic_controller_handle, &scic_user_parameters);

	if (TUNABLE_ULONG_FETCH("hw.isci.no_outbound_task_timeout", &tunable))
		scic_user_parameters.sds1.no_outbound_task_timeout =
		    (uint8_t)tunable;

	if (TUNABLE_ULONG_FETCH("hw.isci.ssp_max_occupancy_timeout", &tunable))
		scic_user_parameters.sds1.ssp_max_occupancy_timeout =
		    (uint16_t)tunable;

	if (TUNABLE_ULONG_FETCH("hw.isci.stp_max_occupancy_timeout", &tunable))
		scic_user_parameters.sds1.stp_max_occupancy_timeout =
		    (uint16_t)tunable;

	if (TUNABLE_ULONG_FETCH("hw.isci.ssp_inactivity_timeout", &tunable))
		scic_user_parameters.sds1.ssp_inactivity_timeout =
		    (uint16_t)tunable;

	if (TUNABLE_ULONG_FETCH("hw.isci.stp_inactivity_timeout", &tunable))
		scic_user_parameters.sds1.stp_inactivity_timeout =
		    (uint16_t)tunable;

	if (TUNABLE_ULONG_FETCH("hw.isci.max_speed_generation", &tunable))
		for (i = 0; i < SCI_MAX_PHYS; i++)
			scic_user_parameters.sds1.phys[i].max_speed_generation =
			    (uint8_t)tunable;

	scic_user_parameters_set(scic_controller_handle, &scic_user_parameters);

	/* Scheduler bug in SCU requires SCIL to reserve some task contexts as a
	 *  a workaround - one per domain.
	 */
	controller->queue_depth = SCI_MAX_IO_REQUESTS - SCI_MAX_DOMAINS;

	if (TUNABLE_INT_FETCH("hw.isci.controller_queue_depth",
	    &controller->queue_depth)) {
		controller->queue_depth = max(1, min(controller->queue_depth,
		    SCI_MAX_IO_REQUESTS - SCI_MAX_DOMAINS));
	}

	/* Reserve one request so that we can ensure we have one available TC
	 *  to do internal device resets.
	 */
	controller->sim_queue_depth = controller->queue_depth - 1;

	/* Although we save one TC to do internal device resets, it is possible
	 *  we could end up using several TCs for simultaneous device resets
	 *  while at the same time having CAM fill our controller queue.  To
	 *  simulate this condition, and how our driver handles it, we can set
	 *  this io_shortage parameter, which will tell CAM that we have a
	 *  large queue depth than we really do.
	 */
	io_shortage = 0;
	TUNABLE_INT_FETCH("hw.isci.io_shortage", &io_shortage);
	controller->sim_queue_depth += io_shortage;

	fail_on_timeout = 1;
	TUNABLE_INT_FETCH("hw.isci.fail_on_task_timeout", &fail_on_timeout);
	controller->fail_on_task_timeout = fail_on_timeout;

	/* Attach to CAM using xpt_bus_register now, then immediately freeze
	 *  the simq.  It will get released later when initial domain discovery
	 *  is complete.
	 */
	controller->has_been_scanned = FALSE;
	mtx_lock(&controller->lock);
	isci_controller_attach_to_cam(controller);
	xpt_freeze_simq(controller->sim, 1);
	mtx_unlock(&controller->lock);

	for (i = 0; i < SCI_MAX_PHYS; i++) {
		controller->phys[i].handle = scic_controller_handle;
		controller->phys[i].index = i;

		/* fault */
		controller->phys[i].led_fault = 0;
		sprintf(led_name, "isci.bus%d.port%d.fault", controller->index, i);
		controller->phys[i].cdev_fault = led_create(isci_led_fault_func,
		    &controller->phys[i], led_name);
			
		/* locate */
		controller->phys[i].led_locate = 0;
		sprintf(led_name, "isci.bus%d.port%d.locate", controller->index, i);
		controller->phys[i].cdev_locate = led_create(isci_led_locate_func,
		    &controller->phys[i], led_name);
	}

	return (scif_controller_initialize(controller->scif_controller_handle));
}