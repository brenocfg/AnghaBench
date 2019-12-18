#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int /*<<< orphan*/  lba_7_0; int /*<<< orphan*/  lba_15_8; int /*<<< orphan*/  lba_23_16; int /*<<< orphan*/  lba_31_24; int /*<<< orphan*/  lba_39_32; int /*<<< orphan*/  lba_47_40; } ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  TYPE_1__ ATA_NCQ_COMMAND_ERROR_LOG_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_scsi_common_descriptor_sense_construct (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_get_sense_data_buffer (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_set_sense_data_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void sati_scsi_read_ncq_error_descriptor_sense_construct(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_input_data,
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

   ATA_NCQ_COMMAND_ERROR_LOG_T * ncq_log = (ATA_NCQ_COMMAND_ERROR_LOG_T *) ata_input_data;

   sati_scsi_get_sense_data_buffer(sequence, scsi_io, scsi_status, &sense_data, &sense_len);

   sati_set_sense_data_byte(
      sense_data,
      sense_len,
      0,
      response_code
   );

   information_buff[2] = ncq_log->lba_47_40;
   information_buff[3] = ncq_log->lba_39_32;
   information_buff[4] = ncq_log->lba_31_24;
   information_buff[5] = ncq_log->lba_23_16;
   information_buff[6] = ncq_log->lba_15_8;
   information_buff[7] = ncq_log->lba_7_0;

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