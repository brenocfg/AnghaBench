#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_6__ {int /*<<< orphan*/  parent; TYPE_1__* state_handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* start_task_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_2__ parent; } ;
typedef  int /*<<< orphan*/  SCI_TASK_STATUS ;
typedef  scalar_t__ SCI_TASK_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_3__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_TASK_STATUS scic_controller_start_task(
   SCI_CONTROLLER_HANDLE_T    controller,
   SCI_REMOTE_DEVICE_HANDLE_T remote_device,
   SCI_TASK_REQUEST_HANDLE_T  task_request,
   U16                        task_tag
)
{
   SCI_STATUS             status = SCI_FAILURE_INVALID_STATE;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_controller_start_task(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      controller, remote_device, task_request, task_tag
   ));

   if (this_controller->state_handlers->parent.start_task_handler != NULL)
   {
      status = this_controller->state_handlers->parent.start_task_handler(
                  &this_controller->parent,
                  (SCI_BASE_REMOTE_DEVICE_T *)remote_device,
                  (SCI_BASE_REQUEST_T *)task_request,
                  task_tag
               );
   }
   else
   {
      SCIC_LOG_INFO((
         sci_base_object_get_logger(controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller starting task from invalid state\n"
      ));
   }

   return (SCI_TASK_STATUS)status;
}