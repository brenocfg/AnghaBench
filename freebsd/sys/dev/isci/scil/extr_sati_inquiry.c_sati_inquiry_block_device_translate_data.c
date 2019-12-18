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
struct TYPE_2__ {int device_nominal_form_factor; } ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_1__ ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_GET_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int SCSI_INQUIRY_BLOCK_DEVICE_LENGTH ; 
 int SCSI_INQUIRY_BLOCK_DEVICE_PAGE ; 
 int /*<<< orphan*/  nominal_media_rotation_rate ; 
 int /*<<< orphan*/  sati_ata_identify_device_copy_data (int /*<<< orphan*/ *,void*,int,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int) ; 

void sati_inquiry_block_device_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_io
)
{
   ATA_IDENTIFY_DEVICE_DATA_T * identify = (ATA_IDENTIFY_DEVICE_DATA_T*)
      ata_input_data;

   U32 offset;

   // Peripheral qualifier (0x0, currently connected)
   // Peripheral device type (0x0 direct-access block device)
   sati_set_data_byte(sequence, scsi_io, 0, 0x00);

   sati_set_data_byte(sequence, scsi_io, 1, SCSI_INQUIRY_BLOCK_DEVICE_PAGE);

   //PAGE LENGTH 0x003C
   sati_set_data_byte(sequence, scsi_io, 2, 0x00);
   sati_set_data_byte(sequence, scsi_io, 3, SCSI_INQUIRY_BLOCK_DEVICE_LENGTH);

   sati_ata_identify_device_copy_data(
      sequence,
      scsi_io,
      4,
      ata_input_data,
      ATA_IDENTIFY_DEVICE_GET_OFFSET(nominal_media_rotation_rate),
      2,
      FALSE
    );

    sati_set_data_byte(sequence, scsi_io, 6, 0x00);

    sati_set_data_byte(
       sequence,
       scsi_io,
       7,
       (identify->device_nominal_form_factor & 0x0F) // only need bits 0-3
    );

    //bytes 8-63 are reserved
    for(offset = 8; offset < 64; offset++)
    {
       sati_set_data_byte(sequence, scsi_io, offset, 0x00);
    }
}