#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_5__ parent; int /*<<< orphan*/  starting_substate_machine; int /*<<< orphan*/ * error_counter; int /*<<< orphan*/  phy_type; int /*<<< orphan*/ * sata_timeout_timer; int /*<<< orphan*/  max_negotiated_speed; int /*<<< orphan*/ * link_layer_registers; int /*<<< orphan*/  protocol; int /*<<< orphan*/  bcn_received_while_port_unassigned; int /*<<< orphan*/  phy_index; int /*<<< orphan*/ * owning_port; } ;
typedef  int /*<<< orphan*/  SCIC_SDS_PORT_T ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_PROTOCOL_UNKNOWN ; 
 int /*<<< orphan*/  SCIC_SDS_PHY_STARTING_SUBSTATE_INITIAL ; 
 int /*<<< orphan*/  SCI_SAS_NO_LINK_RATE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_phy_construct (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_phy_initialize_state_logging (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_initialize_state_recording (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_phy_starting_substates ; 
 int /*<<< orphan*/  scic_sds_phy_state_table ; 

void scic_sds_phy_construct(
   SCIC_SDS_PHY_T  *this_phy,
   SCIC_SDS_PORT_T *owning_port,
   U8              phy_index
)
{
   // Call the base constructor first
   // Copy the logger from the port (this could be the dummy port)
   sci_base_phy_construct(
      &this_phy->parent,
      sci_base_object_get_logger(owning_port),
      scic_sds_phy_state_table
      );

   // Copy the rest of the input data to our locals
   this_phy->owning_port = owning_port;
   this_phy->phy_index = phy_index;
   this_phy->bcn_received_while_port_unassigned = FALSE;
   this_phy->protocol = SCIC_SDS_PHY_PROTOCOL_UNKNOWN;
   this_phy->link_layer_registers = NULL;
   this_phy->max_negotiated_speed = SCI_SAS_NO_LINK_RATE;
   this_phy->sata_timeout_timer = NULL;

   // Clear out the identification buffer data
   memset(&this_phy->phy_type, 0, sizeof(this_phy->phy_type));

   // Clear out the error counter data
   memset(this_phy->error_counter, 0, sizeof(this_phy->error_counter));

   // Initialize the substate machines
   sci_base_state_machine_construct(
      &this_phy->starting_substate_machine,
      &this_phy->parent.parent,
      scic_sds_phy_starting_substates,
      SCIC_SDS_PHY_STARTING_SUBSTATE_INITIAL
      );

   #ifdef SCI_LOGGING
   scic_sds_phy_initialize_state_logging(this_phy);
   #endif // SCI_LOGGING

   #ifdef SCIC_DEBUG_ENABLED
   scic_sds_phy_initialize_state_recording(this_phy);
   #endif // SCIC_DEBUG_ENABLED
}