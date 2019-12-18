#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_15__ {TYPE_1__ parent; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* scic_cb_passthru_get_transfer_length ) (TYPE_4__*) ;int /*<<< orphan*/  (* scic_cb_passthru_get_data_direction ) (TYPE_4__*) ;} ;
struct TYPE_14__ {TYPE_2__ common_callbacks; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_3__ SCIC_SSP_PASSTHRU_REQUEST_CALLBACKS_T ;
typedef  TYPE_4__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_CONSTRUCTED ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (void*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_io_request_build_ssp_command_iu_pass_through (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  scic_sds_request_initialize_state_logging (TYPE_4__*) ; 
 int /*<<< orphan*/  scu_ssp_io_request_construct_task_context (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 

SCI_STATUS scic_io_request_construct_ssp_pass_through (
   void                    * scic_io_request,
   SCIC_SSP_PASSTHRU_REQUEST_CALLBACKS_T *ssp_passthru_cb
)
{
   SCI_STATUS               status = SCI_SUCCESS;
   SCIC_SDS_REQUEST_T       * this_request;

   this_request = (SCIC_SDS_REQUEST_T * )scic_io_request;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(scic_io_request),
      SCIC_LOG_OBJECT_STP_IO_REQUEST,
      "scic_io_request_construct_ssp_pass_through(0x%x) enter\n",
      scic_io_request
   ));

   //build the task context from the pass through buffer
   scu_ssp_io_request_construct_task_context(
      this_request,
      ssp_passthru_cb->common_callbacks.scic_cb_passthru_get_data_direction (this_request),
      ssp_passthru_cb->common_callbacks.scic_cb_passthru_get_transfer_length(this_request)
   );

   //build the ssp command iu from the pass through buffer
   status = scic_sds_io_request_build_ssp_command_iu_pass_through (
               this_request,
               ssp_passthru_cb
            );
   if (status != SCI_SUCCESS)
   {
      return status;
   }

   /* initialize the logging */
   scic_sds_request_initialize_state_logging(this_request);

   sci_base_state_machine_change_state(
      &this_request->parent.state_machine,
      SCI_BASE_REQUEST_STATE_CONSTRUCTED
   );

   return status;
}