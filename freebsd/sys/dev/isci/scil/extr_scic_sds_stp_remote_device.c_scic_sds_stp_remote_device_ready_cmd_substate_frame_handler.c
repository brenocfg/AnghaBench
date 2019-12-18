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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_3__ {int /*<<< orphan*/  working_request; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 int /*<<< orphan*/  scic_sds_io_request_frame_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_remote_device_ready_cmd_substate_frame_handler(
   SCIC_SDS_REMOTE_DEVICE_T * this_device,
   U32                        frame_index
)
{
   SCI_STATUS status;

   /// The device doe not process any UF received from the hardware while
   /// in this state.  All unsolicited frames are forwarded to the io request
   /// object.
   status = scic_sds_io_request_frame_handler(
      this_device->working_request,
      frame_index
   );

   return status;
}