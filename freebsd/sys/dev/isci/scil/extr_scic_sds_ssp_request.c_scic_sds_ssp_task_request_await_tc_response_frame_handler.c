#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_6__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_7__ {TYPE_1__ parent; int /*<<< orphan*/ * owning_controller; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_COMPLETED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_release_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_io_request_copy_response (TYPE_2__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_ssp_task_request_await_tc_response_frame_handler(
   SCIC_SDS_REQUEST_T * this_request,
   U32                  frame_index
)
{
   // Save off the controller, so that we do not touch the request after it
   //  is completed.
   SCIC_SDS_CONTROLLER_T * owning_controller = this_request->owning_controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_request),
      SCIC_LOG_OBJECT_TASK_MANAGEMENT,
      "scic_sds_ssp_task_request_await_tc_response_frame_handler(0x%x, 0x%x) enter\n",
      this_request, frame_index
   ));

   scic_sds_io_request_copy_response(this_request);

   sci_base_state_machine_change_state(
      &this_request->parent.state_machine,
      SCI_BASE_REQUEST_STATE_COMPLETED
   );

   scic_sds_controller_release_frame(
      owning_controller, frame_index
   );

   return SCI_SUCCESS;
}