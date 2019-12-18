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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_get_ata_lba_high (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_get_ata_lba_high_ext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_get_ata_lba_low (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_get_ata_lba_low_ext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_get_ata_lba_mid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_get_ata_lba_mid_ext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_common_descriptor_sense_construct (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_get_sense_data_buffer (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_set_sense_data_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void sati_scsi_read_error_descriptor_sense_construct(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U8                           scsi_status,
   U8                           response_code,
   U8                           sense_key,
   U8                           additional_sense_code,
   U8                           additional_sense_code_qualifier
)
{
   U8 * sense_data;
   U32  sense_len;
   U8 information_buff[8] = {0};

   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);

   sati_scsi_get_sense_data_buffer(sequence, scsi_io, scsi_status, &sense_data, &sense_len);

   information_buff[2] = sati_get_ata_lba_high_ext(register_fis);
   information_buff[3] = sati_get_ata_lba_mid_ext(register_fis);
   information_buff[4] = sati_get_ata_lba_low_ext(register_fis);
   information_buff[5] = sati_get_ata_lba_high(register_fis);
   information_buff[6] = sati_get_ata_lba_mid(register_fis);
   information_buff[7] = sati_get_ata_lba_low(register_fis);

   sati_set_sense_data_byte(
      sense_data,
      sense_len,
      0,
      SCSI_DESCRIPTOR_CURRENT_RESPONSE_CODE
   );

   sati_scsi_common_descriptor_sense_construct(
      sequence,
      scsi_io,
      sense_data,
      sense_len,
      sense_key,
      additional_sense_code,
      additional_sense_code_qualifier,
      information_buff
   );
}