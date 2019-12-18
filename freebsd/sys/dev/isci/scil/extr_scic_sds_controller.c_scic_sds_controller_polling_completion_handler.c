#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_10__ {scalar_t__ encountered_fatal_error; scalar_t__ restrict_completions; } ;
typedef  TYPE_1__* SCI_CONTROLLER_HANDLE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
 int SMU_ISR_COMPLETION ; 
 int SMU_ISR_QUEUE_ERROR ; 
 int SMU_ISR_QUEUE_SUSPEND ; 
 int /*<<< orphan*/  SMU_ISR_WRITE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_controller_completion_queue_has_entries (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_controller_process_completions (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_controller_transitioned_process_completions (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_controller_polling_completion_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   SCIC_SDS_CONTROLLER_T *this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_sds_controller_polling_completion_handler(0x%d) enter\n",
      controller
   ));

   if (this_controller->encountered_fatal_error == TRUE)
   {
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller has encountered a fatal error.\n"
      ));

      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_FAILED
      );
   }
   else if (scic_sds_controller_completion_queue_has_entries(this_controller))
   {
      if (this_controller->restrict_completions == FALSE)
         scic_sds_controller_process_completions(this_controller);
      else
         scic_sds_controller_transitioned_process_completions(this_controller);
   }

   /*
    * The interrupt handler does not adjust the CQ's
    * get pointer.  So, SCU's INTx pin stays asserted during the
    * interrupt handler even though it tries to clear the interrupt
    * source.  Therefore, the completion handler must ensure that the
    * interrupt source is cleared.  Otherwise, we get a spurious
    * interrupt for which the interrupt handler will not issue a
    * corresponding completion event. Also, we unmask interrupts.
    */
   SMU_ISR_WRITE(
      this_controller,
      (U32)(SMU_ISR_COMPLETION | SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND)
   );
}