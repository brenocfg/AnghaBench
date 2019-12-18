#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ active_phy_mask; int /*<<< orphan*/  ready_substate_machine; int /*<<< orphan*/  not_ready_reason; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS ; 
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_OPERATIONAL ; 
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_WAITING ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_set_ready_state_handlers (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_suspend_port_task_scheduler (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_port_ready_substate_waiting_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PORT_T *this_port = (SCIC_SDS_PORT_T *)object;

   scic_sds_port_set_ready_state_handlers(
      this_port, SCIC_SDS_PORT_READY_SUBSTATE_WAITING
   );

   scic_sds_port_suspend_port_task_scheduler(this_port);


   this_port->not_ready_reason = SCIC_PORT_NOT_READY_NO_ACTIVE_PHYS;

   if (this_port->active_phy_mask != 0)
   {
      // At least one of the phys on the port is ready
      sci_base_state_machine_change_state(
         &this_port->ready_substate_machine,
         SCIC_SDS_PORT_READY_SUBSTATE_OPERATIONAL
      );
   }
}