#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
typedef  scalar_t__ U16 ;
struct TYPE_15__ {int /*<<< orphan*/  uf_control; } ;
struct TYPE_14__ {scalar_t__ fis_type; } ;
struct TYPE_13__ {scalar_t__ transfter_count; } ;
struct TYPE_11__ {int /*<<< orphan*/  started_substate_machine; TYPE_7__* owning_controller; } ;
struct TYPE_9__ {scalar_t__ device_preferred_cdb_length; } ;
struct TYPE_10__ {TYPE_1__ packet; } ;
struct TYPE_12__ {TYPE_3__ parent; TYPE_2__ type; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_4__ SCIC_SDS_STP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  TYPE_5__ SATA_FIS_PIO_SETUP_T ;
typedef  TYPE_6__ SATA_FIS_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SATA_FIS_TYPE_PIO_SETUP ; 
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_STP_PACKET_REQUEST_STARTED_COMMAND_PHASE_AWAIT_TC_COMPLETION_SUBSTATE ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_release_frame (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_unsolicited_frame_control_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ scic_sds_unsolicited_frame_control_get_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_packet_request_packet_phase_await_pio_setup_frame_handler(
   SCIC_SDS_REQUEST_T * request,
   U32                  frame_index
)
{
   SCI_STATUS               status;
   SATA_FIS_HEADER_T      * frame_header;
   U32                    * frame_buffer;
   SCIC_SDS_STP_REQUEST_T * this_request;

   this_request = (SCIC_SDS_STP_REQUEST_T *)request;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_request),
      SCIC_LOG_OBJECT_STP_IO_REQUEST,
      "scic_sds_stp_packet_request_packet_phase_await_pio_setup_frame_handler(0x%x, 0x%x) enter\n",
      this_request, frame_index
   ));

   status = scic_sds_unsolicited_frame_control_get_header(
      &(this_request->parent.owning_controller->uf_control),
      frame_index,
      (void**) &frame_header
   );

   if (status == SCI_SUCCESS)
   {
      ASSERT(frame_header->fis_type == SATA_FIS_TYPE_PIO_SETUP);

      // Get from the frame buffer the PIO Setup Data, although we don't need
      // any info from this pio setup fis.
      scic_sds_unsolicited_frame_control_get_buffer(
         &(this_request->parent.owning_controller->uf_control),
         frame_index,
         (void**) &frame_buffer
      );

      // Get the data from the PIO Setup
      // The SCU Hardware returns first word in the frame_header and the rest
      // of the data is in the frame buffer so we need to back up one dword
      this_request->type.packet.device_preferred_cdb_length =
         (U16)((SATA_FIS_PIO_SETUP_T *)(&frame_buffer[-1]))->transfter_count;

      // Frame has been decoded return it to the controller
      scic_sds_controller_release_frame(
         this_request->parent.owning_controller, frame_index
      );

      sci_base_state_machine_change_state(
         &this_request->parent.started_substate_machine,
         SCIC_SDS_STP_PACKET_REQUEST_STARTED_COMMAND_PHASE_AWAIT_TC_COMPLETION_SUBSTATE
      );
   }
   else
   {
      SCIC_LOG_ERROR((
         sci_base_object_get_logger(this_request),
         SCIC_LOG_OBJECT_STP_IO_REQUEST,
         "SCIC IO Request 0x%x could not get frame header for frame index %d, status %x\n",
         this_request, frame_index, status
      ));
   }

   return status;
}