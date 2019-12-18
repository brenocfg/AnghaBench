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
struct TYPE_8__ {scalar_t__ current_state_id; } ;
struct TYPE_9__ {TYPE_1__ state_machine; } ;
struct TYPE_10__ {TYPE_2__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_3__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_CONTROLLER ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_READY ; 
 scalar_t__ SCI_BASE_CONTROLLER_STATE_STARTING ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_3__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_controller_start_complete (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_3__*) ; 

__attribute__((used)) static
void scic_sds_controller_transition_to_ready(
   SCIC_SDS_CONTROLLER_T *this_controller,
   SCI_STATUS             status
)
{
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_controller),
      SCIC_LOG_OBJECT_CONTROLLER,
      "scic_sds_controller_transition_to_ready(0x%x, 0x%x) enter\n",
      this_controller, status
   ));

   if (this_controller->parent.state_machine.current_state_id
       == SCI_BASE_CONTROLLER_STATE_STARTING)
   {
      // We move into the ready state, because some of the phys/ports
      // may be up and operational.
      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_READY
      );

      scic_cb_controller_start_complete(this_controller, status);
   }
}