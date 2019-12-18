#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_6__ {int /*<<< orphan*/  ready_substate_machine; int /*<<< orphan*/  not_ready_reason; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED ; 
 int /*<<< orphan*/  SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_NCQ_ERROR ; 
 int /*<<< orphan*/  SCI_FAILURE_INVALID_STATE ; 
#define  SCU_EVENT_POST_RCN_RELEASE 135 
#define  SCU_EVENT_TL_RNC_SUSPEND_TX 134 
#define  SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_DATA_LEN_ERR 133 
#define  SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_DMASETUP_DIERR 132 
#define  SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_OFFSET_ERR 131 
#define  SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_XFERCNT_ERR 130 
#define  SCU_EVENT_TL_RNC_SUSPEND_TX_RX 129 
#define  SCU_EVENT_TL_RNC_SUSPEND_TX_RX_DONE_PLD_LEN_ERR 128 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_base_state_machine_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_remote_device_general_event_handler (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_remote_device_resume (TYPE_1__*) ; 
 int scu_get_event_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_remote_device_ready_ncq_substate_event_handler(
   SCIC_SDS_REMOTE_DEVICE_T * this_device,
   U32                        event_code
)
{
   SCI_STATUS status;

   status = scic_sds_remote_device_general_event_handler(this_device, event_code);

   switch (scu_get_event_code(event_code))
   {
   case SCU_EVENT_TL_RNC_SUSPEND_TX:
   case SCU_EVENT_TL_RNC_SUSPEND_TX_RX:
      /// @todo We need to decode and understand why the hardware suspended the device.
      ///       The suspension reason was probably due to an SDB error FIS received.
      break;

   case SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_DATA_LEN_ERR:
   case SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_OFFSET_ERR:
   case SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_DMASETUP_DIERR:
   case SCU_EVENT_TL_RNC_SUSPEND_TX_DONE_XFERCNT_ERR:
   case SCU_EVENT_TL_RNC_SUSPEND_TX_RX_DONE_PLD_LEN_ERR:
      this_device->not_ready_reason =
         SCIC_REMOTE_DEVICE_NOT_READY_SATA_SDB_ERROR_FIS_RECEIVED;

      sci_base_state_machine_change_state(
         &this_device->ready_substate_machine,
         SCIC_SDS_STP_REMOTE_DEVICE_READY_SUBSTATE_NCQ_ERROR
      );

      // We have a notification that the driver requested a suspend operation
      // this should not happen.
      SCIC_LOG_WARNING((
         sci_base_object_get_logger(this_device),
         SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
         "SCIC Remote device 0x%x received driver suspend event %x while in ncq ready substate %d\n",
         this_device, event_code, sci_base_state_machine_get_state(&this_device->ready_substate_machine)
      ));

      // Since we didn't expect to get here start the device again.
      status = scic_sds_remote_device_resume(this_device);
      break;

   case SCU_EVENT_POST_RCN_RELEASE:
      /// @todo Do we need to store the suspend state on the device?
      SCIC_LOG_INFO((
         sci_base_object_get_logger(this_device),
         SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
         "SCIC Remote device 0x%x received driver release event %x while in the ready substate %d\n",
         this_device, event_code, sci_base_state_machine_get_state(&this_device->ready_substate_machine)
      ));
      break;

   default:
      // Some other event just log it and continue
      SCIC_LOG_WARNING((
         sci_base_object_get_logger(this_device),
         SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
         "SCIC Remote device 0x%x received driver unexpected event %x while in the ready substate %d\n",
         this_device, event_code, sci_base_state_machine_get_state(&this_device->ready_substate_machine)
      ));

      status = SCI_FAILURE_INVALID_STATE;
      break;
   }

   return status;
}