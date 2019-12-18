#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_7__ {scalar_t__ protocol; TYPE_1__ parent; int /*<<< orphan*/  owning_port; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCIC_SDS_PHY_PROTOCOL_SAS ; 
 int /*<<< orphan*/  SCI_BASE_PHY_STATE_RESETTING ; 
 int /*<<< orphan*/  SCI_BASE_PHY_STATE_STARTING ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_set_base_state_handlers (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_deactivate_phy (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scu_link_layer_tx_hard_reset (TYPE_2__*) ; 

__attribute__((used)) static
void scic_sds_phy_resetting_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PHY_T * this_phy;
   this_phy = (SCIC_SDS_PHY_T *)object;

   scic_sds_phy_set_base_state_handlers(this_phy, SCI_BASE_PHY_STATE_RESETTING);

   // The phy is being reset, therefore deactivate it from the port.
   // In the resetting state we don't notify the user regarding
   // link up and link down notifications.
   scic_sds_port_deactivate_phy(this_phy->owning_port, this_phy, FALSE);

   if (this_phy->protocol == SCIC_SDS_PHY_PROTOCOL_SAS)
   {
      scu_link_layer_tx_hard_reset(this_phy);
   }
   else
   {
      // The SCU does not need to have a descrete reset state so just go back to
      // the starting state.
      sci_base_state_machine_change_state(
         &this_phy->parent.state_machine,
         SCI_BASE_PHY_STATE_STARTING
      );
   }
}