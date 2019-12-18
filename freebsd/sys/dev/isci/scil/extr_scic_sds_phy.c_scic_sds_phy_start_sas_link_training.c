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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_5__ {int /*<<< orphan*/  protocol; int /*<<< orphan*/  starting_substate_machine; } ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATA_SPINUP_HOLD ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_PROTOCOL_SAS ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SAS_SPEED_EN ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_READ (TYPE_1__*) ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_WRITE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_phy_start_sas_link_training(
   SCIC_SDS_PHY_T * this_phy
)
{
   U32 phy_control;

   phy_control = SCU_SAS_PCFG_READ(this_phy);
   phy_control |= SCU_SAS_PCFG_GEN_BIT(SATA_SPINUP_HOLD);
   SCU_SAS_PCFG_WRITE(this_phy, phy_control);

   sci_base_state_machine_change_state(
      &this_phy->starting_substate_machine,
      SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SAS_SPEED_EN
   );

   this_phy->protocol = SCIC_SDS_PHY_PROTOCOL_SAS;
}