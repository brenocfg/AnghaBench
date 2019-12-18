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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_4__ {int /*<<< orphan*/  rnc; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
 int /*<<< orphan*/  SCI_SOFTWARE_SUSPENSION ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_EVENT_IT_NEXUS_TIMEOUT ; 
#define  SCU_EVENT_TYPE_PTX_SCHEDULE_EVENT 131 
#define  SCU_EVENT_TYPE_RNC_OPS_MISC 130 
#define  SCU_EVENT_TYPE_RNC_SUSPEND_TX 129 
#define  SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX 128 
 int /*<<< orphan*/  scic_sds_emit_event_log_message (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_event_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_node_context_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scu_get_event_code (int /*<<< orphan*/ ) ; 
 int scu_get_event_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS  scic_sds_remote_device_core_event_handler(
   SCIC_SDS_REMOTE_DEVICE_T *this_device,
   U32                       event_code,
   BOOL                      is_ready_state
)
{
   SCI_STATUS status;

   switch (scu_get_event_type(event_code))
   {
   case SCU_EVENT_TYPE_RNC_OPS_MISC:
   case SCU_EVENT_TYPE_RNC_SUSPEND_TX:
   case SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX:
      status = scic_sds_remote_node_context_event_handler(this_device->rnc, event_code);
   break;
   case SCU_EVENT_TYPE_PTX_SCHEDULE_EVENT:

       if( scu_get_event_code(event_code) == SCU_EVENT_IT_NEXUS_TIMEOUT )
       {
           status = SCI_SUCCESS;

           // Suspend the associated RNC
           scic_sds_remote_node_context_suspend( this_device->rnc,
                                                 SCI_SOFTWARE_SUSPENSION,
                                                 NULL, NULL );

           scic_sds_emit_event_log_message(
              this_device, event_code,
                   (is_ready_state)
            ? "I_T_Nexus_Timeout event"
            : "I_T_Nexus_Timeout event in wrong state",
                   is_ready_state );

           break;
       }
       // Else, fall through and treat as unhandled...

   default:
      scic_sds_emit_event_log_message( this_device, event_code,
                                       (is_ready_state)
                                          ? "unexpected event"
                                          : "unexpected event in wrong state",
                                       is_ready_state );
      status = SCI_FAILURE_INVALID_STATE;
   break;
   }

   return status;
}