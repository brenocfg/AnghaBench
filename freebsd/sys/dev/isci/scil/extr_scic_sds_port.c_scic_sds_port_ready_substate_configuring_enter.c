#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ active_phy_mask; int /*<<< orphan*/  ready_substate_machine; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS ; 
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_CONFIGURING ; 
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_OPERATIONAL ; 
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_WAITING ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_cb_port_not_ready (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_set_ready_state_handlers (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_port_ready_substate_configuring_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port = (SCIC_SDS_PORT_T *)object;

   scic_sds_port_set_ready_state_handlers(
      this_port, SCIC_SDS_PORT_READY_SUBSTATE_CONFIGURING
   );

   if (this_port->active_phy_mask == 0)
   {
      scic_cb_port_not_ready(
         scic_sds_port_get_controller(this_port),
         this_port,
         SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS
      );

      sci_base_state_machine_change_state(
         &this_port->ready_substate_machine,
         SCIC_SDS_PORT_READY_SUBSTATE_WAITING
      );
   }
   //do not wait for IO to go to 0 in this state.
   else
   {
      sci_base_state_machine_change_state(
         &this_port->ready_substate_machine,
         SCIC_SDS_PORT_READY_SUBSTATE_OPERATIONAL
      );
   }
}