#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* state_handlers; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* reset_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_3__* SCI_CONTROLLER_HANDLE_T ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_3__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

SCI_STATUS scic_controller_reset(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   SCI_STATUS status = SCI_FAILURE_INVALID_STATE;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_controller_reset(0x%x) enter\n",
      controller
   ));

   if (this_controller->state_handlers->parent.reset_handler != NULL)
   {
      status = this_controller->state_handlers->parent.reset_handler(
                  (SCI_BASE_CONTROLLER_T *)controller
               );
   }
   else
   {
      SCIC_LOG_WARNING((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller reset operation requested in invalid state %d\n",
         sci_base_state_machine_get_state(
            scic_sds_controller_get_base_state_machine(this_controller))
      ));
   }

   return status;
}