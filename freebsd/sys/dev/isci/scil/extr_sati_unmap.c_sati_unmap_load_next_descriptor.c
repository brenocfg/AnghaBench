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
typedef  int U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_7__ {scalar_t__ current_unmap_block_descriptor_index; int current_lba_count; int current_lba; scalar_t__ next_lba; } ;
struct TYPE_6__ {TYPE_2__ unmap_process_state; } ;
struct TYPE_8__ {TYPE_1__ command_specific_data; } ;
typedef  TYPE_2__ SATI_UNMAP_PROCESSING_STATE_T ;
typedef  TYPE_3__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;
typedef  int SATI_LBA ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_SUCCESS ; 
 scalar_t__ SATI_UNMAP_SIZEOF_SCSI_UNMAP_BLOCK_DESCRIPTOR ; 
 int /*<<< orphan*/  sati_get_data_byte (TYPE_3__*,void*,scalar_t__,int*) ; 

SATI_STATUS sati_unmap_load_next_descriptor(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io
)
{
   SATI_UNMAP_PROCESSING_STATE_T * unmap_process_state;
   U32                             index;
   U8                              unmap_block_descriptor[16];

   unmap_process_state = &sequence->command_specific_data.unmap_process_state;

   // Load the next descriptor
   for(index = unmap_process_state->current_unmap_block_descriptor_index;
       index < unmap_process_state->current_unmap_block_descriptor_index +
               SATI_UNMAP_SIZEOF_SCSI_UNMAP_BLOCK_DESCRIPTOR;
       index++)
   {
      sati_get_data_byte(sequence,
         scsi_io,
         index,
         &unmap_block_descriptor[index-unmap_process_state->current_unmap_block_descriptor_index]);
   }

   // Update the internal state for the next translation pass
   unmap_process_state->current_lba_count = (unmap_block_descriptor[8] << 24) |
                                            (unmap_block_descriptor[9] << 16) |
                                            (unmap_block_descriptor[10] << 8) |
                                            (unmap_block_descriptor[11]);
   unmap_process_state->current_lba       = ((SATI_LBA)(unmap_block_descriptor[0]) << 56) |
                                            ((SATI_LBA)(unmap_block_descriptor[1]) << 48) |
                                            ((SATI_LBA)(unmap_block_descriptor[2]) << 40) |
                                            ((SATI_LBA)(unmap_block_descriptor[3]) << 32) |
                                            ((SATI_LBA)(unmap_block_descriptor[4]) << 24) |
                                            ((SATI_LBA)(unmap_block_descriptor[5]) << 16) |
                                            ((SATI_LBA)(unmap_block_descriptor[6]) << 8) |
                                            ((SATI_LBA)(unmap_block_descriptor[7]));
   unmap_process_state->next_lba          = 0;

   // Update the index for the next descriptor to translate
   unmap_process_state->current_unmap_block_descriptor_index += SATI_UNMAP_SIZEOF_SCSI_UNMAP_BLOCK_DESCRIPTOR;

   return SATI_SUCCESS;
}