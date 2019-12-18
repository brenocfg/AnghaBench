#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
typedef  int U32 ;
typedef  int U16 ;
struct TYPE_9__ {int physical_logical_sector_info; int logical_sector_alignment; } ;
struct TYPE_8__ {TYPE_1__* device; } ;
struct TYPE_7__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_3__ ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int ATA_IDENTIFY_LOGICAL_SECTOR_PER_PHYSICAL_SECTOR_ENABLE ; 
 int ATA_IDENTIFY_LOGICAL_SECTOR_PER_PHYSICAL_SECTOR_MASK ; 
 int SATI_DEVICE_CAP_DETERMINISTIC_READ_AFTER_TRIM ; 
 int SATI_DEVICE_CAP_DSM_TRIM_SUPPORT ; 
 int SATI_DEVICE_CAP_READ_ZERO_AFTER_TRIM ; 
 int /*<<< orphan*/  sati_ata_identify_device_get_sector_info (TYPE_3__*,int*,int*,int*) ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_2__*,void*,int,int) ; 

void sati_read_capacity_16_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_io
)
{
   U32  lba_low     = 0;
   U32  lba_high    = 0;
   U32  sector_size = 0;
   ATA_IDENTIFY_DEVICE_DATA_T * identify_device_data;
   U16  physical_per_logical_enable_bit = 0;
   U8   physical_per_logical_sector_exponent = 0;
   U16  physical_per_logical_sector = 0;
   U16  logical_sector_alignment = 0;
   U16  scsi_logical_sector_alignment = 0;
   U8   byte14 = 0;

   //A number of data fields need to be extracted from ATA identify device data
   identify_device_data = (ATA_IDENTIFY_DEVICE_DATA_T*)ata_input_data;

   // Extract the sector information (sector size, logical blocks) from
   // the retrieved ATA identify device data.
   sati_ata_identify_device_get_sector_info(
      (ATA_IDENTIFY_DEVICE_DATA_T*)ata_input_data,
      &lba_high,
      &lba_low,
      &sector_size
   );

   // SATA drives report a value that is one LBA larger than the last LBA.
   // SCSI wants the last LBA.  Make the correction here.  lba_low is
   // always decremented since it is an unsigned long the value 0 will
   // wrap to 0xFFFFFFFF.
   if ((lba_low == 0) && (lba_high == 0))
      lba_high -= 1;
   lba_low -= 1;

   // Build the CDB for Read Capacity 16
   // Fill in the Logical Block Address bytes.
   sati_set_data_byte(sequence, scsi_io, 0, (U8)((lba_high >> 24) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 1, (U8)((lba_high >> 16) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 2, (U8)((lba_high >> 8)  & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 3, (U8)(lba_high & 0xFF));

   sati_set_data_byte(sequence, scsi_io, 4, (U8)((lba_low >> 24) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 5, (U8)((lba_low >> 16) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 6, (U8)((lba_low >> 8)  & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 7, (U8)(lba_low & 0xFF));

   //Fill in the sector size field.
   sati_set_data_byte(sequence, scsi_io, 8,  (U8)((sector_size >> 24) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 9,  (U8)((sector_size >> 16) & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 10, (U8)((sector_size >> 8)  & 0xFF));
   sati_set_data_byte(sequence, scsi_io, 11, (U8)(sector_size & 0xFF));

   //Explicitly set byte 12 to 0.  SATI requires that all bytes in the data
   //response be explicitly set to some value.
   sati_set_data_byte(sequence, scsi_io, 12, 0);

   //Check Bit 13 of ATA_IDENTIFY_DEVICE_DATA physical_logical_sector_info
   //(Word 106) is enabled
   physical_per_logical_enable_bit = (identify_device_data->physical_logical_sector_info
      & ATA_IDENTIFY_LOGICAL_SECTOR_PER_PHYSICAL_SECTOR_ENABLE);

   //Extract the Physical per logical sector exponent field and calculate
   //Physical per logical sector value
   physical_per_logical_sector_exponent = (U8) (identify_device_data->physical_logical_sector_info
      & ATA_IDENTIFY_LOGICAL_SECTOR_PER_PHYSICAL_SECTOR_MASK);
   physical_per_logical_sector = 1 << (physical_per_logical_sector_exponent);

   //If the data is valid, fill in the logical blocks per physical block exponent field.
   //Else set logical blocks per physical block exponent to 1
   if (physical_per_logical_enable_bit != 0)
      sati_set_data_byte(
         sequence,
         scsi_io,
         13,
         (U8)(physical_per_logical_sector_exponent & 0xFF)
      );
   else
      sati_set_data_byte(sequence, scsi_io, 13, 0);

   //Fill in the lowest aligned logical block address field.
   logical_sector_alignment = identify_device_data->logical_sector_alignment;
   if (logical_sector_alignment == 0)
      scsi_logical_sector_alignment = 0;
   else
      scsi_logical_sector_alignment = (physical_per_logical_sector - logical_sector_alignment)
         % physical_per_logical_sector;

   //Follow SAT for reporting tprz and tpe
   if ((sequence->device->capabilities & SATI_DEVICE_CAP_DSM_TRIM_SUPPORT) &&
       (sequence->device->capabilities & SATI_DEVICE_CAP_DETERMINISTIC_READ_AFTER_TRIM))
   {
      // tpe
      byte14 |= 0x80;
      // tprz
      if (sequence->device->capabilities & SATI_DEVICE_CAP_READ_ZERO_AFTER_TRIM)
          byte14 |= 0x40;
   }
   sati_set_data_byte(
       sequence,
       scsi_io,
       14,
       (U8)(((scsi_logical_sector_alignment >>8) & 0x3F) | byte14));

   sati_set_data_byte(
       sequence,
       scsi_io,
       15,
       (U8)(scsi_logical_sector_alignment & 0xFF));
}