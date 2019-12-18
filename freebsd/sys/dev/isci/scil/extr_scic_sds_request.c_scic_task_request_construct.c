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
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct TYPE_14__ {int /*<<< orphan*/  task_context_buffer; void* is_task_management_request; TYPE_1__ parent; int /*<<< orphan*/  started_substate_machine; void* has_started_substate_machine; } ;
struct TYPE_11__ {scalar_t__ attached_stp_target; scalar_t__ attached_ssp_target; } ;
struct TYPE_12__ {TYPE_2__ bits; } ;
struct TYPE_13__ {TYPE_3__ u; } ;
typedef  TYPE_4__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCU_TASK_CONTEXT_T ;
typedef  void* SCI_TASK_REQUEST_HANDLE_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  scalar_t__ SCI_REMOTE_DEVICE_HANDLE_T ;
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_5__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_SSP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_IO_REQUEST_STARTED_TASK_MGMT_SUBSTATE_AWAIT_TC_COMPLETION ; 
 scalar_t__ SCI_FAILURE_UNSUPPORTED_PROTOCOL ; 
 scalar_t__ SCI_SUCCESS ; 
 void* TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_general_request_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_io_request_started_task_mgmt_substate_table ; 
 int /*<<< orphan*/  scic_sds_ssp_task_request_assign_buffers (TYPE_5__*) ; 
 int /*<<< orphan*/  scic_sds_stp_request_assign_buffers (TYPE_5__*) ; 

SCI_STATUS scic_task_request_construct(
   SCI_CONTROLLER_HANDLE_T     controller,
   SCI_REMOTE_DEVICE_HANDLE_T  remote_device,
   U16                         io_tag,
   void                       *user_io_request_object,
   void                       *scic_task_request_memory,
   SCI_TASK_REQUEST_HANDLE_T  *new_scic_task_request_handle
)
{
   SCI_STATUS           status = SCI_SUCCESS;
   SCIC_SDS_REQUEST_T * this_request = (SCIC_SDS_REQUEST_T *)
                                       scic_task_request_memory;
   SMP_DISCOVER_RESPONSE_PROTOCOLS_T   device_protocol;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      (SCIC_LOG_OBJECT_SSP_IO_REQUEST
      |SCIC_LOG_OBJECT_SMP_IO_REQUEST
      |SCIC_LOG_OBJECT_STP_IO_REQUEST),
      "scic_task_request_construct(0x%x, 0x%x, 0x02x, 0x%x, 0x%x, 0x%x) enter\n",
      controller, remote_device,
      io_tag, user_io_request_object,
      scic_task_request_memory, new_scic_task_request_handle
   ));

   // Build the common part of the request
   scic_sds_general_request_construct(
      (SCIC_SDS_CONTROLLER_T *)controller,
      (SCIC_SDS_REMOTE_DEVICE_T *)remote_device,
      io_tag,
      user_io_request_object,
      this_request
   );

   scic_remote_device_get_protocols(remote_device, &device_protocol);

   if (device_protocol.u.bits.attached_ssp_target)
   {
      scic_sds_ssp_task_request_assign_buffers(this_request);

      this_request->has_started_substate_machine = TRUE;

      // Construct the started sub-state machine.
      sci_base_state_machine_construct(
         &this_request->started_substate_machine,
         &this_request->parent.parent,
         scic_sds_io_request_started_task_mgmt_substate_table,
         SCIC_SDS_IO_REQUEST_STARTED_TASK_MGMT_SUBSTATE_AWAIT_TC_COMPLETION
      );
   }
   else if (device_protocol.u.bits.attached_stp_target)
   {
      scic_sds_stp_request_assign_buffers(this_request);
   }
   else
   {
      status = SCI_FAILURE_UNSUPPORTED_PROTOCOL;
   }

   if (status == SCI_SUCCESS)
   {
      this_request->is_task_management_request = TRUE;
      memset(this_request->task_context_buffer, 0x00, sizeof(SCU_TASK_CONTEXT_T));
      *new_scic_task_request_handle            = scic_task_request_memory;
   }

   return status;
}