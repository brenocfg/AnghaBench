#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * controller; } ;
struct TYPE_11__ {int /*<<< orphan*/  current_activity_phy_index; int /*<<< orphan*/  current_smp_request; } ;
struct TYPE_12__ {TYPE_1__ smp_device; } ;
struct TYPE_13__ {TYPE_2__ protocol_device; int /*<<< orphan*/  expander_phy_identifier; TYPE_4__* domain; } ;
typedef  TYPE_3__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIF_SAS_DOMAIN_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_FUNCTION_DISCOVER ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  scif_cb_start_internal_io_task_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_controller_start_high_priority_io ; 
 TYPE_3__* scif_sas_domain_find_device_in_spinup_hold (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_finish_discover (TYPE_3__*) ; 
 int /*<<< orphan*/  scif_sas_smp_request_construct_discover (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void scif_sas_smp_remote_device_sata_spinup_hold_release(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_DOMAIN_T        * fw_domain = fw_device->domain;
   SCIF_SAS_CONTROLLER_T    * fw_controller = fw_domain->controller;
   SCIF_SAS_REMOTE_DEVICE_T * device_to_poll = NULL;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_sata_spinup_hold_release(0x%x) enter\n",
      fw_device
   ));

   //search throught domain's device list to find a sata device on spinup_hold
   //state to poll.
   device_to_poll = scif_sas_domain_find_device_in_spinup_hold(fw_domain);

   if (device_to_poll != NULL)
   {
      //send DISCOVER command to this device's expaner phy.
      fw_device->protocol_device.smp_device.current_smp_request =
         SMP_FUNCTION_DISCOVER;

      fw_device->protocol_device.smp_device.current_activity_phy_index =
        device_to_poll->expander_phy_identifier;

      scif_sas_smp_request_construct_discover(
         fw_domain->controller,
         fw_device,
         fw_device->protocol_device.smp_device.current_activity_phy_index,
         NULL, NULL
      );

      //schedule the DPC to start new Discover command.
      scif_cb_start_internal_io_task_schedule(
         fw_controller, scif_sas_controller_start_high_priority_io, fw_controller
      );
   }
   else //SATA SPINUP HOLD RELEASE activity is done.
      scif_sas_smp_remote_device_finish_discover (fw_device);
}