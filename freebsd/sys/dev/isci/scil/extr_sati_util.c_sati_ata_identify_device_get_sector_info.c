#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_3__ {int command_set_enabled1; int* max_48bit_lba; int* total_num_sectors; int physical_logical_sector_info; int* words_per_logical_sector; } ;
typedef  TYPE_1__ ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int ATA_IDENTIFY_COMMAND_SET_SUPPORTED1_48BIT_ENABLE ; 
 int ATA_IDENTIFY_SECTOR_LARGER_THEN_512_ENABLE ; 

void sati_ata_identify_device_get_sector_info(
   ATA_IDENTIFY_DEVICE_DATA_T * identify,
   U32                        * lba_high,
   U32                        * lba_low,
   U32                        * sector_size
)
{
   // Calculate the values to be returned
   // Calculation will be different if the SATA device supports
   // 48-bit addressing.  Bit 10 of Word 86 of ATA Identify
   if (identify->command_set_enabled1
       & ATA_IDENTIFY_COMMAND_SET_SUPPORTED1_48BIT_ENABLE)
   {
      // This drive supports 48-bit addressing

      *lba_high  = identify->max_48bit_lba[7] << 24;
      *lba_high |= identify->max_48bit_lba[6] << 16;
      *lba_high |= identify->max_48bit_lba[5] << 8;
      *lba_high |= identify->max_48bit_lba[4];

      *lba_low  = identify->max_48bit_lba[3] << 24;
      *lba_low |= identify->max_48bit_lba[2] << 16;
      *lba_low |= identify->max_48bit_lba[1] << 8;
      *lba_low |= identify->max_48bit_lba[0];
   }
   else
   {
      // This device doesn't support 48-bit addressing
      // Pull out the largest LBA from words 60 and 61.
      *lba_high  = 0;
      *lba_low   = identify->total_num_sectors[3] << 24;
      *lba_low  |= identify->total_num_sectors[2] << 16;
      *lba_low  |= identify->total_num_sectors[1] << 8;
      *lba_low  |= identify->total_num_sectors[0];
   }

   // If the ATA device reports its sector size (bit 12 of Word 106),
   // then use that instead.
   if (identify->physical_logical_sector_info
       & ATA_IDENTIFY_SECTOR_LARGER_THEN_512_ENABLE)
   {
      *sector_size  = identify->words_per_logical_sector[3] << 24;
      *sector_size |= identify->words_per_logical_sector[2] << 16;
      *sector_size |= identify->words_per_logical_sector[1] << 8;
      *sector_size |= identify->words_per_logical_sector[0];
   }
   else
   {
      // Default the sector size to 512 bytes
      *sector_size = 512;
   }
}