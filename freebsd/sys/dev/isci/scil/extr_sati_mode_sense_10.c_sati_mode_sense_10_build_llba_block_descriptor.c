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
typedef  int U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int SCSI_MODE_SENSE_LLBA_BLOCK_DESCRIPTOR_LENGTH ; 
 int /*<<< orphan*/  sati_ata_identify_device_get_sector_info (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
U32 sati_mode_sense_10_build_llba_block_descriptor(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   U32                          offset
)
{
   U32  lba_low     = 0;
   U32  lba_high    = 0;
   U32  sector_size = 0;

   // Extract the sector information (sector size, logical blocks) from
   // the retrieved ATA identify device data.
   sati_ata_identify_device_get_sector_info(
      identify, &lba_low, &lba_high, &sector_size
   );

   // Fill in the 8-byte logical block area
   sati_set_data_byte(sequence, scsi_io, offset,   (U8)((lba_high>>24) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, offset+1, (U8)((lba_high>>16) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, offset+2, (U8)((lba_high>>8)  & 0xFF));
   sati_set_data_byte(sequence, scsi_io, offset+3, (U8)(lba_high & 0xFF));
   sati_set_data_byte(sequence, scsi_io, offset+4, (U8)((lba_low>>24) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, offset+5, (U8)((lba_low>>16) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, offset+6, (U8)((lba_low>>8)  & 0xFF));
   sati_set_data_byte(sequence, scsi_io, offset+7, (U8)(lba_low & 0xFF));

   // Clear the reserved fields.
   sati_set_data_byte(sequence, scsi_io, offset+8, 0);
   sati_set_data_byte(sequence, scsi_io, offset+9, 0);
   sati_set_data_byte(sequence, scsi_io, offset+10, 0);
   sati_set_data_byte(sequence, scsi_io, offset+11, 0);

   // Fill in the four byte Block Length field
   sati_set_data_byte(sequence,scsi_io, offset+12, (U8)((sector_size>>24) & 0xFF));
   sati_set_data_byte(sequence,scsi_io, offset+13, (U8)((sector_size>>16) & 0xFF));
   sati_set_data_byte(sequence,scsi_io, offset+14, (U8)((sector_size>>8)  & 0xFF));
   sati_set_data_byte(sequence,scsi_io, offset+15, (U8)(sector_size & 0xFF));

   return SCSI_MODE_SENSE_LLBA_BLOCK_DESCRIPTOR_LENGTH;
}