#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_17__ {int /*<<< orphan*/  core_object; } ;
struct TYPE_16__ {TYPE_4__* domain; int /*<<< orphan*/  core_object; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; int /*<<< orphan*/  core_object; } ;
struct TYPE_15__ {TYPE_2__ parent; } ;
struct TYPE_14__ {int /*<<< orphan*/  parent; TYPE_3__* state_handlers; } ;
struct TYPE_13__ {scalar_t__ (* start_task_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* complete_task_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* start_handler ) (int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_5__ SCIF_SAS_TASK_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REQUEST_T ;
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
 scalar_t__ scic_controller_start_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_remote_device_target_reset (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ scif_sas_task_request_get_function (TYPE_5__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_controller_ready_start_task_handler(
   SCI_BASE_CONTROLLER_T    * controller,
   SCI_BASE_REMOTE_DEVICE_T * remote_device,
   SCI_BASE_REQUEST_T       * task_request,
   U16                        io_tag
)
{
   SCIF_SAS_CONTROLLER_T    * fw_controller = (SCIF_SAS_CONTROLLER_T*)
                                              controller;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                          remote_device;
   SCIF_SAS_TASK_REQUEST_T  * fw_task = (SCIF_SAS_TASK_REQUEST_T*)task_request;
   SCI_STATUS                 status;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_CONTROLLER | SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scif_sas_controller_ready_start_task_handler(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      controller, remote_device, task_request, io_tag
   ));

   status = fw_device->domain->state_handlers->start_task_handler(
               &fw_device->domain->parent, remote_device, task_request
            );

   if (status == SCI_SUCCESS)
   {
      if (scif_sas_task_request_get_function(fw_task)
             == SCI_SAS_HARD_RESET)
      {
         // Go off to special target reset path. Don't start task to core.
         scif_sas_remote_device_target_reset(
            fw_device,
            (SCIF_SAS_REQUEST_T *)fw_task
         );

         return SCI_SUCCESS;
      }

      // Ask the core to start processing for this task request.
      status = (SCI_STATUS)scic_controller_start_task(
                  fw_controller->core_object,
                  fw_device->core_object,
                  fw_task->parent.core_object,
                  io_tag
               );

      if (status == SCI_SUCCESS)
      {
         // We were able to start the core request. As a result,
         // commit to starting the request for the framework by changing
         // the state of the task request.
         fw_task->parent.state_handlers->start_handler(&fw_task->parent.parent);
      }
      else
      {
         // We were unable to start the core task request. As a result,
         // back out the start operation for the framework.  It's easier to
         // back out the framework start operation then to backout the core
         // start task operation.
         fw_device->domain->state_handlers->complete_task_handler(
            &fw_device->domain->parent, remote_device, task_request
         );

         if (status == SCI_SUCCESS)
         {
            SCIF_LOG_WARNING((
               sci_base_object_get_logger(fw_controller),
               SCIF_LOG_OBJECT_CONTROLLER,
               "Controller:0x%x TaskRequest:0x%x Status:0x%x core start failed\n",
               fw_controller, fw_task, status
            ));
         }
      }
   }
   else
   {
      SCIF_LOG_WARNING((
         sci_base_object_get_logger(fw_controller),
         SCIF_LOG_OBJECT_CONTROLLER,
         "Controller:0x%x TaskRequest:0x%x Status:0x%x Task start failed\n",
         fw_controller, fw_task, status
      ));
   }

   return status;
}