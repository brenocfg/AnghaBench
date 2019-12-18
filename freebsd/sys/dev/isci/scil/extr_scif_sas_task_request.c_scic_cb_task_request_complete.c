#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ (* protocol_complete_handler ) (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*,scalar_t__*) ;scalar_t__ is_internal; int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_13__ {TYPE_5__ parent; } ;
struct TYPE_12__ {scalar_t__ (* complete_handler ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SCI_TASK_STATUS ;
typedef  int /*<<< orphan*/  SCI_TASK_REQUEST_HANDLE_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_2__ SCIF_SAS_TASK_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_2__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_WARNING (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 scalar_t__ sci_object_get_association (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_cb_task_request_complete (TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_controller_complete_task (TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  scif_sas_task_request_get_function (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*,scalar_t__*) ; 

void scic_cb_task_request_complete(
   SCI_CONTROLLER_HANDLE_T     controller,
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device,
   SCI_TASK_REQUEST_HANDLE_T   task_request,
   SCI_TASK_STATUS             completion_status
)
{
   SCIF_SAS_CONTROLLER_T    * fw_controller = (SCIF_SAS_CONTROLLER_T*)
                                         sci_object_get_association(controller);
   SCIF_SAS_REMOTE_DEVICE_T * fw_device = (SCIF_SAS_REMOTE_DEVICE_T*)
                                      sci_object_get_association(remote_device);
   SCIF_SAS_TASK_REQUEST_T  * fw_task = (SCIF_SAS_TASK_REQUEST_T*)
                                       sci_object_get_association(task_request);
   SCI_STATUS                 status;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_TASK_MANAGEMENT,
      "scic_cb_task_request_complete(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      controller, remote_device, task_request, completion_status
   ));

   status = fw_task->parent.state_handlers->complete_handler(
               &fw_task->parent.parent
            );

   if (status == SCI_SUCCESS)
   {
      if (fw_task->parent.protocol_complete_handler != NULL)
      {
         status = fw_task->parent.protocol_complete_handler(
            fw_controller, fw_device, &fw_task->parent, (SCI_STATUS *)&completion_status
         );
      }

      if (status == SCI_SUCCESS)
      {
         SCIF_LOG_WARNING((
            sci_base_object_get_logger(fw_task),
            SCIF_LOG_OBJECT_TASK_MANAGEMENT,
            "RemoteDevice:0x%x TaskRequest:0x%x Function:0x%x CompletionStatus:0x%x "
            "completed\n",
            fw_device, fw_task,
            scif_sas_task_request_get_function(fw_task),
            completion_status
         ));

         // If this isn't an internal framework IO request, then simply pass the
         // notification up to the SCIF user.  Otherwise, immediately complete the
         // task since there is no SCIF user to notify.
         if (fw_task->parent.is_internal == FALSE)
         {
            scif_cb_task_request_complete(
               fw_controller, fw_device, fw_task, completion_status
            );
         }
         else
         {
            scif_controller_complete_task(
               fw_controller,
               fw_device,
               fw_task
            );
         }
      }
   }
}