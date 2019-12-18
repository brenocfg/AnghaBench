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
typedef  int U8 ;
typedef  int U32 ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_FINAL ; 
 int* sati_cb_get_d2h_register_fis_address (void*) ; 
 int sati_get_ata_device (int*) ; 
 scalar_t__ sati_get_ata_error (int*) ; 
 int sati_get_ata_lba_high (int*) ; 
 int sati_get_ata_lba_high_ext (int*) ; 
 int sati_get_ata_lba_low (int*) ; 
 int sati_get_ata_lba_low_ext (int*) ; 
 int sati_get_ata_lba_mid (int*) ; 
 int sati_get_ata_lba_mid_ext (int*) ; 
 int sati_get_ata_sector_count (int*) ; 
 int sati_get_ata_sector_count_exp (int*) ; 
 scalar_t__ sati_get_ata_status (int*) ; 
 int /*<<< orphan*/  sati_set_data_byte (TYPE_1__*,void*,int,int) ; 

void sati_inquiry_ata_information_finish_translation(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);
   U32 offset;

   //SATA transport
   sati_set_data_byte(sequence, scsi_io, 36, 0x34);
   sati_set_data_byte(sequence, scsi_io, 37, 0x00);
   sati_set_data_byte(sequence, scsi_io, 38, (U8) sati_get_ata_status(register_fis));
   sati_set_data_byte(sequence, scsi_io, 39, (U8) sati_get_ata_error(register_fis));
   sati_set_data_byte(sequence, scsi_io, 40, sati_get_ata_lba_low(register_fis));
   sati_set_data_byte(sequence, scsi_io, 41, sati_get_ata_lba_mid(register_fis));
   sati_set_data_byte(sequence, scsi_io, 42, sati_get_ata_lba_high(register_fis));
   sati_set_data_byte(sequence, scsi_io, 43, sati_get_ata_device(register_fis));
   sati_set_data_byte(sequence, scsi_io, 44, sati_get_ata_lba_low_ext(register_fis));
   sati_set_data_byte(sequence, scsi_io, 45, sati_get_ata_lba_mid_ext(register_fis));
   sati_set_data_byte(sequence, scsi_io, 46, sati_get_ata_lba_high_ext(register_fis));
   sati_set_data_byte(sequence, scsi_io, 47, 0x00);
   sati_set_data_byte(sequence, scsi_io, 48, sati_get_ata_sector_count(register_fis));
   sati_set_data_byte(sequence, scsi_io, 49, sati_get_ata_sector_count_exp(register_fis));

   for(offset = 50; offset < 56; offset++)
   {
      sati_set_data_byte(sequence, scsi_io, offset, 0x00);
   }

   sequence->state = SATI_SEQUENCE_STATE_FINAL;
}