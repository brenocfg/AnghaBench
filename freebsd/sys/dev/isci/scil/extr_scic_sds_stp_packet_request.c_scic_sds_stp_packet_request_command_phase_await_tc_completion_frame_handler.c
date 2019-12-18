#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  d2h_reg_fis; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_STP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_TASK_DONE_CHECK_RESPONSE ; 
 int /*<<< orphan*/  SCU_TASK_DONE_GOOD ; 
 int /*<<< orphan*/  scic_sds_request_set_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ scic_sds_stp_packet_request_command_phase_common_frame_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_stp_packet_request_process_status_fis (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_packet_request_command_phase_await_tc_completion_frame_handler(
   SCIC_SDS_REQUEST_T * request,
   U32                  frame_index
)
{
   SCIC_SDS_STP_REQUEST_T * this_request = (SCIC_SDS_STP_REQUEST_T *)request;

   SCI_STATUS status =
      scic_sds_stp_packet_request_command_phase_common_frame_handler(
         request, frame_index);

   if (status == SCI_SUCCESS)
   {
      // The command has completed with error status from target device.
      status = scic_sds_stp_packet_request_process_status_fis(
         request, &this_request->d2h_reg_fis);

      if (status != SCI_SUCCESS)
      {
         scic_sds_request_set_status(
            &this_request->parent,
            SCU_TASK_DONE_CHECK_RESPONSE,
            status
         );
      }
      else
         scic_sds_request_set_status(
            &this_request->parent, SCU_TASK_DONE_GOOD, SCI_SUCCESS
         );
   }

   return status;
}