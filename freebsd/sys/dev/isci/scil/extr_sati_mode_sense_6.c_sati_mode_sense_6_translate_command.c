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
struct TYPE_4__ {int /*<<< orphan*/  allocation_length; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/  sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_mode_sense_translate_command (TYPE_1__*,void*,void*,int) ; 

SATI_STATUS sati_mode_sense_6_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb = sati_cb_get_cdb_address(scsi_io);

   // Set the data length based on the allocation length field in the CDB.
   sequence->allocation_length = sati_get_cdb_byte(cdb, 4);

   return sati_mode_sense_translate_command(sequence, scsi_io, ata_io, 6);
}