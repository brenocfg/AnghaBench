#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  do_translate_sgl; } ;
struct TYPE_13__ {int /*<<< orphan*/  sequence; } ;
struct TYPE_16__ {void* protocol_complete_handler; int /*<<< orphan*/ * state_handlers; int /*<<< orphan*/  core_object; TYPE_1__ stp; TYPE_5__* device; } ;
struct TYPE_18__ {TYPE_4__ parent; } ;
struct TYPE_14__ {int /*<<< orphan*/  sati_device; } ;
struct TYPE_15__ {TYPE_2__ stp_device; } ;
struct TYPE_17__ {TYPE_3__ protocol_device; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_5__ SCIF_SAS_REMOTE_DEVICE_T ;
typedef  TYPE_6__ SCIF_SAS_IO_REQUEST_T ;
typedef  TYPE_7__ SCIC_IO_SATA_PARAMETERS_T ;
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SATI_COMPLETE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 scalar_t__ SATI_SUCCESS ; 
 scalar_t__ SATI_SUCCESS_SGL_TRANSLATED ; 
 int /*<<< orphan*/  SCIF_LOG_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCI_FAILURE ; 
 int /*<<< orphan*/  SCI_FAILURE_IO_RESPONSE_VALID ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCI_SUCCESS_IO_COMPLETE_BEFORE_START ; 
 scalar_t__ sati_translate_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_6__*) ; 
 int /*<<< orphan*/  scic_io_request_construct_advanced_sata (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  scic_io_request_construct_basic_sata (int /*<<< orphan*/ ) ; 
 void* scif_sas_stp_core_cb_io_request_complete_handler ; 
 int /*<<< orphan*/  stp_io_request_constructed_handlers ; 

SCI_STATUS scif_sas_stp_io_request_construct(
   SCIF_SAS_IO_REQUEST_T * fw_io
)
{
   SATI_STATUS                sati_status;
   SCI_STATUS                 sci_status = SCI_FAILURE;
   SCIF_SAS_REMOTE_DEVICE_T * fw_device  = fw_io->parent.device;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_io),
      SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_stp_io_request_construct(0x%x) enter\n",
      fw_io
   ));

   // The translator will indirectly invoke core methods to set the fields
   // of the ATA register FIS inside of this method.
   sati_status = sati_translate_command(
                    &fw_io->parent.stp.sequence,
                    &fw_device->protocol_device.stp_device.sati_device,
                    fw_io,
                    fw_io
                 );

   if (sati_status == SATI_SUCCESS)
   {
      // Allow the core to finish construction of the IO request.
      sci_status = scic_io_request_construct_basic_sata(fw_io->parent.core_object);
      fw_io->parent.state_handlers = &stp_io_request_constructed_handlers;
      fw_io->parent.protocol_complete_handler
         = scif_sas_stp_core_cb_io_request_complete_handler;
   }
   else if (sati_status == SATI_SUCCESS_SGL_TRANSLATED)
   {
      SCIC_IO_SATA_PARAMETERS_T parms;
      parms.do_translate_sgl = FALSE;

      // The translation actually already caused translation of the
      // scatter gather list.  So, call into the core through an API
      // that will not attempt to translate the SGL.
      scic_io_request_construct_advanced_sata(
                      fw_io->parent.core_object, &parms
                   );
      fw_io->parent.state_handlers = &stp_io_request_constructed_handlers;
      fw_io->parent.protocol_complete_handler
         = scif_sas_stp_core_cb_io_request_complete_handler;
      // Done with translation
      sci_status = SCI_SUCCESS;
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
         "Unexpected SAT translation failure 0x%x\n",
         fw_io
      ));
   }

   return sci_status;
}