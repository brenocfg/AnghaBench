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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_9__ {TYPE_1__* device; int /*<<< orphan*/  protocol; } ;
struct TYPE_8__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DEV_HEAD_REG_FUA_ENABLE ; 
 int /*<<< orphan*/  ATA_READ_DMA ; 
 int /*<<< orphan*/  ATA_READ_DMA_EXT ; 
 int /*<<< orphan*/  ATA_READ_FPDMA ; 
 int /*<<< orphan*/  ATA_WRITE_DMA ; 
 int /*<<< orphan*/  ATA_WRITE_DMA_EXT ; 
 int /*<<< orphan*/  ATA_WRITE_FPDMA ; 
 int SATI_DEVICE_CAP_48BIT_ENABLE ; 
 int SATI_DEVICE_CAP_IGNORE_FUA ; 
 int SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE ; 
 int SATI_DEVICE_CAP_UDMA_ENABLE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SAT_PROTOCOL_FPDMA ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int SCSI_MOVE_FUA_BIT_ENABLE ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_move_large_udma_translate_command (TYPE_2__*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_move_set_ata_command (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_move_set_sector_count (TYPE_2__*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_move_large_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U32                          sector_count,
   U8                         * ata_device_head
)
{
   SATI_STATUS   status = SATI_SUCCESS;
   U8          * cdb    = sati_cb_get_cdb_address(scsi_io);

   // Parts of translation (e.g. sector count) is performed differently
   // for NCQ vs. other protocols.
   if (sequence->device->capabilities & SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE)
   {
      // if the user did not request to ignore FUA
      if((sequence->device->capabilities & SATI_DEVICE_CAP_IGNORE_FUA)==0)
      {
         // Is the Force Unit Access bit set?
         if (sati_get_cdb_byte(cdb, 1) & SCSI_MOVE_FUA_BIT_ENABLE)
            *ata_device_head = ATA_DEV_HEAD_REG_FUA_ENABLE;
      }

      sati_move_set_ata_command(
         sequence, ata_io, ATA_WRITE_FPDMA, ATA_READ_FPDMA
      );
      status = sati_move_set_sector_count(
                  sequence, scsi_io, ata_io, sector_count, TRUE
               );
      sequence->protocol = SAT_PROTOCOL_FPDMA;
   }
   else if (sequence->device->capabilities & SATI_DEVICE_CAP_48BIT_ENABLE)
   {
      // Is the Force Unit Access bit set?  If it is, then error.  We
      // aren't supporting this yet for normal DMA.
      if (sati_get_cdb_byte(cdb, 1) & SCSI_MOVE_FUA_BIT_ENABLE)
      {
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

      status = sati_move_large_udma_translate_command(
                  sequence,
                  scsi_io,
                  ata_io,
                  sector_count,
                  ATA_WRITE_DMA_EXT,
                  ATA_READ_DMA_EXT
               );
   }
   else if (sequence->device->capabilities & SATI_DEVICE_CAP_UDMA_ENABLE)
   {
      status = sati_move_large_udma_translate_command(
                  sequence,
                  scsi_io,
                  ata_io,
                  sector_count,
                  ATA_WRITE_DMA,
                  ATA_READ_DMA
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

   return status;
}