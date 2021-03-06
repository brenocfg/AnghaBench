#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_7__ {int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_PHY ; 
 int SCIC_LOG_OBJECT_RECEIVED_EVENTS ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_PROTOCOL_SATA ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SATA_SPEED_EN ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
#define  SCU_EVENT_LINK_FAILURE 131 
#define  SCU_EVENT_SAS_PHY_DETECTED 130 
#define  SCU_EVENT_SATA_PHY_DETECTED 129 
#define  SCU_EVENT_SATA_SPINUP_HOLD 128 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_get_starting_substate_machine (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_restart_starting_state (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_start_sas_link_training (TYPE_1__*) ; 
 int scu_get_event_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_phy_starting_substate_await_sata_phy_event_handler(
   SCIC_SDS_PHY_T *this_phy,
   U32 event_code
)
{
   U32 result = SCI_SUCCESS;

   switch (scu_get_event_code(event_code))
   {
   case SCU_EVENT_LINK_FAILURE:
      // Link failure change state back to the starting state
      scic_sds_phy_restart_starting_state(this_phy);
      break;

   case SCU_EVENT_SATA_SPINUP_HOLD:
      // These events might be received since we dont know how many may be in
      // the completion queue while waiting for power
      break;

   case SCU_EVENT_SATA_PHY_DETECTED:
      this_phy->protocol = SCIC_SDS_PHY_PROTOCOL_SATA;

      // We have received the SATA PHY notification change state
      sci_base_state_machine_change_state(
         scic_sds_phy_get_starting_substate_machine(this_phy),
         SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_SATA_SPEED_EN
         );
      break;

   case SCU_EVENT_SAS_PHY_DETECTED:
      // There has been a change in the phy type before OOB/SN for the
      // SATA finished start down the SAS link traning path.
      scic_sds_phy_start_sas_link_training(this_phy);
   break;

   default:
      SCIC_LOG_WARNING((
         sci_base_object_get_logger(this_phy),
         SCIC_LOG_OBJECT_PHY | SCIC_LOG_OBJECT_RECEIVED_EVENTS,
         "PHY starting substate machine received unexpected event_code %x\n",
         event_code
      ));

      result = SCI_FAILURE;
      break;
   }

   return result;
}