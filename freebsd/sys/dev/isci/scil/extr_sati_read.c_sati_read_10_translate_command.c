#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int U32 ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_READ_10 ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 scalar_t__ sati_device_state_stopped (TYPE_1__*,void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_read_32_bit_lba_translate_command (TYPE_1__*,void*,void*,int,int) ; 

SATI_STATUS sati_read_10_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{

   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   U32 sector_count = (sati_get_cdb_byte(cdb, 7) << 8) |
                      (sati_get_cdb_byte(cdb, 8));

   if(sati_device_state_stopped(sequence, scsi_io))
   {
      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }
   else
   {
      sequence->type = SATI_SEQUENCE_READ_10;

      return sati_read_32_bit_lba_translate_command(
                sequence, scsi_io, ata_io, sector_count, 9
             );
   }
}