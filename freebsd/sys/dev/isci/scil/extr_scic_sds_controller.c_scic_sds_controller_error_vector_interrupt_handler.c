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
 int SMU_ISR_QUEUE_ERROR ; 
 int SMU_ISR_QUEUE_SUSPEND ; 
 int SMU_ISR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL scic_sds_controller_error_vector_interrupt_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   U32 interrupt_status;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;


   interrupt_status = SMU_ISR_READ(this_controller);
   interrupt_status &= (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND);

   if (interrupt_status != 0)
   {
      // There is an error interrupt pending so let it through and handle
      // in the callback
      return TRUE;
   }

   // There is a race in the hardware that could cause us not to be notified
   // of an interrupt completion if we do not take this step.  We will mask
   // then unmask the error interrupts so if there was another interrupt
   // pending we will be notified.
   // Could we write the value of (SMU_ISR_QUEUE_ERROR | SMU_ISR_QUEUE_SUSPEND)?
   SMU_IMR_WRITE(this_controller, 0x000000FF);
   SMU_IMR_WRITE(this_controller, 0x00000000);

   return FALSE;
}