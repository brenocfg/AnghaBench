#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_6__ {int /*<<< orphan*/  error; } ;
struct TYPE_7__ {size_t remote_node_entries; int /*<<< orphan*/ ** device_table; int /*<<< orphan*/ * phy_table; int /*<<< orphan*/ ** io_request_table; TYPE_1__ parent; } ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;
typedef  TYPE_2__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCIC_LOG_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
 int /*<<< orphan*/  SCI_CONTROLLER_FATAL_MEMORY_ERROR ; 
 int /*<<< orphan*/ * SCI_INVALID_HANDLE ; 
#define  SCU_EVENT_SPECIFIC_IT_NEXUS_TIMEOUT 142 
#define  SCU_EVENT_SPECIFIC_SMP_RESPONSE_NO_PE 141 
#define  SCU_EVENT_SPECIFIC_TASK_TIMEOUT 140 
#define  SCU_EVENT_TYPE_BROADCAST_CHANGE 139 
#define  SCU_EVENT_TYPE_ERR_CNT_EVENT 138 
#define  SCU_EVENT_TYPE_FATAL_MEMORY_ERROR 137 
#define  SCU_EVENT_TYPE_OSSP_EVENT 136 
#define  SCU_EVENT_TYPE_PTX_SCHEDULE_EVENT 135 
#define  SCU_EVENT_TYPE_RNC_OPS_MISC 134 
#define  SCU_EVENT_TYPE_RNC_SUSPEND_TX 133 
#define  SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX 132 
#define  SCU_EVENT_TYPE_SMU_COMMAND_ERROR 131 
#define  SCU_EVENT_TYPE_SMU_ERROR 130 
#define  SCU_EVENT_TYPE_SMU_PCQ_ERROR 129 
#define  SCU_EVENT_TYPE_TRANSPORT_ERROR 128 
 size_t SCU_GET_COMPLETION_INDEX (size_t) ; 
 size_t SCU_GET_PROTOCOL_ENGINE_INDEX (size_t) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_2__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_2__*) ; 
 int /*<<< orphan*/  scic_sds_io_request_event_handler (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  scic_sds_phy_event_handler (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  scic_sds_remote_device_event_handler (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  scu_get_event_specifier (size_t) ; 
 int scu_get_event_type (size_t) ; 

__attribute__((used)) static
void scic_sds_controller_event_completion(
   SCIC_SDS_CONTROLLER_T *this_controller,
   U32                   completion_entry
)
{
   U32 index;
   SCIC_SDS_REQUEST_T       *io_request;
   SCIC_SDS_REMOTE_DEVICE_T *device;
   SCIC_SDS_PHY_T           *phy;

   index = SCU_GET_COMPLETION_INDEX(completion_entry);

   switch (scu_get_event_type(completion_entry))
   {
   case SCU_EVENT_TYPE_SMU_COMMAND_ERROR:
      /// @todo The driver did something wrong and we need to fix the condtion.
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller 0x%x received SMU command error 0x%x\n",
         this_controller, completion_entry
      ));
      break;

   case SCU_EVENT_TYPE_FATAL_MEMORY_ERROR:
       // report fatal memory error
       this_controller->parent.error = SCI_CONTROLLER_FATAL_MEMORY_ERROR;

       sci_base_state_machine_change_state(
          scic_sds_controller_get_base_state_machine(this_controller),
          SCI_BASE_CONTROLLER_STATE_FAILED
       );

       //continue as in following events
   case SCU_EVENT_TYPE_SMU_PCQ_ERROR:
   case SCU_EVENT_TYPE_SMU_ERROR:
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller 0x%x received fatal controller event 0x%x\n",
         this_controller, completion_entry
      ));
      break;

   case SCU_EVENT_TYPE_TRANSPORT_ERROR:
      io_request = this_controller->io_request_table[index];
      scic_sds_io_request_event_handler(io_request, completion_entry);
      break;

   case SCU_EVENT_TYPE_PTX_SCHEDULE_EVENT:
      switch (scu_get_event_specifier(completion_entry))
      {
      case SCU_EVENT_SPECIFIC_SMP_RESPONSE_NO_PE:
      case SCU_EVENT_SPECIFIC_TASK_TIMEOUT:
         io_request = this_controller->io_request_table[index];
         if (io_request != SCI_INVALID_HANDLE)
         {
            scic_sds_io_request_event_handler(io_request, completion_entry);
         }
         else
         {
            SCIC_LOG_WARNING((
               sci_base_object_get_logger(this_controller),
               SCIC_LOG_OBJECT_CONTROLLER |
               SCIC_LOG_OBJECT_SMP_IO_REQUEST |
               SCIC_LOG_OBJECT_SSP_IO_REQUEST |
               SCIC_LOG_OBJECT_STP_IO_REQUEST,
               "SCIC Controller 0x%x received event 0x%x for io request object that doesnt exist.\n",
               this_controller, completion_entry
            ));
         }
         break;

      case SCU_EVENT_SPECIFIC_IT_NEXUS_TIMEOUT:
         device = this_controller->device_table[index];
         if (device != SCI_INVALID_HANDLE)
         {
            scic_sds_remote_device_event_handler(device, completion_entry);
         }
         else
         {
            SCIC_LOG_WARNING((
               sci_base_object_get_logger(this_controller),
               SCIC_LOG_OBJECT_CONTROLLER |
               SCIC_LOG_OBJECT_SMP_REMOTE_TARGET |
               SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
               SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
               "SCIC Controller 0x%x received event 0x%x for remote device object that doesnt exist.\n",
               this_controller, completion_entry
            ));
         }
         break;
      }
      break;

   case SCU_EVENT_TYPE_BROADCAST_CHANGE:
      // direct the broadcast change event to the phy first and then let
      // the phy redirect the broadcast change to the port object
   case SCU_EVENT_TYPE_ERR_CNT_EVENT:
      // direct error counter event to the phy object since that is where
      // we get the event notification.  This is a type 4 event.
   case SCU_EVENT_TYPE_OSSP_EVENT:
      index = SCU_GET_PROTOCOL_ENGINE_INDEX(completion_entry);
      phy = &this_controller->phy_table[index];
      scic_sds_phy_event_handler(phy, completion_entry);
      break;

   case SCU_EVENT_TYPE_RNC_SUSPEND_TX:
   case SCU_EVENT_TYPE_RNC_SUSPEND_TX_RX:
   case SCU_EVENT_TYPE_RNC_OPS_MISC:
      if (index < this_controller->remote_node_entries)
      {
         device = this_controller->device_table[index];

         if (device != NULL)
         {
            scic_sds_remote_device_event_handler(device, completion_entry);
         }
      }
      else
      {
         SCIC_LOG_ERROR((
            sci_base_object_get_logger(this_controller),
            SCIC_LOG_OBJECT_CONTROLLER |
            SCIC_LOG_OBJECT_SMP_REMOTE_TARGET |
            SCIC_LOG_OBJECT_SSP_REMOTE_TARGET |
            SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
            "SCIC Controller 0x%x received event 0x%x for remote device object 0x%0x that doesnt exist.\n",
            this_controller, completion_entry, index
         ));
      }
      break;

   default:
      SCIC_LOG_WARNING((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC Controller received unknown event code %x\n",
         completion_entry
      ));
      break;
   }
}