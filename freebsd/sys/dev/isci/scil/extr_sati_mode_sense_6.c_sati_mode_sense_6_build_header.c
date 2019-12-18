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
typedef  scalar_t__ U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int SATI_DEVICE_CAP_DMA_FUA_ENABLE ; 
 scalar_t__ SCSI_MODE_HEADER_MEDIUM_TYPE_SBC ; 
 int /*<<< orphan*/  SCSI_MODE_SENSE_6_HEADER_LENGTH ; 
 int SCSI_MODE_SENSE_DBD_ENABLE ; 
 scalar_t__ SCSI_MODE_SENSE_HEADER_FUA_ENABLE ; 
 scalar_t__ SCSI_MODE_SENSE_STD_BLOCK_DESCRIPTOR_LENGTH ; 
 scalar_t__* sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (scalar_t__*,int) ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_2__*,void*,int,scalar_t__) ; 

__attribute__((used)) static
U32 sati_mode_sense_6_build_header(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   U8                           mode_data_length
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   // Fill in the length of the mode parameter data returned (do not include
   // the size of the mode data length field in the total).
   sati_set_data_byte(sequence, scsi_io, 0, (U8)mode_data_length-1);

   // Medium Type is 0 for SBC devices
   sati_set_data_byte(sequence, scsi_io, 1, SCSI_MODE_HEADER_MEDIUM_TYPE_SBC);

   // Write Protect (WP), Rsvd, DPOFUA, Rsvd
   if (sequence->device->capabilities & SATI_DEVICE_CAP_DMA_FUA_ENABLE)
      sati_set_data_byte(sequence,scsi_io,2,SCSI_MODE_SENSE_HEADER_FUA_ENABLE);
   else
      sati_set_data_byte(sequence, scsi_io, 2, 0);

   // Set the block descriptor length if block descriptors are utilized.
   if (sati_get_cdb_byte(cdb, 1) & SCSI_MODE_SENSE_DBD_ENABLE)
      sati_set_data_byte(sequence, scsi_io, 3, 0);
   else
      sati_set_data_byte(
         sequence, scsi_io, 3, SCSI_MODE_SENSE_STD_BLOCK_DESCRIPTOR_LENGTH
      );

   return SCSI_MODE_SENSE_6_HEADER_LENGTH;
}