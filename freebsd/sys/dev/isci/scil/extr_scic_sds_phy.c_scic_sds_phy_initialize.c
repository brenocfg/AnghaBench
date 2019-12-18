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
typedef  int /*<<< orphan*/  SCU_LINK_LAYER_REGISTERS_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_PHY_STATE_STOPPED ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_base_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_link_layer_initialization (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_transport_layer_initialization (int /*<<< orphan*/ *,void*) ; 

SCI_STATUS scic_sds_phy_initialize(
   SCIC_SDS_PHY_T             *this_phy,
   void                       *transport_layer_registers,
   SCU_LINK_LAYER_REGISTERS_T *link_layer_registers
)
{
   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_sds_phy_initialize(this_phy:0x%x, link_layer_registers:0x%x)\n",
      this_phy, link_layer_registers
   ));

   // Perform the initialization of the TL hardware
   scic_sds_phy_transport_layer_initialization(this_phy, transport_layer_registers);

   // Perofrm the initialization of the PE hardware
   scic_sds_phy_link_layer_initialization(this_phy, link_layer_registers);

   // There is nothing that needs to be done in this state just
   // transition to the stopped state.
   sci_base_state_machine_change_state(
      scic_sds_phy_get_base_state_machine(this_phy),
      SCI_BASE_PHY_STATE_STOPPED
   );

   return SCI_SUCCESS;
}