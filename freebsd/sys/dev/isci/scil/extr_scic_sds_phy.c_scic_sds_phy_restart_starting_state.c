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
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_PHY_STATE_STARTING ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_base_state_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_get_starting_substate_machine (int /*<<< orphan*/ *) ; 

void scic_sds_phy_restart_starting_state(
   SCIC_SDS_PHY_T *this_phy
)
{
   // Stop the current substate machine
   sci_base_state_machine_stop(
      scic_sds_phy_get_starting_substate_machine(this_phy)
   );

   // Re-enter the base state machine starting state
   sci_base_state_machine_change_state(
      scic_sds_phy_get_base_state_machine(this_phy),
      SCI_BASE_PHY_STATE_STARTING
      );
}