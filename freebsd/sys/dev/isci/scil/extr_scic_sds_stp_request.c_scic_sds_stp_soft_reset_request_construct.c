#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_1__ parent; int /*<<< orphan*/  started_substate_machine; int /*<<< orphan*/  task_context_buffer; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_T ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_STARTED_SOFT_RESET_AWAIT_H2D_ASSERTED_COMPLETION_SUBSTATE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_stp_non_ncq_request_construct (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_stp_request_started_soft_reset_substate_table ; 
 int /*<<< orphan*/  scu_stp_raw_request_construct_task_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SCI_STATUS scic_sds_stp_soft_reset_request_construct(
   SCIC_SDS_REQUEST_T * this_request
)
{
   scic_sds_stp_non_ncq_request_construct(this_request);

   // Build the STP task context structure
   scu_stp_raw_request_construct_task_context(
      (SCIC_SDS_STP_REQUEST_T*) this_request,
      this_request->task_context_buffer
   );

   sci_base_state_machine_construct(
      &this_request->started_substate_machine,
      &this_request->parent.parent,
      scic_sds_stp_request_started_soft_reset_substate_table,
      SCIC_SDS_STP_REQUEST_STARTED_SOFT_RESET_AWAIT_H2D_ASSERTED_COMPLETION_SUBSTATE
   );

   return SCI_SUCCESS;
}