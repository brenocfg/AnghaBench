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
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ control; } ;
struct TYPE_17__ {int /*<<< orphan*/  parent; TYPE_3__* target_device; TYPE_10__* owning_controller; int /*<<< orphan*/  io_tag; } ;
struct TYPE_16__ {scalar_t__ control_frame; } ;
struct TYPE_15__ {int /*<<< orphan*/  parent; } ;
struct TYPE_13__ {scalar_t__ (* continue_io_handler ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {TYPE_1__ parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; TYPE_2__* state_handlers; } ;
typedef  TYPE_4__ SCU_TASK_CONTEXT_T ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_5__ SCIC_SDS_REQUEST_T ;
typedef  TYPE_6__ SATA_FIS_REG_H2D_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_STARTED_SOFT_RESET_AWAIT_H2D_DIAGNOSTIC_COMPLETION_SUBSTATE ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* scic_sds_controller_get_task_context_buffer (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_stp_request_started_soft_reset_substate_handler_table ; 
 TYPE_6__* scic_stp_io_request_get_h2d_reg_address (TYPE_5__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_stp_request_started_soft_reset_await_h2d_diagnostic_completion_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCI_STATUS status;
   SCIC_SDS_REQUEST_T *this_request = (SCIC_SDS_REQUEST_T *)object;
   SATA_FIS_REG_H2D_T *h2d_fis;
   SCU_TASK_CONTEXT_T *task_context;

   // Clear the SRST bit
   h2d_fis = scic_stp_io_request_get_h2d_reg_address(this_request);
   h2d_fis->control = 0;

   // Clear the TC control bit
   task_context = scic_sds_controller_get_task_context_buffer(
                        this_request->owning_controller, this_request->io_tag);
   task_context->control_frame = 0;

   status = this_request->owning_controller->state_handlers->parent.continue_io_handler(
      &this_request->owning_controller->parent,
      &this_request->target_device->parent,
      &this_request->parent
   );

   if (status == SCI_SUCCESS)
   {
      SET_STATE_HANDLER(
         this_request,
         scic_sds_stp_request_started_soft_reset_substate_handler_table,
         SCIC_SDS_STP_REQUEST_STARTED_SOFT_RESET_AWAIT_H2D_DIAGNOSTIC_COMPLETION_SUBSTATE
      );
   }
}