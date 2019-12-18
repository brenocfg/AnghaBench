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
struct TYPE_4__ {int /*<<< orphan*/  sata_timeout_timer; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SATA_PHY_EN ; 
 int /*<<< orphan*/  SCIC_SDS_SATA_LINK_TRAINING_TIMEOUT ; 
 int /*<<< orphan*/  scic_cb_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_set_starting_substate_handlers (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_phy_starting_await_sata_phy_substate_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PHY_T *this_phy;
   this_phy = (SCIC_SDS_PHY_T *)object;

   scic_sds_phy_set_starting_substate_handlers(
      this_phy, SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SATA_PHY_EN
      );

   scic_cb_timer_start(
      scic_sds_phy_get_controller(this_phy),
      this_phy->sata_timeout_timer,
      SCIC_SDS_SATA_LINK_TRAINING_TIMEOUT
   );
}