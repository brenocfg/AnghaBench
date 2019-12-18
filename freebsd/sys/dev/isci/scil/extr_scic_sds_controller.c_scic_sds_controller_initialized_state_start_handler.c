#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
typedef  size_t U16 ;
struct TYPE_17__ {size_t task_context_entries; size_t logical_port_entries; int /*<<< orphan*/  timeout_timer; TYPE_3__* port_table; int /*<<< orphan*/  remote_node_entries; int /*<<< orphan*/  available_remote_nodes; int /*<<< orphan*/  tci_pool; } ;
struct TYPE_16__ {int /*<<< orphan*/  parent; TYPE_2__* state_handlers; } ;
struct TYPE_14__ {scalar_t__ (* start_handler ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_15__ {TYPE_1__ parent; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_CONTROLLER_T ;
typedef  TYPE_4__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_STARTING ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_pool_put (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  scic_cb_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_controller_disable_interrupts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_assign_task_entries (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_controller_enable_port_task_scheduler (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_controller_initialize_completion_queue (TYPE_4__*) ; 
 scalar_t__ scic_sds_controller_initialize_phy_startup (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_controller_initialize_unsolicited_frame_queue (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_controller_ram_initialization (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_controller_start_next_phy (TYPE_4__*) ; 
 scalar_t__ scic_sds_controller_validate_memory_descriptor_table (TYPE_4__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_table_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_controller_initialized_state_start_handler(
   SCI_BASE_CONTROLLER_T * controller,
   U32                     timeout
)
{
   U16                     index;
   SCI_STATUS              result;
   SCIC_SDS_CONTROLLER_T * this_controller;

   this_controller = (SCIC_SDS_CONTROLLER_T *)controller;

   // Make sure that the SCI User filled in the memory descriptor table correctly
   result = scic_sds_controller_validate_memory_descriptor_table(this_controller);

   if (result == SCI_SUCCESS)
   {
      // The memory descriptor list looks good so program the hardware
      scic_sds_controller_ram_initialization(this_controller);
   }

   if (SCI_SUCCESS == result)
   {
      // Build the TCi free pool
      sci_pool_initialize(this_controller->tci_pool);
      for (index = 0; index < this_controller->task_context_entries; index++)
      {
         sci_pool_put(this_controller->tci_pool, index);
      }

      // Build the RNi free pool
      scic_sds_remote_node_table_initialize(
         &this_controller->available_remote_nodes,
         this_controller->remote_node_entries
      );
   }

   if (SCI_SUCCESS == result)
   {
      // Before anything else lets make sure we will not be interrupted
      // by the hardware.
      scic_controller_disable_interrupts(controller);

      // Enable the port task scheduler
      scic_sds_controller_enable_port_task_scheduler(this_controller);

      // Assign all the task entries to this controller physical function
      scic_sds_controller_assign_task_entries(this_controller);

      // Now initialze the completion queue
      scic_sds_controller_initialize_completion_queue(this_controller);

      // Initialize the unsolicited frame queue for use
      scic_sds_controller_initialize_unsolicited_frame_queue(this_controller);

      // Setup the phy start timer
      result = scic_sds_controller_initialize_phy_startup(this_controller);
   }

   // Start all of the ports on this controller
   for (
          index = 0;
          (index < this_controller->logical_port_entries) && (result == SCI_SUCCESS);
          index++
       )
   {
      result = this_controller->port_table[index].
         state_handlers->parent.start_handler(&this_controller->port_table[index].parent);
   }

   if (SCI_SUCCESS == result)
   {
      scic_sds_controller_start_next_phy(this_controller);

      // See if the user requested to timeout this operation.
      if (timeout != 0)
         scic_cb_timer_start(controller, this_controller->timeout_timer, timeout);

      sci_base_state_machine_change_state(
         scic_sds_controller_get_base_state_machine(this_controller),
         SCI_BASE_CONTROLLER_STATE_STARTING
      );
   }

   return result;
}