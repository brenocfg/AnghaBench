#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_6__ {scalar_t__ operation_status; TYPE_1__ parent; int /*<<< orphan*/  core_object; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIF_SAS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_RESET ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_RESETTING ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_controller_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_controller_state_handler_table ; 

__attribute__((used)) static
void scif_sas_controller_resetting_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIF_SAS_CONTROLLER_T * fw_controller = (SCIF_SAS_CONTROLLER_T *)object;

   SET_STATE_HANDLER(
      fw_controller,
      scif_sas_controller_state_handler_table,
      SCI_BASE_CONTROLLER_STATE_RESETTING
   );

   // Attempt to reset the core controller.
   fw_controller->operation_status = scic_controller_reset(
                                        fw_controller->core_object
                                     );
   if (fw_controller->operation_status == SCI_SUCCESS)
   {
      // Reset the framework controller.
      sci_base_state_machine_change_state(
         &fw_controller->parent.state_machine,
         SCI_BASE_CONTROLLER_STATE_RESET
      );
   }
   else
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_controller),
         SCIF_LOG_OBJECT_CONTROLLER,
         "Controller: unable to successfully reset controller.\n"
      ));

      sci_base_state_machine_change_state(
         &fw_controller->parent.state_machine,
         SCI_BASE_CONTROLLER_STATE_FAILED
      );
   }
}