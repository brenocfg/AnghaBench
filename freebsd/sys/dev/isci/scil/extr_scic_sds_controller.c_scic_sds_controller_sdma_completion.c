#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t U32 ;
struct TYPE_5__ {int /*<<< orphan*/ ** device_table; int /*<<< orphan*/ ** io_request_table; } ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;
typedef  TYPE_1__ SCIC_SDS_CONTROLLER_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int SCIC_LOG_OBJECT_CONTROLLER ; 
 int SCIC_LOG_OBJECT_SMP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_SMP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_SSP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_SSP_REMOTE_TARGET ; 
 int SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int SCIC_LOG_OBJECT_STP_REMOTE_TARGET ; 
 int /*<<< orphan*/  SCI_BASE_CONTROLLER_STATE_FAILED ; 
#define  SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_RNC 132 
#define  SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_TC 131 
#define  SCU_CONTEXT_COMMAND_REQUEST_TYPE_OTHER_RNC 130 
#define  SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_RNC 129 
#define  SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC 128 
 size_t SCU_GET_COMPLETION_INDEX (size_t) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_get_base_state_machine (TYPE_1__*) ; 
 int scu_get_command_request_type (size_t) ; 

__attribute__((used)) static
void scic_sds_controller_sdma_completion(
   SCIC_SDS_CONTROLLER_T *this_controller,
   U32                   completion_entry
)
{
   U32 index;
   SCIC_SDS_REQUEST_T       *io_request;
   SCIC_SDS_REMOTE_DEVICE_T *device;

   index = SCU_GET_COMPLETION_INDEX(completion_entry);

   switch (scu_get_command_request_type(completion_entry))
   {
   case SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC:
   case SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_TC:
      io_request = this_controller->io_request_table[index];
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
           SCIC_LOG_OBJECT_CONTROLLER
         | SCIC_LOG_OBJECT_SMP_IO_REQUEST
         | SCIC_LOG_OBJECT_SSP_IO_REQUEST
         | SCIC_LOG_OBJECT_STP_IO_REQUEST,
         "SCIC SDS Completion type SDMA %x for io request %x\n",
         completion_entry,
         io_request
      ));
      /// @todo For a post TC operation we need to fail the IO request
      break;

   case SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_RNC:
   case SCU_CONTEXT_COMMAND_REQUEST_TYPE_OTHER_RNC:
   case SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_RNC:
      device = this_controller->device_table[index];
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
           SCIC_LOG_OBJECT_CONTROLLER
         | SCIC_LOG_OBJECT_SSP_REMOTE_TARGET
         | SCIC_LOG_OBJECT_SMP_REMOTE_TARGET
         | SCIC_LOG_OBJECT_STP_REMOTE_TARGET,
         "SCIC SDS Completion type SDMA %x for remote device %x\n",
         completion_entry,
         device
      ));
      /// @todo For a port RNC operation we need to fail the device
      break;

   default:
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_controller),
         SCIC_LOG_OBJECT_CONTROLLER,
         "SCIC SDS Completion unknown SDMA completion type %x\n",
         completion_entry
      ));
      break;
   }

   /// This is an unexpected completion type and is un-recoverable
   /// Transition to the failed state and wait for a controller reset
   sci_base_state_machine_change_state(
      scic_sds_controller_get_base_state_machine(this_controller),
      SCI_BASE_CONTROLLER_STATE_FAILED
   );
}