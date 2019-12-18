#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ destination_state; void* user_cookie; int /*<<< orphan*/  user_callback; } ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_FINAL ; 
 scalar_t__ SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_READY ; 

__attribute__((used)) static
void scic_sds_remote_node_context_setup_to_resume(
   SCIC_SDS_REMOTE_NODE_CONTEXT_T         * this_rnc,
   SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK   the_callback,
   void                                   * callback_parameter
)
{
   if (this_rnc->destination_state != SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_FINAL)
   {
      this_rnc->destination_state = SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_READY;
      this_rnc->user_callback     = the_callback;
      this_rnc->user_cookie       = callback_parameter;
   }
}