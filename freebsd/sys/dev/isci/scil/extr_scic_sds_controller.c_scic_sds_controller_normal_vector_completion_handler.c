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
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMU_IMR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SMU_ISR_COMPLETION ; 
 int /*<<< orphan*/  SMU_ISR_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 scalar_t__ scic_sds_controller_completion_queue_has_entries (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_process_completions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_controller_normal_vector_completion_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_sds_controller_normal_vector_completion_handler(0x%d) enter\n",
      controller
   ));

   // Empty out the completion queue
   if (scic_sds_controller_completion_queue_has_entries(this_controller))
   {
      scic_sds_controller_process_completions(this_controller);
   }

   // Clear the interrupt and enable all interrupts again
   SMU_ISR_WRITE(this_controller, SMU_ISR_COMPLETION);
   // Could we write the value of SMU_ISR_COMPLETION?
   SMU_IMR_WRITE(this_controller, 0xFF000000);
   SMU_IMR_WRITE(this_controller, 0x00000000);
}