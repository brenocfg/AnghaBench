#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int U16 ;
struct TYPE_3__ {int /*<<< orphan*/  completion_handler; int /*<<< orphan*/  interrupt_handler; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int SCIC_INTERRUPT_TYPE ;
typedef  TYPE_1__ SCIC_CONTROLLER_HANDLER_METHODS_T ;

/* Variables and functions */
#define  SCIC_LEGACY_LINE_INTERRUPT_TYPE 130 
#define  SCIC_MSIX_INTERRUPT_TYPE 129 
#define  SCIC_NO_INTERRUPTS 128 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  SCI_FAILURE_UNSUPPORTED_MESSAGE_COUNT ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_sds_controller_error_vector_completion_handler ; 
 int /*<<< orphan*/  scic_sds_controller_error_vector_interrupt_handler ; 
 int /*<<< orphan*/  scic_sds_controller_legacy_completion_handler ; 
 int /*<<< orphan*/  scic_sds_controller_legacy_interrupt_handler ; 
 int /*<<< orphan*/  scic_sds_controller_normal_vector_completion_handler ; 
 int /*<<< orphan*/  scic_sds_controller_normal_vector_interrupt_handler ; 
 int /*<<< orphan*/  scic_sds_controller_polling_completion_handler ; 
 int /*<<< orphan*/  scic_sds_controller_polling_interrupt_handler ; 
 int /*<<< orphan*/  scic_sds_controller_single_vector_completion_handler ; 
 int /*<<< orphan*/  scic_sds_controller_single_vector_interrupt_handler ; 

SCI_STATUS scic_controller_get_handler_methods(
   SCIC_INTERRUPT_TYPE                interrupt_type,
   U16                                message_count,
   SCIC_CONTROLLER_HANDLER_METHODS_T *handler_methods
)
{
   SCI_STATUS status = SCI_FAILURE_UNSUPPORTED_MESSAGE_COUNT;

   switch (interrupt_type)
   {
#if !defined(DISABLE_INTERRUPTS)
   case SCIC_LEGACY_LINE_INTERRUPT_TYPE:
      if (message_count == 0)
      {
         handler_methods[0].interrupt_handler
            = scic_sds_controller_legacy_interrupt_handler;
         handler_methods[0].completion_handler
            = scic_sds_controller_legacy_completion_handler;

         status = SCI_SUCCESS;
      }
      break;

   case SCIC_MSIX_INTERRUPT_TYPE:
      if (message_count == 1)
      {
         handler_methods[0].interrupt_handler
            = scic_sds_controller_single_vector_interrupt_handler;
         handler_methods[0].completion_handler
            = scic_sds_controller_single_vector_completion_handler;

         status = SCI_SUCCESS;
      }
      else if (message_count == 2)
      {
         handler_methods[0].interrupt_handler
            = scic_sds_controller_normal_vector_interrupt_handler;
         handler_methods[0].completion_handler
            = scic_sds_controller_normal_vector_completion_handler;

         handler_methods[1].interrupt_handler
            = scic_sds_controller_error_vector_interrupt_handler;
         handler_methods[1].completion_handler
            = scic_sds_controller_error_vector_completion_handler;

         status = SCI_SUCCESS;
      }
      break;
#endif // !defined(DISABLE_INTERRUPTS)

   case SCIC_NO_INTERRUPTS:
      if (message_count == 0)
      {

         handler_methods[0].interrupt_handler
            = scic_sds_controller_polling_interrupt_handler;
         handler_methods[0].completion_handler
            = scic_sds_controller_polling_completion_handler;

         status = SCI_SUCCESS;
      }
      break;

   default:
      status = SCI_FAILURE_INVALID_PARAMETER_VALUE;
      break;
   }

   return status;
}