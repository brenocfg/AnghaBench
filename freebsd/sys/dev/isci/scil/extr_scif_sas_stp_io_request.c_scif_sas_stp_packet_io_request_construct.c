#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  sequence; } ;
struct TYPE_14__ {int /*<<< orphan*/  protocol_complete_handler; int /*<<< orphan*/  core_object; TYPE_1__ stp; TYPE_5__* device; } ;
struct TYPE_16__ {TYPE_4__ parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  sati_device; } ;
struct TYPE_13__ {TYPE_2__ stp_device; } ;
struct TYPE_15__ {TYPE_3__ protocol_device; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_6__ SCIF_SAS_IO_REQUEST_T ;
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 scalar_t__ SATI_COMPLETE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 scalar_t__ SATI_SUCCESS ; 
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_FAILURE_IO_RESPONSE_VALID ; 
 int /*<<< orphan*/  SCI_SUCCESS_IO_COMPLETE_BEFORE_START ; 
 scalar_t__ sati_atapi_translate_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_6__*) ; 
 int /*<<< orphan*/  scic_io_request_construct_basic_sata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_sas_stp_core_cb_packet_io_request_complete_handler ; 

SCI_STATUS scif_sas_stp_packet_io_request_construct(
   SCIF_SAS_IO_REQUEST_T * fw_io
)
{
   SATI_STATUS                sati_status;
   SCI_STATUS                 sci_status = SCI_FAILURE;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device  = fw_io->parent.device;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_io),
      SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_stp_packet_io_request_construct(0x%x) enter\n",
      fw_io
   ));

   sati_status = sati_atapi_translate_command(
                    &fw_io->parent.stp.sequence,
                    &fw_device->protocol_device.stp_device.sati_device,
                    fw_io,
                    fw_io
                 );

   if (sati_status == SATI_SUCCESS)
   {
      // Allow the core to finish construction of the IO request.
      sci_status = scic_io_request_construct_basic_sata(fw_io->parent.core_object);

      fw_io->parent.protocol_complete_handler
         = scif_sas_stp_core_cb_packet_io_request_complete_handler;
   }
   else if (sati_status == SATI_COMPLETE)
      sci_status = SCI_SUCCESS_IO_COMPLETE_BEFORE_START;
   else if (sati_status == SATI_FAILURE_CHECK_RESPONSE_DATA)
      sci_status = SCI_FAILURE_IO_RESPONSE_VALID;
   else
   {
      SCIF_LOG_ERROR((
         sci_base_object_get_logger(fw_io),
         SCIF_LOG_OBJECT_IO_REQUEST,
         "Unexpected SAT ATAPI translation failure 0x%x\n",
         fw_io
      ));
   }

   return sci_status;
}