#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  protocol; int /*<<< orphan*/  starting_substate_machine; } ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_PHY_PROTOCOL_SATA ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SATA_POWER ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_phy_start_sata_link_training(
   SCIC_SDS_PHY_T * this_phy
)
{
   sci_base_state_machine_change_state(
      &this_phy->starting_substate_machine,
      SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SATA_POWER
   );

   this_phy->protocol = SCIC_SDS_PHY_PROTOCOL_SATA;
}