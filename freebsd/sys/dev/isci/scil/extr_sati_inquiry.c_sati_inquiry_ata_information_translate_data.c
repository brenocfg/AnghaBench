#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_GET_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_INCOMPLETE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int SCSI_INQUIRY_ATA_INFORMATION_PAGE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  model_number ; 
 int /*<<< orphan*/  sati_ata_identify_device_copy_data (TYPE_1__*,void*,int,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_inquiry_construct_product_revision (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_1__*,void*,int,int) ; 

SATI_STATUS sati_inquiry_ata_information_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_io
)
{
   sati_set_data_byte(sequence, scsi_io, 0, 0x00);
   sati_set_data_byte(sequence, scsi_io, 1, SCSI_INQUIRY_ATA_INFORMATION_PAGE);
   sati_set_data_byte(sequence, scsi_io, 2, 0x02);
   sati_set_data_byte(sequence, scsi_io, 3, 0x38);

   //Reserved SAT2r07
   sati_set_data_byte(sequence, scsi_io, 4, 0x00);
   sati_set_data_byte(sequence, scsi_io, 5, 0x00);
   sati_set_data_byte(sequence, scsi_io, 6, 0x00);
   sati_set_data_byte(sequence, scsi_io, 7, 0x00);

   // The Vender identification field is set to "ATA     "
   sati_set_data_byte(sequence, scsi_io, 8, 0x41);
   sati_set_data_byte(sequence, scsi_io, 9, 0x54);
   sati_set_data_byte(sequence, scsi_io, 10, 0x41);
   sati_set_data_byte(sequence, scsi_io, 11, 0x20);
   sati_set_data_byte(sequence, scsi_io, 12, 0x20);
   sati_set_data_byte(sequence, scsi_io, 13, 0x20);
   sati_set_data_byte(sequence, scsi_io, 14, 0x20);
   sati_set_data_byte(sequence, scsi_io, 15, 0x20);

   //SAT Product identification
   sati_ata_identify_device_copy_data(
      sequence,
      scsi_io,
      16,
      ata_input_data,
      ATA_IDENTIFY_DEVICE_GET_OFFSET(model_number),
      16,
      TRUE
   );

   //SAT Product Revision level bytes 32-35
   sati_inquiry_construct_product_revision(
      sequence,
      ata_input_data,
      scsi_io
   );

   //skipping ATA device signature for now

   //Command code
   sati_set_data_byte(sequence, scsi_io, 56, 0xEC);

   //Reserved SAT2r07
   sati_set_data_byte(sequence, scsi_io, 57, 0x00);
   sati_set_data_byte(sequence, scsi_io, 58, 0x00);
   sati_set_data_byte(sequence, scsi_io, 59, 0x00);

   //copy all ATA identify device data
   sati_ata_identify_device_copy_data(
      sequence,
      scsi_io,
      60,
      ata_input_data,
      0,
      sizeof(ATA_IDENTIFY_DEVICE_DATA_T),
      FALSE
   );

   //Need to send ATA Execute Device Diagnostic command still
   sequence->state = SATI_SEQUENCE_STATE_INCOMPLETE;

   return SATI_SEQUENCE_INCOMPLETE;
}