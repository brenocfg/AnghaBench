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
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_3__ {scalar_t__ ata_transfer_length; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CONTROL_REG_SOFT_RESET_BIT ; 
 int /*<<< orphan*/  ATA_NOP ; 
 int /*<<< orphan*/  SATI_DATA_DIRECTION_NONE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_LUN_RESET ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SAT_PROTOCOL_SOFT_RESET ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_clear_sata_command_flag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_set_ata_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_device_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_features (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_features_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_high_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_low_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_lba_mid_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_lun_reset_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8* register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   sati_set_ata_command(register_fis, ATA_NOP);
   sati_set_ata_control(register_fis, ATA_CONTROL_REG_SOFT_RESET_BIT);

   //set all other fields to zero.
   sati_clear_sata_command_flag(register_fis);
   sati_set_ata_features(register_fis, 0);
   sati_set_ata_features_exp(register_fis, 0);
   sati_set_ata_sector_count(register_fis, 0);
   sati_set_ata_sector_count_exp(register_fis, 0);
   sati_set_ata_lba_low(register_fis, 0);
   sati_set_ata_lba_mid(register_fis, 0);
   sati_set_ata_lba_high(register_fis, 0);
   sati_set_ata_lba_low_exp(register_fis, 0);
   sati_set_ata_lba_mid_exp(register_fis, 0);
   sati_set_ata_lba_high_exp(register_fis, 0);
   sati_set_ata_device_head(register_fis, 0);

   sequence->type                = SATI_SEQUENCE_LUN_RESET;
   sequence->data_direction      = SATI_DATA_DIRECTION_NONE;
   sequence->protocol            = SAT_PROTOCOL_SOFT_RESET;
   sequence->ata_transfer_length = 0;

   return SATI_SUCCESS;
}