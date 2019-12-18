#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * user_callback; int /*<<< orphan*/  destination_state; } ;
typedef  int /*<<< orphan*/  SCI_BASE_OBJECT_T ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_READY_STATE ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_UNSPECIFIED ; 
 int /*<<< orphan*/  SET_STATE_HANDLER (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_notify_user (TYPE_1__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_state_handler_table ; 

__attribute__((used)) static
void scic_sds_remote_node_context_ready_state_enter(
   SCI_BASE_OBJECT_T * object
)
{
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * rnc;
   rnc = (SCIC_SDS_REMOTE_NODE_CONTEXT_T  *)object;

   SET_STATE_HANDLER(
      rnc,
      scic_sds_remote_node_context_state_handler_table,
      SCIC_SDS_REMOTE_NODE_CONTEXT_READY_STATE
         );

   rnc->destination_state = SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_UNSPECIFIED;

   if (rnc->user_callback != NULL)
   {
      scic_sds_remote_node_context_notify_user(rnc);
   }
}