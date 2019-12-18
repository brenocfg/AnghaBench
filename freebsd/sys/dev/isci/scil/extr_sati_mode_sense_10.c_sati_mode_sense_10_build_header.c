#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int U16 ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int SATI_DEVICE_CAP_DMA_FUA_ENABLE ; 
 int SCSI_MODE_HEADER_MEDIUM_TYPE_SBC ; 
 int /*<<< orphan*/  SCSI_MODE_SENSE_10_HEADER_LENGTH ; 
 int SCSI_MODE_SENSE_DBD_ENABLE ; 
 int SCSI_MODE_SENSE_HEADER_FUA_ENABLE ; 
 int SCSI_MODE_SENSE_LLBAA_ENABLE ; 
 int SCSI_MODE_SENSE_LLBA_BLOCK_DESCRIPTOR_LENGTH ; 
 int SCSI_MODE_SENSE_STD_BLOCK_DESCRIPTOR_LENGTH ; 
 int* sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int*,int) ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_2__*,void*,int,int) ; 

__attribute__((used)) static
U32 sati_mode_sense_10_build_header(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   U16                          mode_data_length
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   // Fill in the length of the mode parameter data returned (do not include
   // the size of the mode data length field in the total).  Adjust the
   // mode data length to not include the mode data length fields itself
   // (i.e. subtract 2).
   mode_data_length -= 2;
   sati_set_data_byte(sequence, scsi_io, 0, (U8)(mode_data_length >> 8) & 0xFF);
   sati_set_data_byte(sequence, scsi_io, 1, (U8)(mode_data_length & 0xFF));

   // Medium Type is 0 for SBC devices
   sati_set_data_byte(sequence, scsi_io, 2, SCSI_MODE_HEADER_MEDIUM_TYPE_SBC);

   // Write Protect (WP), Rsvd, DPOFUA, Rsvd
   if (sequence->device->capabilities & SATI_DEVICE_CAP_DMA_FUA_ENABLE)
      sati_set_data_byte(sequence,scsi_io,3,SCSI_MODE_SENSE_HEADER_FUA_ENABLE);
   else
      sati_set_data_byte(sequence, scsi_io, 3, 0);

   // Set the reserved bytes to 0.  The LONGLBA field in byte 4 is overridden
   // later in this method if LLBAA is enabled.
   sati_set_data_byte(sequence, scsi_io, 4, 0);
   sati_set_data_byte(sequence, scsi_io, 5, 0);

   // The MSB for the block descriptor length is never used since the
   // largest block descriptor in this translator is 16-bytes in size.
   sati_set_data_byte(sequence, scsi_io, 6, 0);

   // Set the LSB block descriptor length if block descriptors are utilized.
   if (sati_get_cdb_byte(cdb, 1) & SCSI_MODE_SENSE_DBD_ENABLE)
      sati_set_data_byte(sequence, scsi_io, 7, 0);
   else
   {
      // If Long Logical Block Address are allowed, then the block descriptor
      // is larger (16 bytes total).
      if (sati_get_cdb_byte(cdb, 1) & SCSI_MODE_SENSE_LLBAA_ENABLE)
      {
         sati_set_data_byte(sequence, scsi_io, 4, 1);
         sati_set_data_byte(
            sequence, scsi_io, 7, SCSI_MODE_SENSE_LLBA_BLOCK_DESCRIPTOR_LENGTH
         );
      }
      else
      {
         sati_set_data_byte(
            sequence, scsi_io, 7, SCSI_MODE_SENSE_STD_BLOCK_DESCRIPTOR_LENGTH
         );
      }
   }

   return SCSI_MODE_SENSE_10_HEADER_LENGTH;
}