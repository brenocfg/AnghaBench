#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_4__ {int allocation_length; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_1__*,void*,int,int) ; 

SATI_STATUS sati_report_luns_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   // Set the data length based on the allocation length field in the CDB.
   sequence->allocation_length = (sati_get_cdb_byte(cdb, 6) << 24) |
                                 (sati_get_cdb_byte(cdb, 7) << 16) |
                                 (sati_get_cdb_byte(cdb, 8) << 8)  |
                                 (sati_get_cdb_byte(cdb, 9));

   // The first 4 bytes indicate the length of the LUN list.  Each
   // LUN entry is 8 bytes.  There is only ever LUN 0 for ATA/ATAPI
   // devices.  The value reported is: n-7, where n is the last byte
   // offset (i.e. 15) in the REPORT LUN data.
   sati_set_data_byte(sequence, scsi_io, 0, 0);
   sati_set_data_byte(sequence, scsi_io, 1, 0);
   sati_set_data_byte(sequence, scsi_io, 2, 0);
   sati_set_data_byte(sequence, scsi_io, 3, 8);

   // Bytes 4-7 are reserved.
   sati_set_data_byte(sequence, scsi_io, 4, 0);
   sati_set_data_byte(sequence, scsi_io, 5, 0);
   sati_set_data_byte(sequence, scsi_io, 6, 0);
   sati_set_data_byte(sequence, scsi_io, 7, 0);

   // Add in our single LUN of zero.
   sati_set_data_byte(sequence, scsi_io, 8, 0);
   sati_set_data_byte(sequence, scsi_io, 9, 0);
   sati_set_data_byte(sequence, scsi_io, 10, 0);
   sati_set_data_byte(sequence, scsi_io, 11, 0);
   sati_set_data_byte(sequence, scsi_io, 12, 0);
   sati_set_data_byte(sequence, scsi_io, 13, 0);
   sati_set_data_byte(sequence, scsi_io, 14, 0);
   sati_set_data_byte(sequence, scsi_io, 15, 0);

   return SATI_COMPLETE;
}