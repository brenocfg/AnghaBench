#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_8__ {int ata_command_sent_for_current_lba; int /*<<< orphan*/  current_lba_processed; int /*<<< orphan*/  ata_command_status; scalar_t__ lba_size; int /*<<< orphan*/  size_of_data_processed; } ;
struct TYPE_6__ {TYPE_3__ reassign_blocks_process_state; } ;
struct TYPE_7__ {scalar_t__ state; TYPE_1__ command_specific_data; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  TYPE_3__ SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T ;

/* Variables and functions */
 int ATA_STATUS_REG_ERROR_BIT ; 
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_REASSIGN_BLOCKS_COMMAND_FAIL ; 
 int /*<<< orphan*/  SATI_REASSIGN_BLOCKS_COMMAND_SUCCESS ; 
 int /*<<< orphan*/  SATI_SEQUENCE_INCOMPLETE ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int /*<<< orphan*/  SCSI_ASCQ_UNRECOVERED_READ_ERROR_AUTO_REALLOCATE_FAIL ; 
 int /*<<< orphan*/  SCSI_ASC_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_SENSE_MEDIUM_ERROR ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 int sati_get_ata_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_reassign_blocks_translate_response(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * register_fis = sati_cb_get_d2h_register_fis_address(ata_io);
   SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T * reassign_blocks_process_state;

   reassign_blocks_process_state = &sequence->command_specific_data.reassign_blocks_process_state;

   if (sati_get_ata_status(register_fis) & ATA_STATUS_REG_ERROR_BIT)
   {
      reassign_blocks_process_state->ata_command_status = SATI_REASSIGN_BLOCKS_COMMAND_FAIL;

      //Checking for the number of ATA commands attempted on current LBA, stop
      //the seaquence after 2 commands have returned errors.
      if(reassign_blocks_process_state->ata_command_sent_for_current_lba < 2)
      {
         sequence->state = SATI_SEQUENCE_STATE_INCOMPLETE;
         reassign_blocks_process_state->size_of_data_processed -= reassign_blocks_process_state->lba_size;
         return SATI_SEQUENCE_INCOMPLETE;
      }
      else
      {
         sati_scsi_sense_data_construct(
            sequence,
            scsi_io,
            SCSI_STATUS_CHECK_CONDITION,
            SCSI_SENSE_MEDIUM_ERROR,
            SCSI_ASC_UNRECOVERED_READ_ERROR,
            SCSI_ASCQ_UNRECOVERED_READ_ERROR_AUTO_REALLOCATE_FAIL
         );
      }

      return SATI_FAILURE_CHECK_RESPONSE_DATA;
   }
   else
   {
      reassign_blocks_process_state->ata_command_status = SATI_REASSIGN_BLOCKS_COMMAND_SUCCESS;
      if (reassign_blocks_process_state->ata_command_sent_for_current_lba != 2)
         reassign_blocks_process_state->current_lba_processed = TRUE;

      if (sequence->state == SATI_SEQUENCE_STATE_INCOMPLETE)
      {
         return SATI_SEQUENCE_INCOMPLETE;
      }
   }
   return SATI_COMPLETE;
}