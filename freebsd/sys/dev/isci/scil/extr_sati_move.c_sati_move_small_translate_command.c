#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_9__ {TYPE_1__* device; int /*<<< orphan*/  protocol; } ;
struct TYPE_8__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_READ_DMA ; 
 int /*<<< orphan*/  ATA_READ_DMA_EXT ; 
 int /*<<< orphan*/  ATA_READ_FPDMA ; 
 int /*<<< orphan*/  ATA_WRITE_DMA ; 
 int /*<<< orphan*/  ATA_WRITE_DMA_EXT ; 
 int /*<<< orphan*/  ATA_WRITE_FPDMA ; 
 int SATI_DEVICE_CAP_48BIT_ENABLE ; 
 int SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE ; 
 int SATI_DEVICE_CAP_UDMA_ENABLE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SAT_PROTOCOL_FPDMA ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 scalar_t__ sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_move_6_translate_command (TYPE_2__*,void*,void*) ; 
 int /*<<< orphan*/  sati_move_ncq_translate_8_bit_sector_count (void*,void*) ; 
 int /*<<< orphan*/  sati_move_set_ata_command (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_move_small_udma_translate_command (TYPE_2__*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count_exp (int /*<<< orphan*/ *,int) ; 

SATI_STATUS sati_move_small_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   // Translation of the sector count is performed differently for NCQ vs.
   // other protocols.
   if (sequence->device->capabilities & SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE)
   {
      sati_move_set_ata_command(
         sequence, ata_io, ATA_WRITE_FPDMA, ATA_READ_FPDMA
      );
      sati_move_ncq_translate_8_bit_sector_count(scsi_io, ata_io);
      sequence->protocol = SAT_PROTOCOL_FPDMA;
   }
   else if (sequence->device->capabilities & SATI_DEVICE_CAP_48BIT_ENABLE)
   {
      U8 * cdb = sati_cb_get_cdb_address(scsi_io);

      sati_move_small_udma_translate_command(
         sequence, scsi_io, ata_io, ATA_WRITE_DMA_EXT, ATA_READ_DMA_EXT
      );

      // A read/write 6 with a 0 sector count indicates a transfer of 256
      // sectors.  As a result update the MSB (features expanded register)
      // to indicate 256 sectors (0x100).
      if (sati_get_cdb_byte(cdb, 4) == 0)
      {
         U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);
         sati_set_ata_sector_count_exp(register_fis, 1);
      }
   }
   else if (sequence->device->capabilities & SATI_DEVICE_CAP_UDMA_ENABLE)
   {
      sati_move_small_udma_translate_command(
         sequence, scsi_io, ata_io, ATA_WRITE_DMA, ATA_READ_DMA
      );
   }
   else
   {
      /**
       * Currently the translation does not support devices incapable of
       * handling the 48-bit feature set (i.e. 16 bits of sector count).
       */
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_INVALID_FIELD_IN_CDB,
         SCSI_ASCQ_INVALID_FIELD_IN_CDB
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   return sati_move_6_translate_command(sequence, scsi_io, ata_io);
}