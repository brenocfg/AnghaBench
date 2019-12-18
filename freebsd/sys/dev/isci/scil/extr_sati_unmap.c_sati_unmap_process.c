#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_15__ {scalar_t__ sector_address; scalar_t__ sector_count; } ;
struct TYPE_13__ {scalar_t__ max_lba_range_entries; scalar_t__ current_lba_count; scalar_t__ next_lba; scalar_t__ current_lba; scalar_t__ max_unmap_block_descriptors; int /*<<< orphan*/  physical_unmap_buffer_high; int /*<<< orphan*/  physical_unmap_buffer_low; int /*<<< orphan*/  unmap_buffer_sgl_pair; int /*<<< orphan*/ * current_dsm_descriptor; int /*<<< orphan*/ * virtual_unmap_buffer; } ;
struct TYPE_11__ {TYPE_3__ unmap_process_state; } ;
struct TYPE_14__ {int /*<<< orphan*/  state; TYPE_2__* device; TYPE_1__ command_specific_data; } ;
struct TYPE_12__ {scalar_t__ logical_block_size; } ;
typedef  int /*<<< orphan*/  TRIM_PAIR ;
typedef  TYPE_3__ SATI_UNMAP_PROCESSING_STATE_T ;
typedef  TYPE_4__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  scalar_t__ SATI_LBA ;
typedef  TYPE_5__* PTRIM_PAIR ;
typedef  int POINTER_UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SATI_DSM_MAX_SECTOR_ADDRESS ; 
 scalar_t__ SATI_DSM_MAX_SECTOR_COUNT ; 
 int /*<<< orphan*/  SATI_SEQUENCE_STATE_FINAL ; 
 int /*<<< orphan*/  SATI_SUCCESS_SGL_TRANSLATED ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sati_cb_sge_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sati_unmap_calculate_dsm_blocks (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  sati_unmap_construct (TYPE_4__*,void*,void*,scalar_t__) ; 
 scalar_t__ sati_unmap_get_max_buffer_size_in_blocks (TYPE_4__*) ; 
 int /*<<< orphan*/  sati_unmap_load_next_descriptor (TYPE_4__*,void*) ; 

SATI_STATUS sati_unmap_process(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_UNMAP_PROCESSING_STATE_T * unmap_process_state;
   SATI_LBA dsm_descriptor_lba_count;
   U32 dsm_descriptor;
   U32 dsm_bytes;
   U32 dsm_remainder_bytes;
   U32 dsm_blocks;
   U32 max_dsm_blocks;

   unmap_process_state = &sequence->command_specific_data.unmap_process_state;

   // Set up the starting address of the buffer for this portion of the translation
   unmap_process_state->current_dsm_descriptor = unmap_process_state->virtual_unmap_buffer;
   dsm_descriptor = 0;

   // Translate as much as we can
   while ((dsm_descriptor < unmap_process_state->max_lba_range_entries) &&
          (unmap_process_state->current_lba_count > 0)) {
      // See if the LBA count will fit in to a single descriptor
      if (unmap_process_state->current_lba_count > SATI_DSM_MAX_SECTOR_COUNT) {
         // Can't fit all of the lbas for this descriptor in to
         // one DSM request.  Adjust the current LbaCount and total
         // remaining for the next descriptor
         dsm_descriptor_lba_count = SATI_DSM_MAX_SECTOR_COUNT;
         unmap_process_state->current_lba_count -= SATI_DSM_MAX_SECTOR_COUNT;
         unmap_process_state->next_lba =
             unmap_process_state->current_lba + SATI_DSM_MAX_SECTOR_COUNT;
      } else {
         // It all fits in to one descriptor
         dsm_descriptor_lba_count = unmap_process_state->current_lba_count;
         unmap_process_state->current_lba_count = 0;
      }

      // Fill in the ATA DSM descriptor
      ((PTRIM_PAIR)(unmap_process_state->current_dsm_descriptor))->sector_address =
          unmap_process_state->current_lba;
      ((PTRIM_PAIR)(unmap_process_state->current_dsm_descriptor))->sector_count =
          dsm_descriptor_lba_count;

      // See if we can move on to the next descriptor
      if (unmap_process_state->current_lba_count == 0) {
         // See if there is another descriptor
         --unmap_process_state->max_unmap_block_descriptors;
         if (unmap_process_state->max_unmap_block_descriptors > 0) {
            // Move on to the next descriptor
            sati_unmap_load_next_descriptor(sequence,scsi_io);
         }
      } else {
         // Move to the next LBA in this descriptor
         unmap_process_state->current_lba = unmap_process_state->next_lba;
      }

      // Make sure the LBA does not exceed 48 bits...
      ASSERT(unmap_process_state->current_lba <= SATI_DSM_MAX_SECTOR_ADDRESS);

      // Increment the number of descriptors used and point to the next entry
      dsm_descriptor++;
      unmap_process_state->current_dsm_descriptor =
          (U8 *)(unmap_process_state->current_dsm_descriptor) + sizeof(TRIM_PAIR);
   }

   // Calculate number of blocks we have filled in
   dsm_blocks     = sati_unmap_calculate_dsm_blocks(sequence,dsm_descriptor);
   dsm_bytes      = dsm_blocks * sequence->device->logical_block_size;
   max_dsm_blocks = sati_unmap_get_max_buffer_size_in_blocks(sequence);

   // The current_dsm_descriptor points to the next location in the buffer
   // Get the remaining bytes from the last translated descriptor
   // to the end of the 4k buffer.
   dsm_remainder_bytes = sequence->device->logical_block_size;
   dsm_remainder_bytes -= (U32)((POINTER_UINT)unmap_process_state->current_dsm_descriptor &
                                (sequence->device->logical_block_size-1));

   // If there was no remainder, the complete buffer was filled in.
   if (dsm_remainder_bytes != sequence->device->logical_block_size)
   {
       // Add on the remaining unfilled blocks
       dsm_remainder_bytes += (sequence->device->logical_block_size * (max_dsm_blocks - dsm_blocks));

       // According to ATA-8, if the DSM buffer is not completely filled with
       // valid DSM descriptor data, the remaining portion of the
       // buffer must be filled in with zeros.
       memset((U8 *)unmap_process_state->current_dsm_descriptor, 0, dsm_remainder_bytes);
   }

   // Tell scic to utilize this sgl pair for write DMA processing of
   // the SCSI UNMAP translation with the total number of bytes for this transfer
   sati_cb_sge_write(unmap_process_state->unmap_buffer_sgl_pair,
                     unmap_process_state->physical_unmap_buffer_low,
                     unmap_process_state->physical_unmap_buffer_high,
                     dsm_bytes);

   // Construct the unmap ATA request
   sati_unmap_construct(sequence,
                        scsi_io,
                        ata_io,
                        dsm_blocks);

   // Determine sequence next state based on whether there is more translation
   // to complete
   if (unmap_process_state->current_lba_count == 0)
   {
       // used for completion routine to determine if there is more processing
       sequence->state = SATI_SEQUENCE_STATE_FINAL;
   }
   // This requests has already translated the SGL, have SCIC skip SGL translataion
   return SATI_SUCCESS_SGL_TRANSLATED;
}