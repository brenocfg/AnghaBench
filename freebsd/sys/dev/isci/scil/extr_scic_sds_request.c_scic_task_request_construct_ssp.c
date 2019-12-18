#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_8__ {TYPE_1__ parent; } ;
typedef  scalar_t__ SCI_TASK_REQUEST_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_SSP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_CONSTRUCTED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_request_initialize_state_logging (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_task_request_build_ssp_task_iu (TYPE_2__*) ; 
 int /*<<< orphan*/  scu_ssp_task_request_construct_task_context (TYPE_2__*) ; 

SCI_STATUS scic_task_request_construct_ssp(
   SCI_TASK_REQUEST_HANDLE_T  scic_task_request
)
{
   SCIC_SDS_REQUEST_T *this_request = (SCIC_SDS_REQUEST_T *)
                                      scic_task_request;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_request),
      SCIC_LOG_OBJECT_SSP_IO_REQUEST,
      "scic_task_request_construct_ssp(0x%x) enter\n",
      this_request
   ));

   // Construct the SSP Task SCU Task Context
   scu_ssp_task_request_construct_task_context(this_request);

   // Fill in the SSP Task IU
   scic_sds_task_request_build_ssp_task_iu(this_request);

   scic_sds_request_initialize_state_logging(this_request);

   sci_base_state_machine_change_state(
      &this_request->parent.state_machine,
      SCI_BASE_REQUEST_STATE_CONSTRUCTED
   );

   return SCI_SUCCESS;
}