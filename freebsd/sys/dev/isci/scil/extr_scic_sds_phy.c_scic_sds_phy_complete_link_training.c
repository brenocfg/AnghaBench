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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_4__ {int /*<<< orphan*/  max_negotiated_speed; } ;
typedef  int /*<<< orphan*/  SCI_SAS_LINK_RATE ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_starting_substate_machine (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_phy_complete_link_training(
   SCIC_SDS_PHY_T *   this_phy,
   SCI_SAS_LINK_RATE  max_link_rate,
   U32                next_state
)
{
   this_phy->max_negotiated_speed = max_link_rate;

   sci_base_state_machine_change_state(
      scic_sds_phy_get_starting_substate_machine(this_phy), next_state
   );
}