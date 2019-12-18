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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_FINAL ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_ENSPINUP_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_SAS_ENSPINUP_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCU_SAS_ENSPINUP_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_starting_substate_machine (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_phy_starting_substate_await_sas_power_consume_power_handler(
   SCIC_SDS_PHY_T *this_phy
)
{
   U32 enable_spinup;

   enable_spinup = SCU_SAS_ENSPINUP_READ(this_phy);
   enable_spinup |= SCU_ENSPINUP_GEN_BIT(ENABLE);
   SCU_SAS_ENSPINUP_WRITE(this_phy, enable_spinup);

   // Change state to the final state this substate machine has run to completion
   sci_base_state_machine_change_state(
      scic_sds_phy_get_starting_substate_machine(this_phy),
      SCIC_SDS_PHY_STARTING_SUBSTATE_FINAL
      );

   return SCI_SUCCESS;
}