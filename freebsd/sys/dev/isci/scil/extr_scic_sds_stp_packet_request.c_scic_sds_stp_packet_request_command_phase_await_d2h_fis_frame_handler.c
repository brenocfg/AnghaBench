#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_8__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_10__ {TYPE_1__ parent; } ;
struct TYPE_9__ {int /*<<< orphan*/  d2h_reg_fis; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_2__ SCIC_SDS_STP_REQUEST_T ;
typedef  TYPE_3__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_COMPLETED ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_TASK_DONE_CHECK_RESPONSE ; 
 int /*<<< orphan*/  SCU_TASK_DONE_GOOD ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_request_set_status (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ scic_sds_stp_packet_request_command_phase_common_frame_handler (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_stp_packet_request_process_status_fis (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_packet_request_command_phase_await_d2h_fis_frame_handler(
   SCIC_SDS_REQUEST_T * request,
   U32                  frame_index
)
{
   SCI_STATUS status =
      scic_sds_stp_packet_request_command_phase_common_frame_handler(
         request, frame_index);

   SCIC_SDS_STP_REQUEST_T * this_request = (SCIC_SDS_STP_REQUEST_T *)request;

   if (status == SCI_SUCCESS)
   {
       // The command has completed with error status from target device.
      status = scic_sds_stp_packet_request_process_status_fis(
         request, &this_request->d2h_reg_fis);

      if (status != SCI_SUCCESS)
      {
         scic_sds_request_set_status(
            request,
            SCU_TASK_DONE_CHECK_RESPONSE,
            status
         );
      }
      else
         scic_sds_request_set_status(
            request, SCU_TASK_DONE_GOOD, SCI_SUCCESS
         );

      //Always complete the NON_DATA command right away, no need to delay completion
      //even an error status fis came from target device.
      sci_base_state_machine_change_state(
         &request->parent.state_machine,
         SCI_BASE_REQUEST_STATE_COMPLETED
      );
   }

   return status;
}