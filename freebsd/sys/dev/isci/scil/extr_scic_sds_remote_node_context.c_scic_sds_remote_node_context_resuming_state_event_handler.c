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
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_READY_STATE ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 scalar_t__ SCU_EVENT_POST_RCN_RELEASE ; 
#define  SCU_EVENT_TYPE_RNC_SUSPEND_TX 129 
#define  SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX 128 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 
 scalar_t__ scu_get_event_code (int /*<<< orphan*/ ) ; 
 int scu_get_event_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_remote_node_context_resuming_state_event_handler(
   struct SCIC_SDS_REMOTE_NODE_CONTEXT * this_rnc,
   U32                                   event_code
)
{
   SCI_STATUS status;

   if (scu_get_event_code(event_code) == SCU_EVENT_POST_RCN_RELEASE)
   {
      status = SCI_SUCCESS;

      sci_base_state_machine_change_state(
         &this_rnc->state_machine,
         SCIC_SDS_REMOTE_NODE_CONTEXT_READY_STATE
            );
   }
   else
   {
      switch (scu_get_event_type(event_code))
      {
         case SCU_EVENT_TYPE_RNC_SUSPEND_TX:
         case SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX:
            // We really dont care if the hardware is going to suspend
            // the device since it's being resumed anyway
            SCIC_LOG_INFO((
               sci_base_object_get_logger(this_rnc->device),
               SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
                  SCIC_LOG_OBJECT_SMP_REMOTE_TARGET |
                  SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
               "SCIC Remote Node Context 0x%x was suspeneded by hardware while being resumed.\n",
               this_rnc
                  ));
            status = SCI_SUCCESS;
            break;

         default:
            SCIC_LOG_WARNING((
               sci_base_object_get_logger(this_rnc->device),
               SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
                  SCIC_LOG_OBJECT_SMP_REMOTE_TARGET |
                  SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
               "SCIC Remote Node Context 0x%x requested to process event 0x%x while in state %d.\n",
               this_rnc, event_code, sci_base_state_machine_get_state(&this_rnc->state_machine)
                  ));
            status = SCI_FAILURE;
            break;
      }
   }

   return status;
}