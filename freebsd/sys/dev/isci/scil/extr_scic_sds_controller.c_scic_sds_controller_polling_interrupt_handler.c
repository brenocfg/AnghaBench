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
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int SMU_ISR_COMPLETION ; 
 int SMU_ISR_QUEUE_ERROR ; 
 int SMU_ISR_QUEUE_SUSPEND ; 
 int SMU_ISR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (scalar_t__) ; 
 int /*<<< orphan*/  scic_sds_controller_standard_interrupt_handler (scalar_t__,int) ; 

__attribute__((used)) static
BOOL scic_sds_controller_polling_interrupt_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   U32                    interrupt_status;
   SCIC_SDS_CONTROLLER_T *this_controller = (SCIC_SDS_CONTROLLER_T*)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_sds_controller_polling_interrupt_handler(0x%d) enter\n",
      controller
   ));

   /*
    * In INTERRUPT_POLLING_MODE we exit the interrupt handler if the hardware
    * indicates nothing is pending. Since we are not being called from a real
    * interrupt, we don't want to confuse the hardware by servicing the
    * completion queue before the hardware indicates it is ready. We'll
    * simply wait for another polling interval and check again.
    */
   interrupt_status = SMU_ISR_READ(this_controller);
   if ((interrupt_status &
         (SMU_ISR_COMPLETION |
          SMU_ISR_QUEUE_ERROR |
          SMU_ISR_QUEUE_SUSPEND)) == 0)
   {
      return FALSE;
   }

   return scic_sds_controller_standard_interrupt_handler(
             controller, interrupt_status
          );
}