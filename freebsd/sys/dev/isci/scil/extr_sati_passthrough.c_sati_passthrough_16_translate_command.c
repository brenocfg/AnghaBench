#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  is_translate_response_required; scalar_t__ protocol; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 scalar_t__ PASSTHROUGH_CDB_CK_COND (int /*<<< orphan*/ *) ; 
 int PASSTHROUGH_CDB_EXTEND (int /*<<< orphan*/ *) ; 
 scalar_t__ PASSTHROUGH_CDB_PROTOCOL (int /*<<< orphan*/ *) ; 
 int PASSTHROUGH_CDB_T_DIR (int /*<<< orphan*/ *) ; 
 scalar_t__ PASSTHROUGH_DMA ; 
 scalar_t__ PASSTHROUGH_RETURN_RESPONSE ; 
 scalar_t__ PASSTHROUGH_UDMA_DATA_IN ; 
 scalar_t__ PASSTHROUGH_UDMA_DATA_OUT ; 
 scalar_t__ SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_ATA_PASSTHROUGH_16 ; 
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_AWAIT_RESPONSE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_TRANSLATE_DATA ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SCSI_ASCQ_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sati_passthrough_check_direction (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ sati_passthrough_multiple_count_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_device_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_features (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_features_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_passthrough_16_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_STATUS   status;
   U8          * cdb;
   U8          * register_fis;

   status = SATI_FAILURE;

   sequence->type = SATI_SEQUENCE_ATA_PASSTHROUGH_16;
   sequence->state = SATI_SEQUENCE_STATE_TRANSLATE_DATA;

   cdb = sati_cb_get_cdb_address(scsi_io);
   sequence->protocol = PASSTHROUGH_CDB_PROTOCOL(cdb);
   register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   /*
    * CAM will send passthrough commands with protocol set to multiword
    * DMA even though no multiword DMA mode is selected on the device.
    * This is because some controllers (LSI) will only accept
    * ATA_PASSTHROUGH commands with DMA mode - not UDMA_IN/OUT.
    *
    * Since isci does not support multiword DMA, fix this up here.
    */
   if (sequence->protocol == PASSTHROUGH_DMA)
   {
      if (PASSTHROUGH_CDB_T_DIR(cdb) == 0x1)
      {
         sequence->protocol = PASSTHROUGH_UDMA_DATA_IN;
      }
      else
      {
         sequence->protocol = PASSTHROUGH_UDMA_DATA_OUT;
      }
   }

   if (sati_passthrough_check_direction(sequence, cdb) != SATI_COMPLETE
       || sati_passthrough_multiple_count_error(cdb)
      )
   {
      // Fail due to mismatch
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

   if (PASSTHROUGH_CDB_EXTEND(cdb) == 1)
   {
      sati_set_ata_features_exp(register_fis, sati_get_cdb_byte(cdb, 3));
      sati_set_ata_sector_count_exp(register_fis, sati_get_cdb_byte(cdb, 5));
      sati_set_ata_lba_low_exp(register_fis, sati_get_cdb_byte(cdb, 7));
      sati_set_ata_lba_mid_exp(register_fis, sati_get_cdb_byte(cdb, 9));
      sati_set_ata_lba_high_exp(register_fis, sati_get_cdb_byte(cdb, 11));
   }

   if (PASSTHROUGH_CDB_CK_COND(cdb) ||
       PASSTHROUGH_CDB_PROTOCOL(cdb) == PASSTHROUGH_RETURN_RESPONSE)
   {
      sequence->is_translate_response_required = TRUE;
   }

   sati_set_ata_features(register_fis, sati_get_cdb_byte(cdb, 4));
   sati_set_ata_sector_count(register_fis, sati_get_cdb_byte(cdb, 6));
   sati_set_ata_lba_low(register_fis, sati_get_cdb_byte(cdb, 8));
   sati_set_ata_lba_mid(register_fis, sati_get_cdb_byte(cdb, 10));
   sati_set_ata_lba_high(register_fis, sati_get_cdb_byte(cdb, 12));
   sati_set_ata_device_head(register_fis, sati_get_cdb_byte(cdb, 13));
   sati_set_ata_command(register_fis, sati_get_cdb_byte(cdb, 14));

   sequence->state = SATI_SEQUENCE_STATE_AWAIT_RESPONSE;

   return SATI_SUCCESS;
}