#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_17__ {scalar_t__ high; scalar_t__ low; } ;
struct TYPE_18__ {TYPE_4__ sas_address; } ;
struct TYPE_19__ {TYPE_5__ identify_address_frame_buffer; } ;
struct TYPE_20__ {TYPE_6__ sas; } ;
struct TYPE_22__ {scalar_t__ protocol; TYPE_7__ phy_type; } ;
struct TYPE_21__ {scalar_t__ remote_devices_granted_power; scalar_t__ phys_waiting; TYPE_9__** requesters; int /*<<< orphan*/  timer_started; } ;
struct TYPE_14__ {scalar_t__ max_number_concurrent_device_spin_up; } ;
struct TYPE_15__ {TYPE_1__ controller; } ;
struct TYPE_16__ {TYPE_2__ sds1; } ;
struct TYPE_13__ {TYPE_8__ power_control; TYPE_3__ oem_parameters; } ;
typedef  TYPE_9__ SCIC_SDS_PHY_T ;
typedef  TYPE_10__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SCIC_SDS_PHY_PROTOCOL_SAS ; 
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  scic_sds_controller_power_control_timer_start (TYPE_10__*) ; 
 int /*<<< orphan*/  scic_sds_phy_consume_power_handler (TYPE_9__*) ; 

void scic_sds_controller_power_control_timer_handler(
   void *controller
)
{
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   this_controller->power_control.remote_devices_granted_power = 0;

   if (this_controller->power_control.phys_waiting == 0)
   {
      this_controller->power_control.timer_started = FALSE;
   }
   else
   {
      SCIC_SDS_PHY_T *the_phy = NULL;
      U8 i;

      for (i=0;
              (i < SCI_MAX_PHYS)
           && (this_controller->power_control.phys_waiting != 0);
           i++)
      {
         if (this_controller->power_control.requesters[i] != NULL)
         {
            if ( this_controller->power_control.remote_devices_granted_power <
                 this_controller->oem_parameters.sds1.controller.max_number_concurrent_device_spin_up
               )
            {
               the_phy = this_controller->power_control.requesters[i];
               this_controller->power_control.requesters[i] = NULL;
               this_controller->power_control.phys_waiting--;
               this_controller->power_control.remote_devices_granted_power ++;
               scic_sds_phy_consume_power_handler(the_phy);

               if (the_phy->protocol == SCIC_SDS_PHY_PROTOCOL_SAS)
               {
                  U8 j;
                  SCIC_SDS_PHY_T * current_requester_phy;

                  for (j = 0; j < SCI_MAX_PHYS; j++)
                  {
                     current_requester_phy = this_controller->power_control.requesters[j];

                     //Search the power_control queue to see if there are other phys attached to
                     //the same remote device. If found, take all of them out of await_sas_power state.
                     if (current_requester_phy != NULL &&
                         current_requester_phy != the_phy &&
                         current_requester_phy->phy_type.sas.identify_address_frame_buffer.sas_address.high
                            == the_phy->phy_type.sas.identify_address_frame_buffer.sas_address.high &&
                         current_requester_phy->phy_type.sas.identify_address_frame_buffer.sas_address.low
                            == the_phy->phy_type.sas.identify_address_frame_buffer.sas_address.low)
                     {
                        this_controller->power_control.requesters[j] = NULL;
                        this_controller->power_control.phys_waiting--;
                        scic_sds_phy_consume_power_handler(current_requester_phy);
                     }
                  }
               }
            }
            else
            {
               break;
            }
         }
      }

      // It doesn't matter if the power list is empty, we need to start the
      // timer in case another phy becomes ready.
      scic_sds_controller_power_control_timer_start(this_controller);
   }
}