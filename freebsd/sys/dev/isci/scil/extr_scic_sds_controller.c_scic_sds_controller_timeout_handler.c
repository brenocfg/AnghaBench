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
typedef  scalar_t__ SCI_BASE_CONTROLLER_STATES ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_STARTING ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_STOPPING ; 
 int /*<<< orphan*/  SCI_FAILURE_TIMEOUT ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sci_base_state_machine_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_controller_stop_complete (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_transition_to_ready (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scic_sds_controller_timeout_handler(
   SCI_CONTROLLER_HANDLE_T controller
)
{
   SCI_BASE_CONTROLLER_STATES current_state;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   current_state = sci_base_state_machine_get_state(
                      scic_sds_controller_get_base_state_machine(this_controller)
                   );

   if (current_state == SCI_BASE_CONTROLLER_STATE_STARTING)
   {
      scic_sds_controller_transition_to_ready(
         this_controller, SCI_FAILURE_TIMEOUT
      );
   }
   else if (current_state == SCI_BASE_CONTROLLER_STATE_STOPPING)
   {
      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_FAILED
      );

      scic_cb_controller_stop_complete(controller, SCI_FAILURE_TIMEOUT);
   }
   else
   {
      /// @todo Now what do we want to do in this case?
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "Controller timer fired when controller was not in a state being timed.\n"
      ));
   }
}