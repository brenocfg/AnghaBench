#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ protocol; scalar_t__ type; } ;
struct TYPE_6__ {TYPE_3__ sequence; } ;
struct TYPE_7__ {TYPE_1__ stp; } ;
struct TYPE_9__ {TYPE_2__ parent; } ;
typedef  TYPE_4__ SCIF_SAS_IO_REQUEST_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SATI_SEQUENCE_ATA_PASSTHROUGH_12 ; 
 scalar_t__ SATI_SEQUENCE_ATA_PASSTHROUGH_16 ; 
 scalar_t__ SATI_SEQUENCE_TYPE_READ_MAX ; 
 scalar_t__ SATI_SEQUENCE_TYPE_READ_MIN ; 
 scalar_t__ SAT_PROTOCOL_PIO_DATA_IN ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_4__*) ; 

BOOL scic_cb_io_request_do_copy_rx_frames(
   void * scic_user_io_request
)
{
   SCIF_SAS_IO_REQUEST_T * fw_io = (SCIF_SAS_IO_REQUEST_T*) scic_user_io_request;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(fw_io),
      SCIF_LOG_OBJECT_IO_REQUEST,
      "scic_cb_io_request_do_copy_rx_frames(0x%x) enter\n",
      fw_io
   ));

   // If the translation was a PIO DATA IN (i.e. read) and the request
   // was actually a READ payload operation, then copy the data, since
   // there will be SGL space allocated for the transfer.
   if (fw_io->parent.stp.sequence.protocol == SAT_PROTOCOL_PIO_DATA_IN)
   {
      if (
            (fw_io->parent.stp.sequence.type ==  SATI_SEQUENCE_ATA_PASSTHROUGH_12)
         || (fw_io->parent.stp.sequence.type ==  SATI_SEQUENCE_ATA_PASSTHROUGH_16)
         || (
               (fw_io->parent.stp.sequence.type >= SATI_SEQUENCE_TYPE_READ_MIN)
            && (fw_io->parent.stp.sequence.type <= SATI_SEQUENCE_TYPE_READ_MAX)
            )
         )
      {
           SCIF_LOG_TRACE((
                 sci_base_object_get_logger(fw_io),
                 SCIF_LOG_OBJECT_IO_REQUEST,
                 "scic_cb_io_request_do_copy_rx_frames(0x%x) TRUE\n",
                 fw_io
              ));
           return TRUE;
      }
   }

   // For all other requests we leave the data in the core buffers.
   // This allows the translation to translate without having to have
   // separate space allocated into which to copy the data.
   return FALSE;
}