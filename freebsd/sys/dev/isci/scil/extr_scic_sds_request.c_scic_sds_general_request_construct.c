#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U16 ;
struct TYPE_3__ {int sat_protocol; int post_context; int /*<<< orphan*/ * owning_controller; int /*<<< orphan*/ * task_context_buffer; void* was_tag_assigned_by_user; void* is_task_management_request; scalar_t__ scu_status; int /*<<< orphan*/  sci_status; int /*<<< orphan*/  device_sequence; int /*<<< orphan*/  saved_rx_frame_index; int /*<<< orphan*/  protocol; void* has_started_substate_machine; int /*<<< orphan*/ * target_device; void* user_request; scalar_t__ io_tag; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SCIC_NO_PROTOCOL ; 
 scalar_t__ SCI_CONTROLLER_INVALID_IO_TAG ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_INVALID_FRAME_INDEX ; 
 void* TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_request_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * scic_sds_controller_get_task_context_buffer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_remote_device_get_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_request_state_table ; 

__attribute__((used)) static
void scic_sds_general_request_construct(
   SCIC_SDS_CONTROLLER_T    * the_controller,
   SCIC_SDS_REMOTE_DEVICE_T * the_target,
   U16                        io_tag,
   void                     * user_io_request_object,
   SCIC_SDS_REQUEST_T       * this_request
)
{
   sci_base_request_construct(
      &this_request->parent,
      sci_base_object_get_logger(the_controller),
      scic_sds_request_state_table
   );

   this_request->io_tag = io_tag;
   this_request->user_request = user_io_request_object;
   this_request->owning_controller = the_controller;
   this_request->target_device = the_target;
   this_request->has_started_substate_machine = FALSE;
   this_request->protocol = SCIC_NO_PROTOCOL;
   this_request->sat_protocol = 0xFF;
   this_request->saved_rx_frame_index = SCU_INVALID_FRAME_INDEX;
   this_request->device_sequence = scic_sds_remote_device_get_sequence(the_target);

   this_request->sci_status   = SCI_SUCCESS;
   this_request->scu_status   = 0;
   this_request->post_context = 0xFFFFFFFF;

   this_request->is_task_management_request = FALSE;

   if (io_tag == SCI_CONTROLLER_INVALID_IO_TAG)
   {
      this_request->was_tag_assigned_by_user = FALSE;
      this_request->task_context_buffer = NULL;
   }
   else
   {
      this_request->was_tag_assigned_by_user = TRUE;

      this_request->task_context_buffer =
         scic_sds_controller_get_task_context_buffer(
            this_request->owning_controller, io_tag);
   }
}