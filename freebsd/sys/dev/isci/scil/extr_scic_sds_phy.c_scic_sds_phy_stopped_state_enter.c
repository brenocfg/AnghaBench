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
struct TYPE_5__ {int /*<<< orphan*/ * sata_timeout_timer; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_PHY_STATE_STOPPED ; 
 int /*<<< orphan*/  scic_cb_timer_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_get_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_set_base_state_handlers (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scu_link_layer_stop_protocol_engine (TYPE_1__*) ; 

__attribute__((used)) static
void scic_sds_phy_stopped_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   SCIC_SDS_PHY_T *this_phy;
   this_phy = (SCIC_SDS_PHY_T *)object;

   /// @todo We need to get to the controller to place this PE in a reset state
   scic_sds_phy_set_base_state_handlers(this_phy, SCI_BASE_PHY_STATE_STOPPED);

   if (this_phy->sata_timeout_timer != NULL)
   {
      scic_cb_timer_destroy(
         scic_sds_phy_get_controller(this_phy),
         this_phy->sata_timeout_timer
      );

      this_phy->sata_timeout_timer = NULL;
   }

   scu_link_layer_stop_protocol_engine(this_phy);
}