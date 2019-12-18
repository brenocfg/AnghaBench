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
struct TYPE_6__ {scalar_t__ previous_state_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  destination_state; TYPE_1__ state_machine; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_2__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INITIAL_STATE ; 
 scalar_t__ SCIC_SDS_REMOTE_NODE_CONTEXT_INVALIDATING_STATE ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_UNSPECIFIED ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_deinitialize_state_logging (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_notify_user (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_state_handler_table ; 

__attribute__((used)) static
void scic_sds_remote_node_context_initial_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * rnc;
   rnc = (SCIC_SDS_REMOTE_NODE_CONTEXT_T  *)object;

   SET_STATE_HANDLER(
      rnc,
      scic_sds_remote_node_context_state_handler_table,
      SCIC_SDS_REMOTE_NODE_CONTEXT_INITIAL_STATE
         );

   // Check to see if we have gotten back to the initial state because someone
   // requested to destroy the remote node context object.
   if (
      rnc->state_machine.previous_state_id
         == SCIC_SDS_REMOTE_NODE_CONTEXT_INVALIDATING_STATE
         )
   {
      rnc->destination_state = SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_UNSPECIFIED;

      scic_sds_remote_node_context_notify_user(rnc);

      // Since we are destroying the remote node context deinitialize the state logging
      // should we resume the remote node context the state logging will be reinitialized
      // on the resume handler.
      scic_sds_remote_node_context_deinitialize_state_logging(rnc);
   }
}