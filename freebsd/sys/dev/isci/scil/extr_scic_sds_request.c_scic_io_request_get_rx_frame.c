#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U32 ;
struct TYPE_4__ {scalar_t__ saved_rx_frame_index; TYPE_1__* owning_controller; } ;
struct TYPE_3__ {int /*<<< orphan*/  uf_control; } ;
typedef  scalar_t__ SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_2__ SCIC_SDS_REQUEST_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SCU_INVALID_FRAME_INDEX ; 
 scalar_t__ SCU_UNSOLICITED_FRAME_BUFFER_SIZE ; 
 int /*<<< orphan*/  scic_sds_unsolicited_frame_control_get_buffer (int /*<<< orphan*/ *,scalar_t__,void**) ; 

void * scic_io_request_get_rx_frame(
   SCI_IO_REQUEST_HANDLE_T  scic_io_request,
   U32                      offset
)
{
   void               * frame_buffer = NULL;
   SCIC_SDS_REQUEST_T * this_request = (SCIC_SDS_REQUEST_T *)scic_io_request;

   ASSERT(offset < SCU_UNSOLICITED_FRAME_BUFFER_SIZE);

   if (this_request->saved_rx_frame_index != SCU_INVALID_FRAME_INDEX)
   {
      scic_sds_unsolicited_frame_control_get_buffer(
         &(this_request->owning_controller->uf_control),
         this_request->saved_rx_frame_index,
         &frame_buffer
      );
   }

   return frame_buffer;
}