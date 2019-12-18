#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_TX_RX_SUSPENDED_STATE ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_continue_state_transitions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_state_handler_table ; 

__attribute__((used)) static
void scic_sds_remote_node_context_tx_rx_suspended_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * rnc;
   rnc = (SCIC_SDS_REMOTE_NODE_CONTEXT_T  *)object;

   SET_STATE_HANDLER(
      rnc,
      scic_sds_remote_node_context_state_handler_table,
      SCIC_SDS_REMOTE_NODE_CONTEXT_TX_RX_SUSPENDED_STATE
         );

   scic_sds_remote_node_context_continue_state_transitions(rnc);
}