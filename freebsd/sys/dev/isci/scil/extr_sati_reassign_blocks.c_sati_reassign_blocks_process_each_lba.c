#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ata_command_sent_for_current_lba; scalar_t__ ata_command_status; scalar_t__ lba_size; int /*<<< orphan*/  size_of_data_processed; int /*<<< orphan*/  lba_offset; } ;
struct TYPE_7__ {TYPE_3__ reassign_blocks_process_state; } ;
struct TYPE_8__ {TYPE_1__ command_specific_data; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  TYPE_3__ SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 scalar_t__ SATI_REASSIGN_BLOCKS_COMMAND_FAIL ; 
 scalar_t__ SATI_REASSIGN_BLOCKS_COMMAND_SUCCESS ; 
 int /*<<< orphan*/  sati_reassign_blocks_verify_condition (TYPE_2__*,void*,void*) ; 
 int /*<<< orphan*/  sati_reassign_blocks_write_condition (TYPE_2__*,void*,void*) ; 

__attribute__((used)) static
SATI_STATUS sati_reassign_blocks_process_each_lba(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
   )
{
   SATI_STATUS status = SATI_FAILURE_CHECK_RESPONSE_DATA;
   SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T * reassign_blocks_process_state;

   reassign_blocks_process_state = &sequence->command_specific_data.reassign_blocks_process_state;

   if((reassign_blocks_process_state->ata_command_sent_for_current_lba == 0)&&
      (reassign_blocks_process_state->ata_command_status == SATI_REASSIGN_BLOCKS_COMMAND_FAIL))
   {
      reassign_blocks_process_state->size_of_data_processed += reassign_blocks_process_state->lba_size;
      status = sati_reassign_blocks_verify_condition(sequence, scsi_io, ata_io);
   }
   else if((reassign_blocks_process_state->ata_command_sent_for_current_lba == 0)&&
      (reassign_blocks_process_state->ata_command_status == SATI_REASSIGN_BLOCKS_COMMAND_SUCCESS))
   {
      // point to next lba
      reassign_blocks_process_state->size_of_data_processed += reassign_blocks_process_state->lba_size;
      reassign_blocks_process_state->lba_offset += reassign_blocks_process_state->lba_size;
      status = sati_reassign_blocks_verify_condition(sequence, scsi_io, ata_io);
   }
   else if((reassign_blocks_process_state->ata_command_sent_for_current_lba == 1)&&
      (reassign_blocks_process_state->ata_command_status == SATI_REASSIGN_BLOCKS_COMMAND_FAIL))
   {
      reassign_blocks_process_state->size_of_data_processed += reassign_blocks_process_state->lba_size;
      status = sati_reassign_blocks_write_condition(sequence, scsi_io, ata_io);
   }
   else if((reassign_blocks_process_state->ata_command_sent_for_current_lba == 2) &&
      (reassign_blocks_process_state->ata_command_status == SATI_REASSIGN_BLOCKS_COMMAND_SUCCESS))
   {
      reassign_blocks_process_state->size_of_data_processed += reassign_blocks_process_state->lba_size;
      status = sati_reassign_blocks_verify_condition(sequence, scsi_io, ata_io);
   }
   else //commands sent is 2; SATI_REASSIGN_BLOCKS_COMMAND_FAIL
   {
      status = SATI_FAILURE_CHECK_RESPONSE_DATA;
   }

   return status;
}