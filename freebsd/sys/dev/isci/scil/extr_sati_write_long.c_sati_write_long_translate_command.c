#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int U16 ;
struct TYPE_10__ {void* type; TYPE_1__* device; } ;
struct TYPE_9__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_WRITE_UNCORRECTABLE_FLAGGED ; 
 int /*<<< orphan*/  ATA_WRITE_UNCORRECTABLE_PSEUDO ; 
#define  COR_DIS_WR_UNCORR_BIT 130 
 int SATI_DEVICE_CAP_MULTIPLE_SECTORS_PER_PHYSCIAL_SECTOR ; 
 int SATI_DEVICE_CAP_WRITE_UNCORRECTABLE_ENABLE ; 
 scalar_t__ SATI_FAILURE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 void* SATI_SEQUENCE_WRITE_LONG ; 
 scalar_t__ SATI_SUCCESS ; 
 int SATI_WRITE_LONG_GET_COR_WR_PB_BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_COMMAND_OPERATION_CODE ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_COMMAND_OPERATION_CODE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int SCSI_WRITE_LONG_10 ; 
#define  WR_UNCOR_BIT 129 
#define  WR_UNCOR_PBLOCK_BIT 128 
 int /*<<< orphan*/  sati_ata_write_uncorrectable_construct (void*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_move_translate_32_bit_lba (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_move_translate_64_bit_lba (TYPE_2__*,void*,void*) ; 
 int /*<<< orphan*/  sati_move_translate_command (TYPE_2__*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_write_long_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);
   SATI_STATUS status = SATI_FAILURE;
   U16 byte_transfer_length;
   U8 device_head  = 0;

   if((sequence->device->capabilities &
       SATI_DEVICE_CAP_WRITE_UNCORRECTABLE_ENABLE) == 0)
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_INVALID_COMMAND_OPERATION_CODE,
         SCSI_ASCQ_INVALID_COMMAND_OPERATION_CODE
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   //Write Long 10
   if(sati_get_cdb_byte(cdb, 0) == SCSI_WRITE_LONG_10)
   {
      byte_transfer_length = (sati_get_cdb_byte(cdb, 7) << 8) |
                             (sati_get_cdb_byte(cdb, 8));

      sati_move_translate_32_bit_lba(sequence, scsi_io, ata_io);
   }
   else //Write Long 16
   {
      byte_transfer_length = (sati_get_cdb_byte(cdb, 12) << 8) |
                             (sati_get_cdb_byte(cdb, 13));

      status = sati_move_translate_64_bit_lba(sequence, scsi_io, ata_io);

      if( status == SATI_FAILURE_CHECK_RESPONSE_DATA)
      {
         return status;
      }
   }


   sati_move_translate_command(sequence, scsi_io, ata_io, device_head);

   if( byte_transfer_length != 0 )
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

   switch(SATI_WRITE_LONG_GET_COR_WR_PB_BITS(cdb))
   {
      case WR_UNCOR_BIT :

         if( (sequence->device->capabilities &
              SATI_DEVICE_CAP_MULTIPLE_SECTORS_PER_PHYSCIAL_SECTOR) != 0 )
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
         else
         {
            sati_ata_write_uncorrectable_construct(
               ata_io,
               sequence,
               ATA_WRITE_UNCORRECTABLE_PSEUDO
            );
            sequence->type = SATI_SEQUENCE_WRITE_LONG;
            status = SATI_SUCCESS;
         }
         break;

      case WR_UNCOR_PBLOCK_BIT :

         sati_ata_write_uncorrectable_construct(
            ata_io,
            sequence,
            ATA_WRITE_UNCORRECTABLE_PSEUDO
         );
         sequence->type = SATI_SEQUENCE_WRITE_LONG;
         status = SATI_SUCCESS;
         break;

      case COR_DIS_WR_UNCORR_BIT :

         sati_ata_write_uncorrectable_construct(
            ata_io,
            sequence,
            ATA_WRITE_UNCORRECTABLE_FLAGGED
         );
         sequence->type = SATI_SEQUENCE_WRITE_LONG;
         status = SATI_SUCCESS;
         break;

      default :

         sati_scsi_sense_data_construct(
            sequence,
            scsi_io,
            SCSI_STATUS_CHECK_CONDITION,
            SCSI_SENSE_ILLEGAL_REQUEST,
            SCSI_ASC_INVALID_FIELD_IN_CDB,
            SCSI_ASCQ_INVALID_FIELD_IN_CDB
         );
         return SATI_FAILURE_CHECK_RESPONSE_DATA;
         break;
   }
   return status;
}