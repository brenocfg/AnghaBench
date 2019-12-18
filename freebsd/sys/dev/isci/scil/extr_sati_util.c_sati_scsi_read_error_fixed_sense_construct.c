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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int FALSE ; 
 int SCSI_FIXED_CURRENT_RESPONSE_CODE ; 
 int TRUE ; 
 int* sati_cb_get_d2h_register_fis_address (void*) ; 
 int sati_get_ata_lba_high (int*) ; 
 int sati_get_ata_lba_low (int*) ; 
 int sati_get_ata_lba_low_ext (int*) ; 
 int sati_get_ata_lba_mid (int*) ; 
 scalar_t__ sati_get_ata_lba_mid_ext (int*) ; 
 int /*<<< orphan*/  sati_scsi_common_fixed_sense_construct (int*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sati_scsi_get_sense_data_buffer (int /*<<< orphan*/ *,void*,int,int**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_set_sense_data_byte (int*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static
void sati_scsi_read_error_fixed_sense_construct(
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
   U8   valid = TRUE;

   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);

   sati_scsi_get_sense_data_buffer(sequence, scsi_io, scsi_status, &sense_data, &sense_len);

   if(sati_get_ata_lba_mid_ext(register_fis) > 0)
   {
      valid = FALSE;
   }

   sati_set_sense_data_byte(sense_data, sense_len, 3,  sati_get_ata_lba_low_ext(register_fis));
   sati_set_sense_data_byte(sense_data, sense_len, 4,  sati_get_ata_lba_high(register_fis));
   sati_set_sense_data_byte(sense_data, sense_len, 5,  sati_get_ata_lba_mid(register_fis));
   sati_set_sense_data_byte(sense_data, sense_len, 6,  sati_get_ata_lba_low(register_fis));


   sati_set_sense_data_byte(
      sense_data,
      sense_len,
      0,
      (valid << 7) | SCSI_FIXED_CURRENT_RESPONSE_CODE
   );

   sati_scsi_common_fixed_sense_construct(
      sense_data,
      sense_len,
      sense_key,
      additional_sense_code,
      additional_sense_code_qualifier
   );
}