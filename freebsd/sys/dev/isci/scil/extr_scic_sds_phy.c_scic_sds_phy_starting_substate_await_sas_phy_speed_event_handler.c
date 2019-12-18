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
 int SCIC_LOG_OBJECT_PHY ; 
 int SCIC_LOG_OBJECT_RECEIVED_EVENTS ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_IAF_UF ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SAS_150_GB ; 
 int /*<<< orphan*/  SCI_SAS_300_GB ; 
 int /*<<< orphan*/  SCI_SAS_600_GB ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
#define  SCU_EVENT_LINK_FAILURE 136 
#define  SCU_EVENT_SAS_15 135 
#define  SCU_EVENT_SAS_15_SSC 134 
#define  SCU_EVENT_SAS_30 133 
#define  SCU_EVENT_SAS_30_SSC 132 
#define  SCU_EVENT_SAS_60 131 
#define  SCU_EVENT_SAS_60_SSC 130 
#define  SCU_EVENT_SAS_PHY_DETECTED 129 
#define  SCU_EVENT_SATA_SPINUP_HOLD 128 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_complete_link_training (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_restart_starting_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_phy_start_sata_link_training (int /*<<< orphan*/ *) ; 
 int scu_get_event_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_phy_starting_substate_await_sas_phy_speed_event_handler(
   SCIC_SDS_PHY_T *this_phy,
   U32 event_code
)
{
   U32 result = SCI_SUCCESS;

   switch (scu_get_event_code(event_code))
   {
   case SCU_EVENT_SAS_PHY_DETECTED:
      // Why is this being reported again by the controller?
      // We would re-enter this state so just stay here
   break;

   case SCU_EVENT_SAS_15:
   case SCU_EVENT_SAS_15_SSC:
      scic_sds_phy_complete_link_training(
         this_phy, SCI_SAS_150_GB, SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_IAF_UF
      );
   break;

   case SCU_EVENT_SAS_30:
   case SCU_EVENT_SAS_30_SSC:
      scic_sds_phy_complete_link_training(
         this_phy, SCI_SAS_300_GB, SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_IAF_UF
      );
   break;

   case SCU_EVENT_SAS_60:
   case SCU_EVENT_SAS_60_SSC:
      scic_sds_phy_complete_link_training(
         this_phy, SCI_SAS_600_GB, SCIC_SDS_PHY_STARTING_SUBSTATE_AWAIT_IAF_UF
      );
   break;

   case SCU_EVENT_SATA_SPINUP_HOLD:
      // We were doing SAS PHY link training and received a SATA PHY event
      // continue OOB/SN as if this were a SATA PHY
      scic_sds_phy_start_sata_link_training(this_phy);
   break;

   case SCU_EVENT_LINK_FAILURE:
      // Link failure change state back to the starting state
      scic_sds_phy_restart_starting_state(this_phy);
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