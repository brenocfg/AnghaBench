#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * virtual_unmap_buffer; } ;
struct TYPE_5__ {TYPE_2__ unmap_process_state; } ;
struct TYPE_7__ {TYPE_1__ command_specific_data; } ;
typedef  TYPE_2__ SATI_UNMAP_PROCESSING_STATE_T ;
typedef  TYPE_3__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_cb_free_dma_buffer (void*,int /*<<< orphan*/ *) ; 

void sati_unmap_terminate(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_UNMAP_PROCESSING_STATE_T * unmap_process_state;
   unmap_process_state = &sequence->command_specific_data.unmap_process_state;

   if (unmap_process_state->virtual_unmap_buffer != NULL)
   {
      sati_cb_free_dma_buffer(scsi_io, unmap_process_state->virtual_unmap_buffer);
      unmap_process_state->virtual_unmap_buffer = NULL;
   }
}