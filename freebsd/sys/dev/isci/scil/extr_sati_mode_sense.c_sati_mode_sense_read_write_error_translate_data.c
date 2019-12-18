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
typedef  int U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_MODE_PAGE_READ_WRITE_ERROR ; 
 int SCSI_MODE_SENSE_PC_SHIFT ; 
 int* sati_cb_get_cdb_address (void*) ; 
 int sati_get_cdb_byte (int*,int) ; 
 int /*<<< orphan*/  sati_mode_sense_copy_initial_data (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

U32 sati_mode_sense_read_write_error_translate_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   U32                          offset
)
{
   U8 * cdb          = sati_cb_get_cdb_address(scsi_io);
   U8   page_control = sati_get_cdb_byte(cdb, 2) >> SCSI_MODE_SENSE_PC_SHIFT;
   U32  page_length;

   page_length = sati_mode_sense_copy_initial_data(
                    sequence,
                    scsi_io,
                    offset,
                    page_control,
                    SCSI_MODE_PAGE_READ_WRITE_ERROR
                 );

   // Currently we do not override any bits in this mode page from the
   // identify data.

   return page_length;
}