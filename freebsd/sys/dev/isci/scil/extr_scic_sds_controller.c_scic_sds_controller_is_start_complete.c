#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U8 ;
struct TYPE_16__ {scalar_t__ phy_ready_mask; scalar_t__ phy_configured_mask; } ;
struct TYPE_11__ {scalar_t__ mode_type; } ;
struct TYPE_12__ {TYPE_1__ controller; } ;
struct TYPE_13__ {TYPE_2__ sds1; } ;
struct TYPE_18__ {TYPE_6__ port_agent; TYPE_3__ oem_parameters; TYPE_7__* phy_table; } ;
struct TYPE_14__ {scalar_t__ current_state_id; } ;
struct TYPE_15__ {TYPE_4__ state_machine; } ;
struct TYPE_17__ {scalar_t__ is_in_link_training; TYPE_5__ parent; } ;
typedef  TYPE_7__ SCIC_SDS_PHY_T ;
typedef  TYPE_8__ SCIC_SDS_CONTROLLER_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE ; 
 scalar_t__ SCIC_PORT_MANUAL_CONFIGURATION_MODE ; 
 scalar_t__ SCI_BASE_PHY_STATE_INITIAL ; 
 scalar_t__ SCI_BASE_PHY_STATE_STARTING ; 
 scalar_t__ SCI_BASE_PHY_STATE_STOPPED ; 
 scalar_t__ SCI_INVALID_HANDLE ; 
 size_t SCI_MAX_PHYS ; 
 scalar_t__ TRUE ; 
 scalar_t__ scic_sds_phy_get_port (TYPE_7__*) ; 

BOOL scic_sds_controller_is_start_complete(
   SCIC_SDS_CONTROLLER_T *this_controller
)
{
   U8 index;

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      SCIC_SDS_PHY_T *the_phy = & this_controller->phy_table[index];

      if (
            (
                  this_controller->oem_parameters.sds1.controller.mode_type
               == SCIC_PORT_AUTOMATIC_CONFIGURATION_MODE
            )
         || (
               (
                  this_controller->oem_parameters.sds1.controller.mode_type
               == SCIC_PORT_MANUAL_CONFIGURATION_MODE
               )
            && (scic_sds_phy_get_port(the_phy) != SCI_INVALID_HANDLE)
            )
         )
      {
         /**
          * The controller start operation is complete if and only
          * if:
          * - all links have been given an opportunity to start
          * - have no indication of a connected device
          * - have an indication of a connected device and it has
          *   finished the link training process.
          */
        if (
               (
                  (the_phy->is_in_link_training == FALSE)
               && (the_phy->parent.state_machine.current_state_id
                   == SCI_BASE_PHY_STATE_INITIAL)
               )
            || (
                  (the_phy->is_in_link_training == FALSE)
               && (the_phy->parent.state_machine.current_state_id
                   == SCI_BASE_PHY_STATE_STOPPED)
               )
            || (
                  (the_phy->is_in_link_training == TRUE)
               && (the_phy->parent.state_machine.current_state_id
                   == SCI_BASE_PHY_STATE_STARTING)
               )
            || (
                  this_controller->port_agent.phy_ready_mask
                  != this_controller->port_agent.phy_configured_mask
               )
            )
         {
            return FALSE;
         }
      }
   }

   return TRUE;
}