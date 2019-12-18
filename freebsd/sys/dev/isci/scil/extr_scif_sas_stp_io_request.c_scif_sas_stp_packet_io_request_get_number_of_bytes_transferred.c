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
typedef  scalar_t__ U32 ;
struct TYPE_8__ {int /*<<< orphan*/  sequence; } ;
struct TYPE_9__ {TYPE_1__ stp; } ;
struct TYPE_10__ {TYPE_2__ parent; } ;
typedef  scalar_t__ SCI_IO_STATUS ;
typedef  int /*<<< orphan*/  SCI_IO_REQUEST_HANDLE_T ;
typedef  TYPE_3__ SCIF_SAS_IO_REQUEST_T ;

/* Variables and functions */
 scalar_t__ SCI_IO_FAILURE_RESPONSE_VALID ; 
 scalar_t__ SCI_IO_SUCCESS_IO_DONE_EARLY ; 
 scalar_t__ sati_atapi_translate_number_of_bytes_transferred (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ scic_io_request_get_number_of_bytes_transferred (int /*<<< orphan*/ ) ; 
 scalar_t__ scic_request_get_sci_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_io_request_get_scic_handle (TYPE_3__*) ; 

U32 scif_sas_stp_packet_io_request_get_number_of_bytes_transferred(
   SCIF_SAS_IO_REQUEST_T * fw_io
)
{
   SCI_IO_REQUEST_HANDLE_T scic_io = scif_io_request_get_scic_handle(fw_io);
   SCI_IO_STATUS io_status = scic_request_get_sci_status (scic_io);
   U32 actual_data_length;

   if (io_status == SCI_IO_FAILURE_RESPONSE_VALID)
       actual_data_length = 0;
   else if (io_status == SCI_IO_SUCCESS_IO_DONE_EARLY)
   {
      actual_data_length = sati_atapi_translate_number_of_bytes_transferred(
         &fw_io->parent.stp.sequence, fw_io, fw_io);

      if (actual_data_length == 0)
         actual_data_length =
            scic_io_request_get_number_of_bytes_transferred(scic_io);
   }
   else
      actual_data_length =
         scic_io_request_get_number_of_bytes_transferred(scic_io);

   return actual_data_length;
}