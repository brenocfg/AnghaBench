#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ block_lists_size; scalar_t__ size_of_data_processed; scalar_t__ current_lba_processed; scalar_t__ ata_command_sent_for_current_lba; } ;
struct TYPE_8__ {TYPE_3__ reassign_blocks_process_state; } ;
struct TYPE_9__ {scalar_t__ state; int /*<<< orphan*/  type; TYPE_1__ command_specific_data; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  scalar_t__ SATI_STATUS ;
typedef  TYPE_3__ SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_REASSIGN_BLOCKS ; 
 void* SATI_SEQUENCE_STATE_FINAL ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 
 int /*<<< orphan*/  SCSI_ASCQ_UNRECOVERED_READ_ERROR_AUTO_REALLOCATE_FAIL ; 
 int /*<<< orphan*/  SCSI_ASC_UNRECOVERED_READ_ERROR ; 
 int /*<<< orphan*/  SCSI_SENSE_MEDIUM_ERROR ; 
 int /*<<< orphan*/  SCSI_STATUS_CHECK_CONDITION ; 
 int /*<<< orphan*/  sati_reassign_blocks_initial_processing (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_reassign_blocks_process (TYPE_2__*,void*,void*) ; 
 int /*<<< orphan*/  sati_scsi_sense_data_construct (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_reassign_blocks_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_STATUS status = SATI_FAILURE_CHECK_RESPONSE_DATA;
   SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T * reassign_blocks_process_state;

   reassign_blocks_process_state = &sequence->command_specific_data.reassign_blocks_process_state;

   sequence->type = SATI_SEQUENCE_REASSIGN_BLOCKS;

   //Initial processing if
   if ( sequence->state != SATI_SEQUENCE_STATE_INCOMPLETE )
   {
      sati_reassign_blocks_initial_processing(
         sequence,
         scsi_io,
         ata_io
      );
   }

   // start processing current lba
   if(reassign_blocks_process_state->current_lba_processed)
   {
      reassign_blocks_process_state->ata_command_sent_for_current_lba = 0;
      reassign_blocks_process_state->current_lba_processed = FALSE;
   }

   status = sati_reassign_blocks_process(sequence, scsi_io, ata_io);

   if(reassign_blocks_process_state->block_lists_size ==
      reassign_blocks_process_state->size_of_data_processed)
   {
      // Done this lba
      sequence->state = SATI_SEQUENCE_STATE_FINAL;
   }
   else
   {
      sequence->state = SATI_SEQUENCE_STATE_INCOMPLETE;
   }

   if(status == SATI_FAILURE_CHECK_RESPONSE_DATA)
   {
      sequence->state = SATI_SEQUENCE_STATE_FINAL;
      sati_scsi_sense_data_construct(
         sequence,
         scsi_io,
         SCSI_STATUS_CHECK_CONDITION,
         SCSI_SENSE_MEDIUM_ERROR,
         SCSI_ASC_UNRECOVERED_READ_ERROR,
         SCSI_ASCQ_UNRECOVERED_READ_ERROR_AUTO_REALLOCATE_FAIL
      );
   }

   return status;
}