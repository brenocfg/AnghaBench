#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_13__ {int /*<<< orphan*/  logger; } ;
struct TYPE_9__ {int /*<<< orphan*/  logger; } ;
struct TYPE_10__ {TYPE_1__ parent; } ;
struct TYPE_12__ {TYPE_2__ parent; } ;
struct TYPE_11__ {int /*<<< orphan*/  state_machine; TYPE_7__ parent; int /*<<< orphan*/  destination_state; TYPE_4__* device; int /*<<< orphan*/  remote_node_index; } ;
typedef  TYPE_3__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;
typedef  TYPE_4__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INITIAL_STATE ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_UNSPECIFIED ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sci_base_state_machine_construct (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_state_table ; 

void scic_sds_remote_node_context_construct(
   SCIC_SDS_REMOTE_DEVICE_T       * device,
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * rnc,
   U16                              remote_node_index
      )
{
   memset (rnc, 0, sizeof(SCIC_SDS_REMOTE_NODE_CONTEXT_T) );

   rnc->remote_node_index = remote_node_index;
   rnc->device            = device;
   rnc->destination_state = SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_UNSPECIFIED;

   rnc->parent.logger = device->parent.parent.logger;

   sci_base_state_machine_construct(
      &rnc->state_machine,
      &rnc->parent,
      scic_sds_remote_node_context_state_table,
      SCIC_SDS_REMOTE_NODE_CONTEXT_INITIAL_STATE
         );

   sci_base_state_machine_start(&rnc->state_machine);

   // State logging initialization takes place late for the remote node context
   // see the resume state handler for the initial state.
}