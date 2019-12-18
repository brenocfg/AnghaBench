#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  scheduled_activity; int /*<<< orphan*/  current_smp_request; int /*<<< orphan*/  current_activity; } ;
struct TYPE_10__ {TYPE_3__ smp_device; } ;
struct TYPE_12__ {TYPE_2__ protocol_device; TYPE_1__* domain; } ;
struct TYPE_9__ {int /*<<< orphan*/ * controller; } ;
typedef  TYPE_4__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_DOMAIN_DISCOVERY ; 
 int SCIF_LOG_OBJECT_REMOTE_DEVICE ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER ; 
 int /*<<< orphan*/  SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE ; 
 int /*<<< orphan*/  SMP_FUNCTION_REPORT_GENERAL ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_cb_start_internal_io_task_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_sas_controller_start_high_priority_io ; 
 int /*<<< orphan*/  scif_sas_smp_remote_device_clear (TYPE_4__*) ; 
 int /*<<< orphan*/  scif_sas_smp_request_construct_report_general (int /*<<< orphan*/ *,TYPE_4__*) ; 

void scif_sas_smp_remote_device_start_discover(
   SCIF_SAS_REMOTE_DEVICE_T * fw_device
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller = fw_device->domain->controller;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_device),
      SCIF_LOG_OBJECT_REMOTE_DEVICE | SCIF_LOG_OBJECT_DOMAIN_DISCOVERY,
      "scif_sas_smp_remote_device_start_discover(0x%x) enter\n",
      fw_device
   ));

   //For safety, clear the device again, there may be some config route table
   //related info are not cleared yet.
   scif_sas_smp_remote_device_clear(fw_device);

   //set current activity
   fw_device->protocol_device.smp_device.current_activity =
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_DISCOVER;

   //Set current_smp_request to REPORT GENERAL.
   fw_device->protocol_device.smp_device.current_smp_request =
      SMP_FUNCTION_REPORT_GENERAL;

   //reset discover_to_start flag.
   fw_device->protocol_device.smp_device.scheduled_activity =
      SCIF_SAS_SMP_REMOTE_DEVICE_ACTIVITY_NONE;

   //build the first smp request Report Genernal.
   scif_sas_smp_request_construct_report_general(fw_controller, fw_device);

   //issue DPC to start this request.
   scif_cb_start_internal_io_task_schedule(
      fw_controller,
      scif_sas_controller_start_high_priority_io,
      fw_controller
   );
}