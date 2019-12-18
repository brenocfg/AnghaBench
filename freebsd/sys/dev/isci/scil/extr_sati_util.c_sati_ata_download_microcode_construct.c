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
typedef  int U32 ;
struct TYPE_4__ {int ata_transfer_length; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data_direction; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DOWNLOAD_MICROCODE ; 
 int /*<<< orphan*/  ATA_MICROCODE_DOWNLOAD_SAVE ; 
 int /*<<< orphan*/  SATI_DATA_DIRECTION_OUT ; 
 int /*<<< orphan*/  SAT_PROTOCOL_PIO_DATA_OUT ; 
 int /*<<< orphan*/  sati_ata_non_data_command (void*,TYPE_1__*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_set_ata_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_features (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sati_ata_download_microcode_construct(
   void                       * ata_io,
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   U8                           mode,
   U32                          allocation_length,
   U32                          buffer_offset
)
{
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);
   U32 allocation_blocks = allocation_length >> 9;
   U32 buffer_blkoffset = buffer_offset >> 9;

   sati_set_ata_command(register_fis, ATA_DOWNLOAD_MICROCODE);
   sati_set_ata_features(register_fis, mode);

   if(mode == ATA_MICROCODE_DOWNLOAD_SAVE)
   {
      sati_set_ata_sector_count(register_fis, (U8) (allocation_length >> 9));
      sati_set_ata_lba_low(register_fis, (U8) (allocation_length >> 17));
   }
   else //mode == 0x03
   {
      sati_set_ata_sector_count(register_fis, (U8) (allocation_blocks & 0xff));
      sati_set_ata_lba_low(register_fis, (U8) ((allocation_blocks >> 8) & 0xff));
      sati_set_ata_lba_mid(register_fis, (U8) (buffer_blkoffset & 0xff));
      sati_set_ata_lba_high(register_fis, (U8) ((buffer_blkoffset >> 8) & 0xff));
   }

   if((allocation_length == 0) && (buffer_offset == 0))
   {
      sati_ata_non_data_command(ata_io, sequence);
   }
   else
   {
      sequence->data_direction      = SATI_DATA_DIRECTION_OUT;
      sequence->protocol            = SAT_PROTOCOL_PIO_DATA_OUT;
      sequence->ata_transfer_length = allocation_length;
   }
}