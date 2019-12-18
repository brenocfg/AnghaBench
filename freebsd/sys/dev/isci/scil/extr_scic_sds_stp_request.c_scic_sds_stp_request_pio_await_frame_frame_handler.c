#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;
struct TYPE_15__ {int /*<<< orphan*/  state_machine; } ;
struct TYPE_20__ {TYPE_3__ parent; int /*<<< orphan*/  started_substate_machine; TYPE_5__* owning_controller; } ;
struct TYPE_19__ {int fis_type; int status; } ;
struct TYPE_18__ {int /*<<< orphan*/  ending_status; int /*<<< orphan*/  transfter_count; } ;
struct TYPE_17__ {int /*<<< orphan*/  uf_control; } ;
struct TYPE_12__ {int /*<<< orphan*/  status; } ;
struct TYPE_13__ {int /*<<< orphan*/  sat_protocol; int /*<<< orphan*/  ending_status; int /*<<< orphan*/  pio_transfer_bytes; } ;
struct TYPE_14__ {TYPE_1__ pio; } ;
struct TYPE_16__ {TYPE_8__ parent; TYPE_10__ d2h_reg_fis; TYPE_2__ type; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_4__ SCIC_SDS_STP_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIC_SDS_REQUEST_T ;
typedef  TYPE_5__ SCIC_SDS_CONTROLLER_T ;
typedef  TYPE_6__ SATA_FIS_PIO_SETUP_T ;
typedef  TYPE_7__ SATA_FIS_HEADER_T ;

/* Variables and functions */
 int ATA_STATUS_REG_BSY_BIT ; 
#define  SATA_FIS_TYPE_PIO_SETUP 130 
#define  SATA_FIS_TYPE_REGD2H 129 
#define  SATA_FIS_TYPE_SETDEVBITS 128 
 int /*<<< orphan*/  SAT_PROTOCOL_PIO_DATA_IN ; 
 int /*<<< orphan*/  SAT_PROTOCOL_PIO_DATA_OUT ; 
 int /*<<< orphan*/  SCIC_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_LOG_OBJECT_STP_IO_REQUEST ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_STARTED_PIO_AWAIT_FRAME_SUBSTATE ; 
 int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_STARTED_PIO_DATA_IN_AWAIT_DATA_SUBSTATE ; 
 int /*<<< orphan*/  SCIC_SDS_STP_REQUEST_STARTED_PIO_DATA_OUT_TRANSMIT_DATA_SUBSTATE ; 
 int /*<<< orphan*/  SCI_BASE_REQUEST_STATE_COMPLETED ; 
 int /*<<< orphan*/  SCI_FAILURE_IO_RESPONSE_VALID ; 
 scalar_t__ SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_TASK_DONE_CHECK_RESPONSE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 
 int /*<<< orphan*/  sci_base_state_machine_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_controller_copy_sata_response (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_controller_release_frame (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_sds_request_set_status (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scic_sds_stp_request_pio_data_out_transmit_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scic_sds_unsolicited_frame_control_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ scic_sds_unsolicited_frame_control_get_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_stp_request_pio_await_frame_frame_handler(
   SCIC_SDS_REQUEST_T * request,
   U32                  frame_index
)
{
   SCI_STATUS               status;
   SATA_FIS_HEADER_T      * frame_header;
   U32                    * frame_buffer;
   SCIC_SDS_STP_REQUEST_T * this_request;
   SCIC_SDS_CONTROLLER_T  * owning_controller;

   this_request = (SCIC_SDS_STP_REQUEST_T *)request;

   // Save off the controller, so that we do not touch the request after it
   //  is completed.
   owning_controller = this_request->parent.owning_controller;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_request),
      SCIC_LOG_OBJECT_STP_IO_REQUEST,
      "scic_sds_stp_request_pio_data_in_await_frame_frame_handler(0x%x, 0x%x) enter\n",
      this_request, frame_index
   ));

   status = scic_sds_unsolicited_frame_control_get_header(
      &(owning_controller->uf_control),
      frame_index,
      (void**) &frame_header
   );

   if (status == SCI_SUCCESS)
   {
      switch (frame_header->fis_type)
      {
      case SATA_FIS_TYPE_PIO_SETUP:
         // Get from the frame buffer the PIO Setup Data
         scic_sds_unsolicited_frame_control_get_buffer(
            &(owning_controller->uf_control),
            frame_index,
            (void**) &frame_buffer
         );

         // Get the data from the PIO Setup
         // The SCU Hardware returns first word in the frame_header and the rest
         // of the data is in the frame buffer so we need to back up one dword
         this_request->type.pio.pio_transfer_bytes =
            (U16)((SATA_FIS_PIO_SETUP_T *)(&frame_buffer[-1]))->transfter_count;
         this_request->type.pio.ending_status =
            (U8)((SATA_FIS_PIO_SETUP_T *)(&frame_buffer[-1]))->ending_status;

         scic_sds_controller_copy_sata_response(
            &this_request->d2h_reg_fis, (U32 *)frame_header, frame_buffer
         );

         this_request->d2h_reg_fis.status =
            this_request->type.pio.ending_status;

         //The next state is dependent on whether the request was PIO Data-in or Data out
         if (this_request->type.pio.sat_protocol == SAT_PROTOCOL_PIO_DATA_IN)
         {
         sci_base_state_machine_change_state(
            &this_request->parent.started_substate_machine,
            SCIC_SDS_STP_REQUEST_STARTED_PIO_DATA_IN_AWAIT_DATA_SUBSTATE
            );
         }
         else if (this_request->type.pio.sat_protocol == SAT_PROTOCOL_PIO_DATA_OUT)
         {
            //Transmit data
            status = scic_sds_stp_request_pio_data_out_transmit_data ( request);
            if (status == SCI_SUCCESS)
            {
               sci_base_state_machine_change_state(
                  &this_request->parent.started_substate_machine,
                  SCIC_SDS_STP_REQUEST_STARTED_PIO_DATA_OUT_TRANSMIT_DATA_SUBSTATE
               );
            }
         }
      break;

      case SATA_FIS_TYPE_SETDEVBITS:
         sci_base_state_machine_change_state(
            &this_request->parent.started_substate_machine,
            SCIC_SDS_STP_REQUEST_STARTED_PIO_AWAIT_FRAME_SUBSTATE
            );
      break;

      case SATA_FIS_TYPE_REGD2H:
         if ( (frame_header->status & ATA_STATUS_REG_BSY_BIT) == 0)
         {
            scic_sds_unsolicited_frame_control_get_buffer(
               &(owning_controller->uf_control),
               frame_index,
               (void**) &frame_buffer
            );

            scic_sds_controller_copy_sata_response(
               &this_request->d2h_reg_fis, (U32 *)frame_header, frame_buffer);

            scic_sds_request_set_status(
               &this_request->parent,
               SCU_TASK_DONE_CHECK_RESPONSE,
               SCI_FAILURE_IO_RESPONSE_VALID
            );

            sci_base_state_machine_change_state(
               &this_request->parent.parent.state_machine,
               SCI_BASE_REQUEST_STATE_COMPLETED
            );
         }
         else
         {
            // Now why is the drive sending a D2H Register FIS when it is still busy?
            // Do nothing since we are still in the right state.
            SCIC_LOG_INFO((
               sci_base_object_get_logger(this_request),
               SCIC_LOG_OBJECT_STP_IO_REQUEST,
               "SCIC PIO Request 0x%x received D2H Register FIS with BSY status 0x%x\n",
               this_request, frame_header->status
            ));
         }
         break;

         default:
         break;
         }

      // Frame is decoded return it to the controller
      scic_sds_controller_release_frame(
         owning_controller,
         frame_index
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