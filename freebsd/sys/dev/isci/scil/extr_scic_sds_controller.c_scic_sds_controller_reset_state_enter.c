#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
struct TYPE_9__ {void* count; } ;
struct TYPE_8__ {void* count; } ;
struct TYPE_10__ {TYPE_2__ address_table; TYPE_1__ buffers; } ;
struct TYPE_11__ {int logical_port_entries; TYPE_3__ uf_control; int /*<<< orphan*/  task_context_entries; int /*<<< orphan*/  remote_node_entries; int /*<<< orphan*/  completion_queue_entries; int /*<<< orphan*/  completion_event_entries; scalar_t__ invalid_phy_mask; int /*<<< orphan*/ * port_table; int /*<<< orphan*/ * phy_table; int /*<<< orphan*/  port_agent; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_4__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int SCIC_SDS_DUMMY_PORT ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_RESET ; 
 int SCI_MAX_PHYS ; 
 int SCI_MAX_PORTS ; 
 int /*<<< orphan*/  SCI_MAX_REMOTE_DEVICES ; 
 int /*<<< orphan*/  SCU_COMPLETION_QUEUE_COUNT ; 
 int /*<<< orphan*/  SCU_EVENT_COUNT ; 
 int /*<<< orphan*/  SCU_IO_REQUEST_COUNT ; 
 void* SCU_UNSOLICITED_FRAME_COUNT ; 
 int /*<<< orphan*/  scic_sds_controller_set_base_state_handlers (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_set_default_config_parameters (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_phy_construct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scic_sds_port_configuration_agent_construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_port_construct (int /*<<< orphan*/ *,int,TYPE_4__*) ; 

__attribute__((used)) static
void scic_sds_controller_reset_state_enter(
   SCI_BASE_OBJECT_T *object
)
{
   U8 index;
   SCIC_SDS_CONTROLLER_T *this_controller;
   this_controller= (SCIC_SDS_CONTROLLER_T *)object;

   scic_sds_controller_set_base_state_handlers(
      this_controller, SCI_BASE_CONTROLLER_STATE_RESET);

   scic_sds_port_configuration_agent_construct(&this_controller->port_agent);

   // Construct the ports for this controller
   for (index = 0; index < (SCI_MAX_PORTS + 1); index++)
   {
      scic_sds_port_construct(
         &this_controller->port_table[index],
         (index == SCI_MAX_PORTS) ? SCIC_SDS_DUMMY_PORT : index,
         this_controller
      );
   }

   // Construct the phys for this controller
   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      // Add all the PHYs to the dummy port
      scic_sds_phy_construct(
         &this_controller->phy_table[index],
         &this_controller->port_table[SCI_MAX_PORTS],
         index
      );
   }

   this_controller->invalid_phy_mask = 0;

   // Set the default maximum values
   this_controller->completion_event_entries      = SCU_EVENT_COUNT;
   this_controller->completion_queue_entries      = SCU_COMPLETION_QUEUE_COUNT;
   this_controller->remote_node_entries           = SCI_MAX_REMOTE_DEVICES;
   this_controller->logical_port_entries          = SCI_MAX_PORTS;
   this_controller->task_context_entries          = SCU_IO_REQUEST_COUNT;
   this_controller->uf_control.buffers.count      = SCU_UNSOLICITED_FRAME_COUNT;
   this_controller->uf_control.address_table.count= SCU_UNSOLICITED_FRAME_COUNT;

   // Initialize the User and OEM parameters to default values.
   scic_sds_controller_set_default_config_parameters(this_controller);
}