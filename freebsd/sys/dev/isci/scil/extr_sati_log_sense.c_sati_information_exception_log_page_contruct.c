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
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 scalar_t__ ATA_HIGH_REGISTER_THRESHOLD_EXCEEDED ; 
 scalar_t__ ATA_MID_REGISTER_THRESHOLD_EXCEEDED ; 
 int SCSI_ASCQ_GENERAL_HARD_DRIVE_FAILURE ; 
 int SCSI_ASCQ_NO_ADDITIONAL_SENSE ; 
 int SCSI_ASC_HARDWARE_IMPENDING_FAILURE ; 
 int SCSI_ASC_NO_ADDITIONAL_SENSE ; 
 int SCSI_LOG_PAGE_INFORMATION_EXCEPTION ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 scalar_t__ sati_get_ata_lba_high (int /*<<< orphan*/ *) ; 
 scalar_t__ sati_get_ata_lba_mid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int) ; 

__attribute__((used)) static
void sati_information_exception_log_page_contruct(
   SATI_TRANSLATOR_SEQUENCE_T  * sequence,
   void                        * scsi_io,
   void                        * ata_io
)
{
   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);
   U32 mid_register = sati_get_ata_lba_mid(register_fis);
   U32 high_register = sati_get_ata_lba_high(register_fis);

   //Information Exception Page code
   sati_set_data_byte(
      sequence,
      scsi_io,
      0,
      SCSI_LOG_PAGE_INFORMATION_EXCEPTION
   );

   //Sub-page code
   sati_set_data_byte(sequence, scsi_io, 1, 0x00);

   //Page length of log parameters
   sati_set_data_byte(sequence, scsi_io, 2, 0x00);
   sati_set_data_byte(sequence, scsi_io, 3, 0x08);

   //parameter code
   sati_set_data_byte(sequence, scsi_io, 4, 0x00);
   sati_set_data_byte(sequence, scsi_io, 5, 0x00);

   //Format and Linking
   sati_set_data_byte(sequence, scsi_io, 6, 0x03);
   //Parameter Length
   sati_set_data_byte(sequence, scsi_io, 7, 0x04);

   if(mid_register == ATA_MID_REGISTER_THRESHOLD_EXCEEDED
      && high_register == ATA_HIGH_REGISTER_THRESHOLD_EXCEEDED)
   {
      sati_set_data_byte(
         sequence,
         scsi_io,
         8,
         SCSI_ASC_HARDWARE_IMPENDING_FAILURE
      );

      sati_set_data_byte(
         sequence,
         scsi_io,
         9,
         SCSI_ASCQ_GENERAL_HARD_DRIVE_FAILURE
      );
   }
   else
   {
      sati_set_data_byte(sequence, scsi_io, 8, SCSI_ASC_NO_ADDITIONAL_SENSE);
      sati_set_data_byte(sequence, scsi_io, 9, SCSI_ASCQ_NO_ADDITIONAL_SENSE);
   }
   //setting most recent temperature reading to 0xFF(not supported) for now.
   sati_set_data_byte(sequence, scsi_io, 10, 0xFF);
}