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
struct TYPE_2__ {int* firmware_revision; } ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_1__ ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 scalar_t__ ATA_IDENTIFY_DEVICE_GET_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  firmware_revision ; 
 int /*<<< orphan*/  sati_ata_identify_device_copy_data (int /*<<< orphan*/ *,void*,int,void*,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void sati_inquiry_construct_product_revision(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * ata_input_data,
   void                       * scsi_io
)
{
   ATA_IDENTIFY_DEVICE_DATA_T * identify = (ATA_IDENTIFY_DEVICE_DATA_T*)
      ata_input_data;

   // Fill in the product revision level field.
   // Per SAT, copy portions of the firmware revision that is not filled
   // with spaces.  Some devices left-align their firmware rev ID, while
   // others right-align.
   if (  (identify->firmware_revision[4] == 0x20)
       && (identify->firmware_revision[5] == 0x20)
       && (identify->firmware_revision[6] == 0x20)
       && (identify->firmware_revision[7] == 0x20) )
   {
      sati_ata_identify_device_copy_data(
         sequence,
         scsi_io,
         32,
         ata_input_data,
         ATA_IDENTIFY_DEVICE_GET_OFFSET(firmware_revision),
         4,
         TRUE
       );
   }
   else
   {
      // Since the last 4 bytes of the firmware revision are not spaces,
      // utilize these bytes as the firmware revision in the inquiry data.
      sati_ata_identify_device_copy_data(
         sequence,
         scsi_io,
         32,
         ata_input_data,
         ATA_IDENTIFY_DEVICE_GET_OFFSET(firmware_revision)+4,
         4,
         TRUE
      );
   }
}