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
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_move_translate_command (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid (int /*<<< orphan*/ *,int) ; 

SATI_STATUS sati_move_6_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb          = sati_cb_get_cdb_address(scsi_io);
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   // Translate the logical block address information from the SCSI CDB.
   // There is only 5 bits of MSB located in byte 1 of the CDB.
   sati_set_ata_lba_low(register_fis, sati_get_cdb_byte(cdb, 3));
   sati_set_ata_lba_mid(register_fis, sati_get_cdb_byte(cdb, 2));
   sati_set_ata_lba_high(register_fis, sati_get_cdb_byte(cdb, 1) & 0x1F);

   sati_move_translate_command(sequence, scsi_io, ata_io, 0);

   return SATI_SUCCESS;
}