#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_11__ {scalar_t__ io_tag; scalar_t__ was_tag_assigned_by_user; TYPE_3__ parent; int /*<<< orphan*/  post_context; int /*<<< orphan*/  owning_controller; TYPE_4__* task_context_buffer; } ;
struct TYPE_7__ {scalar_t__ tag; int target_port_transfer_tag; } ;
struct TYPE_8__ {TYPE_1__ ssp; } ;
struct TYPE_10__ {int protocol_type; TYPE_2__ type; int /*<<< orphan*/  task_index; } ;
typedef  TYPE_4__ SCU_TASK_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  TYPE_5__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_STARTED ; 
 scalar_t__ SCI_CONTROLLER_INVALID_IO_TAG ; 
 int /*<<< orphan*/  SCI_FAILURE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
#define  SCU_TASK_CONTEXT_PROTOCOL_NONE 131 
#define  SCU_TASK_CONTEXT_PROTOCOL_SMP 130 
#define  SCU_TASK_CONTEXT_PROTOCOL_SSP 129 
#define  SCU_TASK_CONTEXT_PROTOCOL_STP 128 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_controller_allocate_io_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_copy_task_context (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_io_tag_get_index (scalar_t__) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_request_constructed_state_start_handler(
   SCI_BASE_REQUEST_T *request
)
{
   SCU_TASK_CONTEXT_T *task_context;
   SCIC_SDS_REQUEST_T *this_request = (SCIC_SDS_REQUEST_T *)request;

   if (this_request->io_tag == SCI_CONTROLLER_INVALID_IO_TAG)
   {
      this_request->io_tag =
         scic_controller_allocate_io_tag(this_request->owning_controller);
   }

   // Record the IO Tag in the request
   if (this_request->io_tag != SCI_CONTROLLER_INVALID_IO_TAG)
   {
      task_context = this_request->task_context_buffer;

      task_context->task_index = scic_sds_io_tag_get_index(this_request->io_tag);

      switch (task_context->protocol_type)
      {
      case SCU_TASK_CONTEXT_PROTOCOL_SMP:
      case SCU_TASK_CONTEXT_PROTOCOL_SSP:
         // SSP/SMP Frame
         task_context->type.ssp.tag = this_request->io_tag;
         task_context->type.ssp.target_port_transfer_tag = 0xFFFF;
         break;

      case SCU_TASK_CONTEXT_PROTOCOL_STP:
         // STP/SATA Frame
         //task_context->type.stp.ncq_tag = this_request->ncq_tag;
         break;

      case SCU_TASK_CONTEXT_PROTOCOL_NONE:
         /// @todo When do we set no protocol type?
         break;

      default:
         // This should never happen since we build the IO requests
         break;
      }

      // Check to see if we need to copy the task context buffer
      // or have been building into the task context buffer
      if (this_request->was_tag_assigned_by_user == FALSE)
      {
         scic_sds_controller_copy_task_context(
            this_request->owning_controller, this_request
         );
      }

      // Add to the post_context the io tag value
      this_request->post_context |= scic_sds_io_tag_get_index(this_request->io_tag);

      // Everything is good go ahead and change state
      sci_base_state_machine_change_state(
         &this_request->parent.state_machine,
         SCI_BASE_REQUEST_STATE_STARTED
      );

      return SCI_SUCCESS;
   }

   return SCI_FAILURE_INSUFFICIENT_RESOURCES;
}