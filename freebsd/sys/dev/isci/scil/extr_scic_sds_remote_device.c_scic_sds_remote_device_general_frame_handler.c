#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_13__ {int /*<<< orphan*/  uf_control; } ;
struct TYPE_12__ {TYPE_1__* state_handlers; int /*<<< orphan*/ * target_device; } ;
struct TYPE_11__ {int /*<<< orphan*/  tag; } ;
struct TYPE_10__ {scalar_t__ (* frame_handler ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_2__ SCI_SSP_FRAME_HEADER_T ;
typedef  TYPE_3__ SCIC_SDS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REMOTE_DEVICE_T ;

/* Variables and functions */
 TYPE_3__* SCI_INVALID_HANDLE ; 
 scalar_t__ SCI_SUCCESS ; 
 TYPE_3__* scic_sds_controller_get_io_request_from_tag (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_release_frame (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* scic_sds_remote_device_get_controller (int /*<<< orphan*/ *) ; 
 scalar_t__ scic_sds_unsolicited_frame_control_get_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

SCI_STATUS scic_sds_remote_device_general_frame_handler(
   SCIC_SDS_REMOTE_DEVICE_T *this_device,
   U32                       frame_index
)
{
   SCI_STATUS result;
   SCI_SSP_FRAME_HEADER_T *frame_header;
   SCIC_SDS_REQUEST_T     *io_request;

   result = scic_sds_unsolicited_frame_control_get_header(
      &(scic_sds_remote_device_get_controller(this_device)->uf_control),
      frame_index,
      (void **)&frame_header
   );

   if (SCI_SUCCESS == result)
   {
      io_request = scic_sds_controller_get_io_request_from_tag(
         scic_sds_remote_device_get_controller(this_device), frame_header->tag);

      if (  (io_request == SCI_INVALID_HANDLE)
         || (io_request->target_device != this_device) )
      {
         // We could not map this tag to a valid IO request
         // Just toss the frame and continue
         scic_sds_controller_release_frame(
            scic_sds_remote_device_get_controller(this_device), frame_index
         );
      }
      else
      {
         // The IO request is now in charge of releasing the frame
         result = io_request->state_handlers->frame_handler(
                                                    io_request, frame_index);
      }
   }

   return result;
}