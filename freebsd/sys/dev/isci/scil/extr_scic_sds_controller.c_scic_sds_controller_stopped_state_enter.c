#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  port_agent; int /*<<< orphan*/ * timeout_timer; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_STOPPED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  scic_cb_controller_stop_complete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_timer_destroy (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_set_base_state_handlers (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_stop_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_configuration_agent_destroy (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void scic_sds_controller_stopped_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller= (SCIC_SDS_CONTROLLER_T *)object;

   scic_sds_controller_set_base_state_handlers(
      this_controller, SCI_BASE_CONTROLLER_STATE_STOPPED);

   // We are done with this timer until the next timer we initialize
   scic_cb_timer_destroy(
      this_controller,
      this_controller->timeout_timer
   );
   this_controller->timeout_timer = NULL;

   // Controller has stopped so disable all the phys on this controller
   scic_sds_controller_stop_phys(this_controller);

   scic_sds_port_configuration_agent_destroy(
      this_controller,
      &this_controller->port_agent
   );

   scic_cb_controller_stop_complete(this_controller, SCI_SUCCESS);
}