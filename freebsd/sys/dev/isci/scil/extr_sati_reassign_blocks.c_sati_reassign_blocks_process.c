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
typedef  scalar_t__ U32 ;
struct TYPE_9__ {scalar_t__ lba_offset; scalar_t__ lba_size; scalar_t__ block_lists_size; scalar_t__ size_of_data_processed; } ;
struct TYPE_7__ {TYPE_3__ reassign_blocks_process_state; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; TYPE_1__ command_specific_data; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  TYPE_3__ SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_FINAL ; 
 int /*<<< orphan*/  sati_reassign_blocks_process_each_lba (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_reassign_blocks_unprocessed_data_size (TYPE_3__*) ; 

__attribute__((used)) static
SATI_STATUS sati_reassign_blocks_process(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_STATUS status = SATI_FAILURE_CHECK_RESPONSE_DATA;

   U32 page_size = 0; // in bytes
   U32 size_of_data_to_be_processed;
   U32 lba_offset;
   SATI_REASSIGN_BLOCKS_PROCESSING_STATE_T * reassign_blocks_process_state;

   reassign_blocks_process_state = &sequence->command_specific_data.reassign_blocks_process_state;

   lba_offset = reassign_blocks_process_state->lba_offset;
   page_size  = reassign_blocks_process_state->lba_size;


   if(sati_reassign_blocks_unprocessed_data_size(reassign_blocks_process_state) < page_size)
   {
      return status;
   }

   // Any more lba blocks? If not, done.
   if(reassign_blocks_process_state->block_lists_size ==
      reassign_blocks_process_state->size_of_data_processed)
   {
      sequence->state = SATI_SEQUENCE_STATE_FINAL;
      status = SATI_COMPLETE;
   }
   //start processing next lba
   else
   {
      size_of_data_to_be_processed = reassign_blocks_process_state->block_lists_size
         - reassign_blocks_process_state->size_of_data_processed;

      status = sati_reassign_blocks_process_each_lba(sequence, scsi_io, ata_io);

   }

   return status;
}