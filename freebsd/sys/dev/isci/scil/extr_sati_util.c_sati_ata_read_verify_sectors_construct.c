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

/* Variables and functions */
 int /*<<< orphan*/  ATA_READ_VERIFY_SECTORS ; 
 int /*<<< orphan*/  sati_ata_non_data_command (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_set_ata_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count (int /*<<< orphan*/ *,int) ; 

void sati_ata_read_verify_sectors_construct(
   void                       * ata_io,
   SATI_TRANSLATOR_SEQUENCE_T * sequence
)
{
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   sati_set_ata_command(register_fis, ATA_READ_VERIFY_SECTORS);

   //According to SAT-2 (v7) 9.11.3
   sati_set_ata_sector_count(register_fis, 1);

   //According to SAT-2 (v7) 9.11.3, set LBA to a value between zero and the
   //maximum LBA supported by the ATA device in its current configuration.
   //From the unit test, it seems we have to set LBA to a non-zero value.
   sati_set_ata_lba_low(register_fis, 1);

   sati_ata_non_data_command(ata_io, sequence);
}