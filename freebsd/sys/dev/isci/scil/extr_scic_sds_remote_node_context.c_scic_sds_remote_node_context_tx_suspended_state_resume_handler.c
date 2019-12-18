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
struct TYPE_13__ {int /*<<< orphan*/  is_direct_attached; } ;
struct TYPE_12__ {int /*<<< orphan*/  state_machine; TYPE_7__* device; } ;
struct TYPE_9__ {int attached_stp_target; } ;
struct TYPE_10__ {TYPE_1__ bits; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
typedef  TYPE_3__ SMP_DISCOVER_RESPONSE_PROTOCOLS_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_4__ SCIC_SDS_REMOTE_NODE_CONTEXT_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INVALIDATING_STATE ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_RESUMING_STATE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_remote_device_get_protocols (TYPE_7__*,TYPE_3__*) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_setup_to_resume (TYPE_4__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_node_context_tx_suspended_state_resume_handler(
   SCIC_SDS_REMOTE_NODE_CONTEXT_T         * this_rnc,
   SCIC_SDS_REMOTE_NODE_CONTEXT_CALLBACK   the_callback,
   void                                   * callback_parameter
)
{
   SMP_DISCOVER_RESPONSE_PROTOCOLS_T protocols;

   scic_sds_remote_node_context_setup_to_resume(
      this_rnc, the_callback, callback_parameter
         );

   // If this is an expander attached SATA device we must invalidate
   // and repost the RNC since this is the only way to clear the
   // TCi to NCQ tag mapping table for the RNi
   // All other device types we can just resume.
   scic_remote_device_get_protocols(this_rnc->device, &protocols);

   if (
      (protocols.u.bits.attached_stp_target == 1)
         && !(this_rnc->device->is_direct_attached)
         )
   {
      sci_base_state_machine_change_state(
         &this_rnc->state_machine,
         SCIC_SDS_REMOTE_NODE_CONTEXT_INVALIDATING_STATE
            );
   }
   else
   {
      sci_base_state_machine_change_state(
         &this_rnc->state_machine,
         SCIC_SDS_REMOTE_NODE_CONTEXT_RESUMING_STATE
            );
   }

   return SCI_SUCCESS;
}