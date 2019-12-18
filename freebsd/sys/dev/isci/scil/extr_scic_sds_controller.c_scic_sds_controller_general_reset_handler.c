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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_RESETTING ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_release_resource (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_general_reset_handler(
   SCI_BASE_CONTROLLER_T *controller
)
{
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_sds_controller_resetting_state_enter(0x%x) enter\n",
      controller
   ));

   //Release resource. So far only resource to be released are timers.
   scic_sds_controller_release_resource(this_controller);

   // The reset operation is not a graceful cleanup just perform the state
   // transition.
   sci_base_state_machine_change_state(
      scic_sds_controller_get_base_state_machine(this_controller),
      SCI_BASE_CONTROLLER_STATE_RESETTING
   );

   return SCI_SUCCESS;
}