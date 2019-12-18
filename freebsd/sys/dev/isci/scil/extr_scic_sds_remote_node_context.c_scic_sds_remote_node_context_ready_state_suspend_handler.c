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
typedef  scalar_t__ U32 ;
struct TYPE_3__ {int /*<<< orphan*/  state_machine; int /*<<< orphan*/  device; scalar_t__ suspension_code; void* user_cookie; int /*<<< orphan*/  user_callback; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_AWAIT_SUSPENSION_STATE ; 
 scalar_t__ SCI_SOFTWARE_SUSPENSION ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_post_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_node_context_ready_state_suspend_handler(
   SCIC_SDS_REMOTE_NODE_CONTEXT_T         * this_rnc,
   U32                                      suspend_type,
   SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK   the_callback,
   void                                   * callback_parameter
)
{
   this_rnc->user_callback   = the_callback;
   this_rnc->user_cookie     = callback_parameter;
   this_rnc->suspension_code = suspend_type;

   if (suspend_type == SCI_SOFTWARE_SUSPENSION)
   {
      scic_sds_remote_device_post_request(
         this_rnc->device,
         SCU_CONTEXT_COMMAND_POST_RNC_SUSPEND_TX
            );
   }

   sci_base_state_machine_change_state(
      &this_rnc->state_machine,
      SCIC_SDS_REMOTE_NODE_CONTEXT_AWAIT_SUSPENSION_STATE
         );

   return SCI_SUCCESS;
}