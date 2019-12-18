#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  is_in_link_training; int /*<<< orphan*/  sata_timeout_timer; int /*<<< orphan*/  owning_port; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SIG_FIS_UF ; 
 int /*<<< orphan*/  SCIC_SDS_SIGNATURE_FIS_TIMEOUT ; 
 int /*<<< orphan*/  scic_cb_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_resume (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_set_starting_substate_handlers (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_port_link_detected (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_phy_starting_await_sig_fis_uf_substate_enter(
   SCI_BASE_OBJECT_T *object
)
{
   BOOL             continue_to_ready_state;
   SCIC_SDS_PHY_T * this_phy;

   this_phy = (SCIC_SDS_PHY_T *)object;

   scic_sds_phy_set_starting_substate_handlers(
      this_phy, SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SIG_FIS_UF
   );

   continue_to_ready_state = scic_sds_port_link_detected(
                                 this_phy->owning_port,
                                 this_phy
                             );

   if (continue_to_ready_state)
   {
      // Clear the PE suspend condition so we can actually receive SIG FIS
      // The hardware will not respond to the XRDY until the PE suspend
      // condition is cleared.
      scic_sds_phy_resume(this_phy);

      scic_cb_timer_start(
         scic_sds_phy_get_controller(this_phy),
         this_phy->sata_timeout_timer,
         SCIC_SDS_SIGNATURE_FIS_TIMEOUT
      );
   }
   else
   {
      this_phy->is_in_link_training = FALSE;
   }
}