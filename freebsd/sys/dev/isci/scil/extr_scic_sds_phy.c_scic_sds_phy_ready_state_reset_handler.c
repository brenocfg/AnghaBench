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
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_PHY_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_PHY_STATE_RESETTING ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_base_state_machine (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_phy_ready_state_reset_handler(
   SCI_BASE_PHY_T * phy
)
{
   SCIC_SDS_PHY_T * this_phy;
   this_phy = (SCIC_SDS_PHY_T *)phy;

   sci_base_state_machine_change_state(
      scic_sds_phy_get_base_state_machine(this_phy),
      SCI_BASE_PHY_STATE_RESETTING
   );

   return SCI_SUCCESS;
}