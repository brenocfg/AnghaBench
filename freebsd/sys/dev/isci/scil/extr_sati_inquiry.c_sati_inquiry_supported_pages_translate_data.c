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
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int SCSI_INQUIRY_ATA_INFORMATION_PAGE ; 
 int SCSI_INQUIRY_BLOCK_DEVICE_PAGE ; 
 int SCSI_INQUIRY_DEVICE_ID_PAGE ; 
 int SCSI_INQUIRY_SUPPORTED_PAGES_PAGE ; 
 int SCSI_INQUIRY_UNIT_SERIAL_NUM_PAGE ; 
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int) ; 

__attribute__((used)) static
void sati_inquiry_supported_pages_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io
)
{
   // Formulate the SCSI output data for the caller.
   sati_set_data_byte(sequence, scsi_io, 0, 0); // Qualifier and Device Type
   sati_set_data_byte(sequence, scsi_io, 1, SCSI_INQUIRY_SUPPORTED_PAGES_PAGE);
   sati_set_data_byte(sequence, scsi_io, 2, 0); // Reserved.
   sati_set_data_byte(sequence, scsi_io, 3, 4); // # VPD pages supported
   sati_set_data_byte(sequence, scsi_io, 4, SCSI_INQUIRY_SUPPORTED_PAGES_PAGE);
   sati_set_data_byte(sequence, scsi_io, 5, SCSI_INQUIRY_UNIT_SERIAL_NUM_PAGE);
   sati_set_data_byte(sequence, scsi_io, 6, SCSI_INQUIRY_DEVICE_ID_PAGE);
   sati_set_data_byte(sequence, scsi_io, 7, SCSI_INQUIRY_ATA_INFORMATION_PAGE);
   sati_set_data_byte(sequence, scsi_io, 8, SCSI_INQUIRY_BLOCK_DEVICE_PAGE);
   sati_set_data_byte(sequence, scsi_io, 9, 0); // End of the list
}