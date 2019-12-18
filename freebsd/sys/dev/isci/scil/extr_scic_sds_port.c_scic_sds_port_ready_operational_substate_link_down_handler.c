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
struct TYPE_5__ {scalar_t__ active_phy_mask; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_WAITING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_deactivate_phy (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_ready_substate_machine (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_port_ready_operational_substate_link_down_handler(
   SCIC_SDS_PORT_T *this_port,
   SCIC_SDS_PHY_T  *the_phy
)
{
   scic_sds_port_deactivate_phy(this_port, the_phy, TRUE);

   // If there are no active phys left in the port, then transition
   // the port to the WAITING state until such time as a phy goes
   // link up.
   if (this_port->active_phy_mask == 0)
   {
      sci_base_state_machine_change_state(
         scic_sds_port_get_ready_substate_machine(this_port),
         SCIC_SDS_PORT_READY_SUBSTATE_WAITING
      );
   }
}