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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int SCSI_MODE_SENSE_DBD_ENABLE ; 
 int SCSI_MODE_SENSE_LLBAA_ENABLE ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_mode_sense_10_build_header (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_10_build_llba_block_descriptor (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sati_mode_sense_build_std_block_descriptor (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
U32 sati_mode_sense_10_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   void                       * scsi_io,
   U16                          transfer_length
)
{
   U8  * cdb = sati_cb_get_cdb_address(scsi_io);
   U32   offset;

   offset = sati_mode_sense_10_build_header(
               sequence, scsi_io, identify, transfer_length
            );

   // Determine if the caller disabled block descriptors (DBD).  If not,
   // then generate a block descriptor.
   if ((sati_get_cdb_byte(cdb, 1) & SCSI_MODE_SENSE_DBD_ENABLE) == 0)
   {
      // If the user requested the Long LBA format descriptor, then build
      // it
      if (sati_get_cdb_byte(cdb, 1) & SCSI_MODE_SENSE_LLBAA_ENABLE)
         offset += sati_mode_sense_10_build_llba_block_descriptor(
                      sequence, scsi_io, identify, offset
                   );
      else
         offset += sati_mode_sense_build_std_block_descriptor(
                      sequence, scsi_io, identify, offset
                   );
   }

   return offset;
}