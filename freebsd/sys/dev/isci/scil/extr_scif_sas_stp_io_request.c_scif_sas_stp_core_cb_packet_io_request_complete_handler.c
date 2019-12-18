#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  sequence; } ;
struct TYPE_15__ {TYPE_3__ stp; } ;
struct TYPE_17__ {TYPE_4__ parent; } ;
struct TYPE_12__ {scalar_t__ state; } ;
struct TYPE_13__ {TYPE_1__ sequence; } ;
struct TYPE_16__ {TYPE_2__ stp; } ;
typedef  scalar_t__ SCI_STATUS ;
typedef  TYPE_5__ SCIF_SAS_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_6__ SCIF_SAS_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  SCIF_SAS_CONTROLLER_T ;
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 scalar_t__ SATI_COMPLETE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 scalar_t__ SATI_SEQUENCE_INCOMPLETE ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ SCI_FAILURE ; 
 scalar_t__ SCI_FAILURE_IO_RESPONSE_VALID ; 
 scalar_t__ SCI_SUCCESS ; 
 scalar_t__ SCI_WARNING_SEQUENCE_INCOMPLETE ; 
 scalar_t__ sati_atapi_translate_command_response (int /*<<< orphan*/ *,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sati_atapi_translate_request_sense_response (int /*<<< orphan*/ *,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_stp_core_cb_packet_io_request_complete_handler(
   SCIF_SAS_CONTROLLER_T    * fw_controller,
   SCIF_SAS_REMOTE_DEVICE_T * fw_device,
   SCIF_SAS_REQUEST_T       * fw_request,
   SCI_STATUS               * completion_status
)
{
   SCIF_SAS_IO_REQUEST_T * fw_io = (SCIF_SAS_IO_REQUEST_T *) fw_request;
   SATI_STATUS sati_status;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_controller),
      SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_stp_packet_core_cb_io_request_complete_handler(0x%x, 0x%x, 0x%x, 0x%x) enter\n",
      fw_controller, fw_device, fw_request, *completion_status
   ));

   if (*completion_status == SCI_FAILURE_IO_RESPONSE_VALID)
   {
      sati_status = sati_atapi_translate_command_response(
                       &fw_io->parent.stp.sequence, fw_io, fw_io
                    );

      if (sati_status == SATI_COMPLETE)
         *completion_status = SCI_SUCCESS;
      else if (sati_status == SATI_FAILURE_CHECK_RESPONSE_DATA)
         *completion_status = SCI_FAILURE_IO_RESPONSE_VALID;
      else if (sati_status == SATI_SEQUENCE_INCOMPLETE)
      {
         // The translation indicates that additional REQUEST SENSE command is
         // necessary to finish the original SCSI request.  As a result,
         // do not complete the IO and begin the next stage of the IO.
         return SCI_WARNING_SEQUENCE_INCOMPLETE;
      }
      else
      {
         // Something unexpected occurred during translation.  Fail the
         // IO request to the user.
         *completion_status = SCI_FAILURE;
      }
   }
   else if (*completion_status == SCI_SUCCESS &&
        fw_request->stp.sequence.state == SATI_SEQUENCE_STATE_INCOMPLETE)
   {
      //The internal Request Sense command is completed successfully.
      sati_atapi_translate_request_sense_response(
         &fw_io->parent.stp.sequence, fw_io, fw_io
      );

      *completion_status = SCI_FAILURE_IO_RESPONSE_VALID;
   }

   return SCI_SUCCESS;
}