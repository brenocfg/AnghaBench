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
typedef  scalar_t__ SCI_OBJECT_HANDLE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCI_BASE_PHY_STATE_STARTING ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_base_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_get_starting_substate_machine (int /*<<< orphan*/ *) ; 

void scic_sds_phy_sata_timeout( SCI_OBJECT_HANDLE_T cookie)
{
   SCIC_SDS_PHY_T * this_phy = (SCIC_SDS_PHY_T *)cookie;

   SCIC_LOG_INFO((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "SCIC SDS Phy 0x%x did not receive signature fis before timeout.\n",
      this_phy
   ));

   sci_base_state_machine_stop(
      scic_sds_phy_get_starting_substate_machine(this_phy));

   sci_base_state_machine_change_state(
      scic_sds_phy_get_base_state_machine(this_phy),
      SCI_BASE_PHY_STATE_STARTING
   );
}