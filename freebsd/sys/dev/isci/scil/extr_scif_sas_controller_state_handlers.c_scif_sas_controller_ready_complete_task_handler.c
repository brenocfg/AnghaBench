#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_15__ {int /*<<< orphan*/  core_object; TYPE_2__* domain; } ;
struct TYPE_13__ {int /*<<< orphan*/  core_object; int /*<<< orphan*/  parent; TYPE_3__* state_handlers; } ;
struct TYPE_14__ {TYPE_4__ parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* destruct_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_10__ {scalar_t__ (* complete_task_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_5__ SCIF_SAS_TASK_REQUEST_T ;
typedef  TYPE_6__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_7__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int SCIF_LOG_OBJECT_CONTROLLER ; 
 int SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_SAS_HARD_RESET ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_7__*) ; 
 scalar_t__ scic_controller_complete_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scif_sas_task_request_get_function (TYPE_5__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_ready_complete_task_handler(
   SCI_BASE_CONTROLLER_T    * controller,
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * task_request
)
{
   SCIF_SAS_CONTROLLER_T    *fw_controller = (SCIF_SAS_CONTROLLER_T*)controller;
   SCIF_SAS_REMOTE_DEVICE_T *fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)remote_device;
   SCIF_SAS_TASK_REQUEST_T  *fw_task = (SCIF_SAS_TASK_REQUEST_T*)task_request;
   SCI_STATUS                status;
   SCI_STATUS                core_status;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_controller_ready_complete_task_handler(0x%x, 0x%x, 0x%x) enter\n",
      controller, remote_device, task_request
   ));

   status = fw_device->domain->state_handlers->complete_task_handler(
               &fw_device->domain->parent, remote_device, task_request
            );

   if (scif_sas_task_request_get_function(fw_task)
          == SCI_SAS_HARD_RESET)
   {
      //No more things to do in the core, since this task is for Target Reset.
      return status;
   }

   fw_task->parent.state_handlers->destruct_handler(&fw_task->parent.parent);

   // Ask the core to finish processing for this task request.
   core_status = scic_controller_complete_task(
                    fw_controller->core_object,
                    fw_device->core_object,
                    fw_task->parent.core_object
                 );

   if (status == SCI_SUCCESS)
      status = core_status;

   if (status != SCI_SUCCESS)
   {
      SCIF_LOG_WARNING((
         sci_base_object_get_logger(fw_controller),
         SCIF_LOG_OBJECT_CONTROLLER,
         "Controller:0x%x TaskRequest:0x%x Status:0x%x CoreStatus:0x%x "
         "failed to complete\n",
         fw_controller, fw_task, status, core_status
      ));
   }

   return status;
}