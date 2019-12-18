#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int U32 ;
typedef  int /*<<< orphan*/ * SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
 int /*<<< orphan*/  SMU_IMR_WRITE (int /*<<< orphan*/ *,int) ; 
 int SMU_ISR_QUEUE_SUSPEND ; 
 int SMU_ISR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMU_ISR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_controller_completion_queue_has_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_process_completions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_controller_error_vector_completion_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   U32 interrupt_status;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_sds_controller_error_vector_completion_handler(0x%d) enter\n",
      controller
   ));

   interrupt_status = SMU_ISR_READ(this_controller);

   if (
            (interrupt_status & SMU_ISR_QUEUE_SUSPEND)
         && scic_sds_controller_completion_queue_has_entries(this_controller)
      )
   {
      scic_sds_controller_process_completions(this_controller);

      SMU_ISR_WRITE(this_controller, SMU_ISR_QUEUE_SUSPEND);
   }
   else
   {
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller reports CRC error on completion ISR %x\n",
         interrupt_status
      ));

      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_FAILED
      );

      return;
   }

   // If we dont process any completions I am not sure that we want to do this.
   // We are in the middle of a hardware fault and should probably be reset.
   SMU_IMR_WRITE(this_controller, 0x00000000);
}