#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_2__ {int general_config_bits; } ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_1__ ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_GET_OFFSET (int /*<<< orphan*/ ) ; 
 int ATA_IDENTIFY_REMOVABLE_MEDIA_ENABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  model_number ; 
 int /*<<< orphan*/  sati_ata_identify_device_copy_data (int /*<<< orphan*/ *,void*,int,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_inquiry_construct_product_revision (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int) ; 

void sati_inquiry_standard_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_io
)
{
   ATA_IDENTIFY_DEVICE_DATA_T * identify = (ATA_IDENTIFY_DEVICE_DATA_T*)
                                           ata_input_data;
   U32  index;

   // Device type is disk, attached to this lun.
   sati_set_data_byte(sequence, scsi_io, 0, 0x00);

   // If the device indicates it's a removable media device, then set the
   // RMB bit
   if (identify->general_config_bits & ATA_IDENTIFY_REMOVABLE_MEDIA_ENABLE)
      sati_set_data_byte(sequence, scsi_io, 1, 0x80);
   else
      sati_set_data_byte(sequence, scsi_io, 1, 0x00);

   sati_set_data_byte(sequence, scsi_io, 2, 0x05); // Indicate SPC-3 support
   sati_set_data_byte(sequence, scsi_io, 3, 0x02); // Response Format SPC-3

   sati_set_data_byte(sequence, scsi_io, 4, 62); // 62 Additional Data Bytes.
                                                 // n-4 per the spec, we end at
                                                 // byte 66, so 66-4.
   sati_set_data_byte(sequence, scsi_io, 5, 0x00);
   sati_set_data_byte(sequence, scsi_io, 6, 0x00);
   sati_set_data_byte(sequence, scsi_io, 7, 0x02); // Enable Cmd Queueing

   // The Vender identification field is set to "ATA     "
   sati_set_data_byte(sequence, scsi_io, 8, 0x41);
   sati_set_data_byte(sequence, scsi_io, 9, 0x54);
   sati_set_data_byte(sequence, scsi_io, 10, 0x41);
   sati_set_data_byte(sequence, scsi_io, 11, 0x20);
   sati_set_data_byte(sequence, scsi_io, 12, 0x20);
   sati_set_data_byte(sequence, scsi_io, 13, 0x20);
   sati_set_data_byte(sequence, scsi_io, 14, 0x20);
   sati_set_data_byte(sequence, scsi_io, 15, 0x20);

   // Fill in the product ID field.
   sati_ata_identify_device_copy_data(
      sequence,
      scsi_io,
      16,
      ata_input_data,
      ATA_IDENTIFY_DEVICE_GET_OFFSET(model_number),
      16,
      TRUE
   );

   sati_inquiry_construct_product_revision(
      sequence,
      ata_input_data,
      scsi_io
   );

   // Set the remaining fields up to the version descriptors to 0.
   for (index = 36; index < 58; index++)
      sati_set_data_byte(sequence, scsi_io, index, 0);

   // Add version descriptors for the various protocols in play.

   // SAM-4
   sati_set_data_byte(sequence, scsi_io, 58, 0);
   sati_set_data_byte(sequence, scsi_io, 59, 0x80);

   // SAS-2
   sati_set_data_byte(sequence, scsi_io, 60, 0x0C);
   sati_set_data_byte(sequence, scsi_io, 61, 0x20);

   // SPC-4
   sati_set_data_byte(sequence, scsi_io, 62, 0x04);
   sati_set_data_byte(sequence, scsi_io, 63, 0x60);

   // SBC-3
   sati_set_data_byte(sequence, scsi_io, 64, 0x04);
   sati_set_data_byte(sequence, scsi_io, 65, 0xC0);

   // ATA/ATAPI-8 ACS
   sati_set_data_byte(sequence, scsi_io, 66, 0x16);
   sati_set_data_byte(sequence, scsi_io, 67, 0x23);
}