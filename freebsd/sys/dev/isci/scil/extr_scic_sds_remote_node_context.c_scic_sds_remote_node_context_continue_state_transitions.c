#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ destination_state; int /*<<< orphan*/  user_cookie; int /*<<< orphan*/  user_callback; TYPE_1__* state_handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* resume_handler ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_READY ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void scic_sds_remote_node_context_continue_state_transitions(
   SCIC_SDS_REMOTE_NODE_CONTEXT_T * rnc
)
{
   if (rnc->destination_state == SCIC_SDS_REMOTE_NODE_DESTINATION_STATE_READY)
   {
      rnc->state_handlers->resume_handler(
         rnc, rnc->user_callback, rnc->user_cookie
            );
   }
}