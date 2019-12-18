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
typedef  scalar_t__ SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SMU_IMR_WRITE (int /*<<< orphan*/ *,int) ; 
 int SMU_ISR_COMPLETION ; 
 int SMU_ISR_QUEUE_ERROR ; 
 int SMU_ISR_QUEUE_SUSPEND ; 
 int SMU_ISR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMU_ISR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ scic_sds_controller_completion_queue_has_entries (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
BOOL scic_sds_controller_single_vector_interrupt_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   U32 interrupt_status;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   // Mask the interrupts
   // There is a race in the hardware that could cause us not to be notified
   // of an interrupt completion if we do not take this step.  We will unmask
   // the interrupts in the completion routine.
   SMU_IMR_WRITE(this_controller, 0xFFFFFFFF);

   interrupt_status = SMU_ISR_READ(this_controller);
   interrupt_status &= (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND);

   if (
           (interrupt_status == 0)
        && scic_sds_controller_completion_queue_has_entries(this_controller)
      )
   {
      // There is at least one completion queue entry to process so we can
      // return a success and ignore for now the case of an error interrupt
      SMU_ISR_WRITE(this_controller, SMU_ISR_COMPLETION);

      return TRUE;
   }


   if (interrupt_status != 0)
   {
      // There is an error interrupt pending so let it through and handle
      // in the callback
      return TRUE;
   }

   // Clear any offending interrupts since we could not find any to handle
   // and unmask them all
   SMU_ISR_WRITE(this_controller, 0x00000000);
   SMU_IMR_WRITE(this_controller, 0x00000000);

   return FALSE;
}