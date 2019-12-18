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

/* Variables and functions */
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 scalar_t__ sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_set_ata_features (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sati_set_ata_features_exp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
void sati_move_ncq_translate_8_bit_sector_count(
   void * scsi_io,
   void * ata_io
)
{
   U8 * cdb          = sati_cb_get_cdb_address(scsi_io);
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   sati_set_ata_features(register_fis, sati_get_cdb_byte(cdb, 4));

   // A read 6 with a 0 sector count indicates a transfer of 256 sectors.
   // As a result update the MSB (features expanded register) to indicate
   // 256 sectors (0x100).
   if (sati_get_cdb_byte(cdb, 4) == 0)
      sati_set_ata_features_exp(register_fis, 1);
}