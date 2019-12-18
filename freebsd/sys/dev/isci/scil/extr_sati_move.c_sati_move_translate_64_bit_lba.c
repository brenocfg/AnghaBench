#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SCSI_ASCQ_LBA_OUT_OF_RANGE ; 
 int /*<<< orphan*/  SCSI_ASC_LBA_OUT_OF_RANGE ; 
 int /*<<< orphan*/  SCSI_SENSE_ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 scalar_t__ sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high_exp (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low_exp (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid_exp (int /*<<< orphan*/ *,scalar_t__) ; 

SATI_STATUS sati_move_translate_64_bit_lba(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb          = sati_cb_get_cdb_address(scsi_io);
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   // Ensure we receive a logical block address that is within range of
   // addressibility per the ATA specification (i.e. 48-bit or 28-bit).
   if ( (sati_get_cdb_byte(cdb, 2) == 0) && (sati_get_cdb_byte(cdb, 3) == 0) )
   {
      sati_set_ata_lba_low(register_fis, sati_get_cdb_byte(cdb, 9));
      sati_set_ata_lba_mid(register_fis, sati_get_cdb_byte(cdb, 8));
      sati_set_ata_lba_high(register_fis, sati_get_cdb_byte(cdb, 7));
      sati_set_ata_lba_low_exp(register_fis, sati_get_cdb_byte(cdb, 6));
      sati_set_ata_lba_mid_exp(register_fis, sati_get_cdb_byte(cdb, 5));
      sati_set_ata_lba_high_exp(register_fis, sati_get_cdb_byte(cdb, 4));
      return SATI_SUCCESS;
   }
   else
   {
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_ILLEGAL_REQUEST,
         SCSI_ASC_LBA_OUT_OF_RANGE,
         SCSI_ASCQ_LBA_OUT_OF_RANGE
      );
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }
}