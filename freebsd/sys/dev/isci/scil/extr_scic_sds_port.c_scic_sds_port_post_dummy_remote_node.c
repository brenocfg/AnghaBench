#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_9__ {TYPE_2__* remote_node_context_table; } ;
struct TYPE_8__ {size_t reserved_rni; int physical_port_index; TYPE_5__* owning_controller; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_valid; } ;
struct TYPE_7__ {TYPE_1__ ssp; } ;
typedef  TYPE_2__ SCU_REMOTE_NODE_CONTEXT_T ;
typedef  TYPE_3__ SCIC_SDS_PORT_T ;

/* Variables and functions */
 int SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT ; 
 int SCU_CONTEXT_COMMAND_POST_RNC_32 ; 
 int SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX_RX ; 
 size_t SCU_DUMMY_INDEX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  scic_cb_stall_execution (int) ; 
 int /*<<< orphan*/  scic_sds_controller_post_request (TYPE_5__*,int) ; 

__attribute__((used)) static
void scic_sds_port_post_dummy_remote_node(
      SCIC_SDS_PORT_T *this_port
)
{
   U32 command;
   SCU_REMOTE_NODE_CONTEXT_T * rnc;

   if (this_port->reserved_rni != SCU_DUMMY_INDEX)
   {
   rnc = &(this_port->owning_controller->remote_node_context_table[this_port->reserved_rni]);

   rnc->ssp.is_valid = TRUE;

   command = (
       (SCU_CONTEXT_COMMAND_POST_RNC_32)
     | (this_port->physical_port_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT)
     | (this_port->reserved_rni)
   );

   scic_sds_controller_post_request(this_port->owning_controller, command);

   scic_cb_stall_execution(10);

   command = (
       (SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX_RX)
     | (this_port->physical_port_index << SCU_CONTEXT_COMMAND_LOGICAL_PORT_SHIFT)
     | (this_port->reserved_rni)
   );

   scic_sds_controller_post_request(this_port->owning_controller, command);
}
}