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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SMU_IMR_WRITE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SMU_ISR_COMPLETION ; 
 int /*<<< orphan*/  SMU_ISR_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ scic_sds_controller_completion_queue_has_entries (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
BOOL scic_sds_controller_normal_vector_interrupt_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   if (scic_sds_controller_completion_queue_has_entries(this_controller))
   {
      return TRUE;
   }
   else
   {
      // we have a spurious interrupt it could be that we have already
      // emptied the completion queue from a previous interrupt
      SMU_ISR_WRITE(this_controller, SMU_ISR_COMPLETION);

      // There is a race in the hardware that could cause us not to be notified
      // of an interrupt completion if we do not take this step.  We will mask
      // then unmask the interrupts so if there is another interrupt pending
      // the clearing of the interrupt source we get the next interrupt message.
      SMU_IMR_WRITE(this_controller, 0xFF000000);
      SMU_IMR_WRITE(this_controller, 0x00000000);
   }

   return FALSE;
}