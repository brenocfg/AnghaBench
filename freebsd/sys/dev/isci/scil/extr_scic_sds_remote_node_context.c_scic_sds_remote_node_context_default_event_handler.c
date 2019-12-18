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
struct SCIC_SDS_REMOTE_NODE_CONTEXT {int /*<<< orphan*/  state_machine; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SCI_STATUS ;

/* Variables and functions */
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_node_context_default_event_handler(
   struct SCIC_SDS_REMOTE_NODE_CONTEXT * this_rnc,
   U32                                   event_code
)
{
   SCIC_LOG_WARNING((
      sci_base_object_get_logger(this_rnc->device),
      SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
         SCIC_LOG_OBJECT_SMP_REMOTE_TARGET |
         SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
      "SCIC Remote Node Context 0x%x requested to process event 0x%x while in wrong state %d\n",
      this_rnc, event_code, sci_base_state_machine_get_state(&this_rnc->state_machine)
         ));

   return SCI_FAILURE_INVALID_STATE;
}