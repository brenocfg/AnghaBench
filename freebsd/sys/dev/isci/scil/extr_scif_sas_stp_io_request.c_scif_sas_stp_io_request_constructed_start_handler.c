#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int sector_count; } ;
struct TYPE_7__ {scalar_t__ protocol; } ;
struct TYPE_8__ {int ncq_tag; TYPE_1__ sequence; } ;
struct TYPE_9__ {TYPE_2__ stp; int /*<<< orphan*/  core_object; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {TYPE_3__ parent; } ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  int /*<<< orphan*/  SCI_BASE_REQUEST_T ;
typedef  TYPE_4__ SCIF_SAS_IO_REQUEST_T ;
typedef  TYPE_5__ SATA_FIS_REG_H2D_T ;

/* Variables and functions */
 scalar_t__ SAT_PROTOCOL_FPDMA ; 
 int /*<<< orphan*/  SCIF_LOG_OBJECT_IO_REQUEST ; 
 int /*<<< orphan*/  SCIF_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int SCIF_SAS_INVALID_NCQ_TAG ; 
 int /*<<< orphan*/  SCI_FAILURE_NO_NCQ_TAG_AVAILABLE ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  sci_base_object_get_logger (int /*<<< orphan*/ *) ; 
 TYPE_5__* scic_stp_io_request_get_h2d_reg_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scic_stp_io_request_set_ncq_tag (int /*<<< orphan*/ ,int) ; 
 int scif_sas_stp_remote_device_allocate_ncq_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SCI_STATUS scif_sas_stp_io_request_constructed_start_handler(
   SCI_BASE_REQUEST_T * io_request
)
{
   SCIF_SAS_IO_REQUEST_T * fw_io = (SCIF_SAS_IO_REQUEST_T *) io_request;

   SCIF_LOG_TRACE((
      sci_base_object_get_logger(io_request),
      SCIF_LOG_OBJECT_IO_REQUEST,
      "scif_sas_stp_io_request_constructed_start_handler(0x%x) enter\n",
      io_request
   ));

   if (fw_io->parent.stp.sequence.protocol == SAT_PROTOCOL_FPDMA)
   {
      SATA_FIS_REG_H2D_T * fis;

      // For NCQ, we need to attempt to allocate an available tag.
      fw_io->parent.stp.ncq_tag = scif_sas_stp_remote_device_allocate_ncq_tag(
                                     fw_io->parent.device
                                  );

      if (fw_io->parent.stp.ncq_tag == SCIF_SAS_INVALID_NCQ_TAG)
         return SCI_FAILURE_NO_NCQ_TAG_AVAILABLE;

      // Set the NCQ tag in the host to device register FIS (upper 5 bits
      // of the 8-bit sector count register).
      fis = scic_stp_io_request_get_h2d_reg_address(fw_io->parent.core_object);
      fis->sector_count = (fw_io->parent.stp.ncq_tag << 3);

      // The Core also requires that we inform it separately regarding the
      // NCQ tag for this IO.
      scic_stp_io_request_set_ncq_tag(
         fw_io->parent.core_object, fw_io->parent.stp.ncq_tag
      );
   }

   return SCI_SUCCESS;
}