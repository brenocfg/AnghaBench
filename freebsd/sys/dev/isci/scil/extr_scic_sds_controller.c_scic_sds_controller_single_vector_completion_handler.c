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
 int SMU_ISR_COMPLETION ; 
 int SMU_ISR_QUEUE_ERROR ; 
 int SMU_ISR_QUEUE_SUSPEND ; 
 int SMU_ISR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMU_ISR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_controller_completion_queue_has_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_process_completions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_controller_single_vector_completion_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   U32 interrupt_status;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_sds_controller_single_vector_completion_handler(0x%d) enter\n",
      controller
   ));

   interrupt_status = SMU_ISR_READ(this_controller);
   interrupt_status &= (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND);

   if (interrupt_status & SMU_ISR_QUEUE_ERROR)
   {
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller has encountered a fatal error.\n"
      ));

      // We have a fatal condition and must reset the controller
      // Leave the interrupt mask in place and get the controller reset
      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_FAILED
      );
      return;
   }

   if (
           (interrupt_status & SMU_ISR_QUEUE_SUSPEND)
        && !scic_sds_controller_completion_queue_has_entries(this_controller)
      )
   {
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller has encountered a fatal error.\n"
      ));

      // We have a fatal condtion and must reset the controller
      // Leave the interrupt mask in place and get the controller reset
      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_FAILED
      );
      return;
   }

   if (scic_sds_controller_completion_queue_has_entries(this_controller))
   {
      scic_sds_controller_process_completions(this_controller);

      // We dont care which interrupt got us to processing the completion queu
      // so clear them both.
      SMU_ISR_WRITE(
         this_controller,
         (SMU_ISR_COMPLETION | SMU_ISR_QUEUE_SUSPEND)
      );
   }

   SMU_IMR_WRITE(this_controller, 0x00000000);
}