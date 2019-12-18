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

/* Variables and functions */
 int ATA_DEV_HEAD_REG_LBA_MODE_ENABLE ; 
 int* sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_set_ata_device_head (int*,int) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high (int*,int) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low (int*,int) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid (int*,int) ; 

__attribute__((used)) static
void set_current_lba(U8 * lba, void  * ata_io)
{
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   sati_set_ata_lba_low(register_fis, lba[0]);
   sati_set_ata_lba_mid(register_fis, lba[1]);
   sati_set_ata_lba_high(register_fis, lba[2]);
   sati_set_ata_device_head(register_fis, ATA_DEV_HEAD_REG_LBA_MODE_ENABLE | (lba[3] & 0x0F));


}