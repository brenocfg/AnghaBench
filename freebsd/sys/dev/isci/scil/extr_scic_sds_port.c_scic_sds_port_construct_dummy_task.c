#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_7__ {int /*<<< orphan*/  reserved_rni; int /*<<< orphan*/  physical_port_index; int /*<<< orphan*/  owning_controller; } ;
struct TYPE_6__ {int initiator_request; int connection_rate; int do_not_dma_ssp_good_response; int task_phase; scalar_t__ address_modifier; scalar_t__ block_guard_enable; scalar_t__ timeout_enable; scalar_t__ control_frame; scalar_t__ strict_ordering; scalar_t__ link_layer_control; scalar_t__ command_code; int /*<<< orphan*/  remote_node_index; int /*<<< orphan*/  context_type; int /*<<< orphan*/  valid; int /*<<< orphan*/  task_index; int /*<<< orphan*/  protocol_type; int /*<<< orphan*/  logical_port_index; scalar_t__ protocol_engine_index; scalar_t__ priority; scalar_t__ abort; } ;
typedef  TYPE_1__ SCU_TASK_CONTEXT_T ;
typedef  TYPE_2__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCU_TASK_CONTEXT_PROTOCOL_SSP ; 
 int /*<<< orphan*/  SCU_TASK_CONTEXT_TYPE ; 
 int /*<<< orphan*/  SCU_TASK_CONTEXT_VALID ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* scic_sds_controller_get_task_context_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_io_tag_get_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_port_construct_dummy_task(
   SCIC_SDS_PORT_T *this_port,
   U16              tci
)
{
   SCU_TASK_CONTEXT_T * task_context;

   task_context = scic_sds_controller_get_task_context_buffer(this_port->owning_controller, tci);

   memset(task_context, 0, sizeof(SCU_TASK_CONTEXT_T));

   task_context->abort = 0;
   task_context->priority = 0;
   task_context->initiator_request = 1;
   task_context->connection_rate = 1;
   task_context->protocol_engine_index = 0;
   task_context->logical_port_index = this_port->physical_port_index;
   task_context->protocol_type = SCU_TASK_CONTEXT_PROTOCOL_SSP;
   task_context->task_index = scic_sds_io_tag_get_index(tci);
   task_context->valid = SCU_TASK_CONTEXT_VALID;
   task_context->context_type = SCU_TASK_CONTEXT_TYPE;

   task_context->remote_node_index = this_port->reserved_rni;
   task_context->command_code = 0;

   task_context->link_layer_control = 0;
   task_context->do_not_dma_ssp_good_response = 1;
   task_context->strict_ordering = 0;
   task_context->control_frame = 0;
   task_context->timeout_enable = 0;
   task_context->block_guard_enable = 0;

   task_context->address_modifier = 0;

   task_context->task_phase = 0x01;
}