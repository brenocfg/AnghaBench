#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* state_handlers; } ;
struct TYPE_17__ {int /*<<< orphan*/  rnc; int /*<<< orphan*/  ready_substate_machine; TYPE_4__* working_request; TYPE_6__* owning_port; } ;
struct TYPE_16__ {TYPE_3__* state_handlers; } ;
struct TYPE_14__ {scalar_t__ (* start_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_15__ {TYPE_2__ parent; } ;
struct TYPE_13__ {scalar_t__ (* start_io_handler ) (TYPE_6__*,TYPE_5__*,TYPE_4__*) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  int /*<<< orphan*/  SCI_BASE_REMOTE_DEVICE_T ;
typedef  TYPE_4__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK ;
typedef  TYPE_5__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_CMD ; 
 scalar_t__ SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS ; 
 int /*<<< orphan*/  SCI_SOFTWARE_SUSPENSION ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_remote_device_continue_request ; 
 int /*<<< orphan*/  scic_sds_remote_device_start_request (TYPE_5__*,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ scic_sds_remote_node_context_start_task (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_6__*,TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_remote_device_ready_substate_start_request_handler(
   SCI_BASE_REMOTE_DEVICE_T * device,
   SCI_BASE_REQUEST_T       * request
)
{
   SCI_STATUS status;
   SCIC_SDS_REMOTE_DEVICE_T * this_device  = (SCIC_SDS_REMOTE_DEVICE_T *)device;
   SCIC_SDS_REQUEST_T       * this_request = (SCIC_SDS_REQUEST_T       *)request;

   // Will the port allow the io request to start?
   status = this_device->owning_port->state_handlers->start_io_handler(
      this_device->owning_port,
      this_device,
      this_request
   );

   if (SCI_SUCCESS == status)
   {
      status =
         scic_sds_remote_node_context_start_task(this_device->rnc, this_request);

      if (SCI_SUCCESS == status)
      {
         status = this_request->state_handlers->parent.start_handler(request);
      }

      if (status == SCI_SUCCESS)
      {
         /// @note If the remote device state is not IDLE this will replace
         ///       the request that probably resulted in the task management
         ///       request.
         this_device->working_request = this_request;

         sci_base_state_machine_change_state(
            &this_device->ready_substate_machine,
            SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_CMD
         );

         //The remote node context must cleanup the TCi to NCQ mapping table.
         //The only way to do this correctly is to either write to the TLCR
         //register or to invalidate and repost the RNC. In either case the
         //remote node context state machine will take the correct action when
         //the remote node context is suspended and later resumed.
         scic_sds_remote_node_context_suspend(
            this_device->rnc, SCI_SOFTWARE_SUSPENSION, NULL, NULL);

         scic_sds_remote_node_context_resume(
            this_device->rnc,
            (SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK)
                scic_sds_remote_device_continue_request,
            this_device);
      }

      scic_sds_remote_device_start_request(this_device,this_request,status);

      //We need to let the controller start request handler know that it can't
      //post TC yet. We will provide a callback function to post TC when RNC gets
      //resumed.
      return SCI_FAILURE_RESET_DEVICE_PARTIAL_SUCCESS;
   }

   return status;
}