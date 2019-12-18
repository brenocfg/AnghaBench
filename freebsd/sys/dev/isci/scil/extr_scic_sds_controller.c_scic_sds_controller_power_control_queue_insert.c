#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_25__ {scalar_t__ high; scalar_t__ low; } ;
struct TYPE_26__ {TYPE_6__ sas_address; } ;
struct TYPE_27__ {TYPE_7__ identify_address_frame_buffer; } ;
struct TYPE_28__ {TYPE_8__ sas; } ;
struct TYPE_23__ {scalar_t__ current_state_id; } ;
struct TYPE_24__ {TYPE_4__ state_machine; } ;
struct TYPE_20__ {scalar_t__ max_number_concurrent_device_spin_up; } ;
struct TYPE_21__ {TYPE_1__ controller; } ;
struct TYPE_22__ {TYPE_2__ sds1; } ;
struct TYPE_17__ {scalar_t__ remote_devices_granted_power; int /*<<< orphan*/  phys_waiting; TYPE_11__** requesters; } ;
struct TYPE_19__ {TYPE_10__ power_control; TYPE_11__* phy_table; TYPE_3__ oem_parameters; } ;
struct TYPE_18__ {scalar_t__ protocol; size_t phy_index; TYPE_9__ phy_type; TYPE_5__ parent; } ;
typedef  TYPE_11__ SCIC_SDS_PHY_T ;
typedef  TYPE_12__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SCIC_SDS_PHY_PROTOCOL_SAS ; 
 scalar_t__ SCI_BASE_PHY_STATE_READY ; 
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  scic_sds_controller_power_control_timer_restart (TYPE_12__*) ; 
 int /*<<< orphan*/  scic_sds_phy_consume_power_handler (TYPE_11__*) ; 

void scic_sds_controller_power_control_queue_insert(
   SCIC_SDS_CONTROLLER_T *this_controller,
   SCIC_SDS_PHY_T        *the_phy
)
{
   ASSERT (the_phy != NULL);

   if( this_controller->power_control.remote_devices_granted_power <
       this_controller->oem_parameters.sds1.controller.max_number_concurrent_device_spin_up
     )
   {
      this_controller->power_control.remote_devices_granted_power ++;
      scic_sds_phy_consume_power_handler(the_phy);

      //stop and start the power_control timer. When the timer fires, the
      //no_of_devices_granted_power will be set to 0
      scic_sds_controller_power_control_timer_restart (this_controller);
   }
   else
   {
      //there are phys, attached to the same sas address as this phy, are already
      //in READY state, this phy don't need wait.
      U8 i;
      SCIC_SDS_PHY_T * current_phy;
      for(i = 0; i < SCI_MAX_PHYS; i++)
      {
         current_phy = &this_controller->phy_table[i];

         if (current_phy->parent.state_machine.current_state_id == SCI_BASE_PHY_STATE_READY &&
             current_phy->protocol == SCIC_SDS_PHY_PROTOCOL_SAS &&
             current_phy->phy_type.sas.identify_address_frame_buffer.sas_address.high
                == the_phy->phy_type.sas.identify_address_frame_buffer.sas_address.high &&
             current_phy->phy_type.sas.identify_address_frame_buffer.sas_address.low
                == the_phy->phy_type.sas.identify_address_frame_buffer.sas_address.low)
         {
            scic_sds_phy_consume_power_handler(the_phy);
            break;
         }
      }

      if (i == SCI_MAX_PHYS)
      {
         //Add the phy in the waiting list
         this_controller->power_control.requesters[the_phy->phy_index] = the_phy;
         this_controller->power_control.phys_waiting++;
      }
   }
}