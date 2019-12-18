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
typedef  size_t U32 ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** phy_table; int /*<<< orphan*/ * port_task_scheduler_registers; int /*<<< orphan*/  timer_handle; void* reserved_tci; void* reserved_rni; scalar_t__ assigned_device_count; scalar_t__ started_request_count; int /*<<< orphan*/ * owning_controller; scalar_t__ enabled_phy_mask; scalar_t__ active_phy_mask; int /*<<< orphan*/  physical_port_index; int /*<<< orphan*/  logical_port_index; TYPE_5__ parent; } ;
typedef  TYPE_1__ SCIC_SDS_PORT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_DUMMY_PORT ; 
 int /*<<< orphan*/  SCIC_SDS_PORT_READY_SUBSTATE_WAITING ; 
 int /*<<< orphan*/  SCI_INVALID_HANDLE ; 
 size_t SCI_MAX_PHYS ; 
 void* SCU_DUMMY_INDEX ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sci_base_port_construct (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_port_get_ready_substate_machine (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_initialize_state_logging (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_port_ready_substate_table ; 
 int /*<<< orphan*/  scic_sds_port_state_table ; 

void scic_sds_port_construct(
   SCIC_SDS_PORT_T         *this_port,
   U8                      port_index,
   SCIC_SDS_CONTROLLER_T   *owning_controller
)
{
   U32 index;

   sci_base_port_construct(
      &this_port->parent,
      sci_base_object_get_logger(owning_controller),
      scic_sds_port_state_table
   );

   sci_base_state_machine_construct(
      scic_sds_port_get_ready_substate_machine(this_port),
      &this_port->parent.parent,
      scic_sds_port_ready_substate_table,
      SCIC_SDS_PORT_READY_SUBSTATE_WAITING
   );

   scic_sds_port_initialize_state_logging(this_port);

   this_port->logical_port_index  = SCIC_SDS_DUMMY_PORT;
   this_port->physical_port_index = port_index;
   this_port->active_phy_mask     = 0;
   this_port->enabled_phy_mask    = 0;
   this_port->owning_controller = owning_controller;

   this_port->started_request_count = 0;
   this_port->assigned_device_count = 0;

   this_port->reserved_rni = SCU_DUMMY_INDEX;
   this_port->reserved_tci = SCU_DUMMY_INDEX;

   this_port->timer_handle = SCI_INVALID_HANDLE;

   this_port->port_task_scheduler_registers = NULL;

   for (index = 0; index < SCI_MAX_PHYS; index++)
   {
      this_port->phy_table[index] = NULL;
   }
}