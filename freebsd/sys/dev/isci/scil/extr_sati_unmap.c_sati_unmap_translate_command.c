#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  unmap_process_state; } ;
struct TYPE_7__ {scalar_t__ state; TYPE_1__ command_specific_data; } ;
typedef  int /*<<< orphan*/  SATI_UNMAP_PROCESSING_STATE_T ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  scalar_t__ SATI_STATUS ;

/* Variables and functions */
 scalar_t__ SATI_COMPLETE ; 
 scalar_t__ SATI_FAILURE_CHECK_RESPONSE_DATA ; 
 scalar_t__ SATI_SEQUENCE_STATE_INITIAL ; 
 scalar_t__ sati_unmap_initial_processing (TYPE_2__*,void*,void*) ; 
 scalar_t__ sati_unmap_process (TYPE_2__*,void*,void*) ; 

SATI_STATUS sati_unmap_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_STATUS status = SATI_FAILURE_CHECK_RESPONSE_DATA;
   SATI_UNMAP_PROCESSING_STATE_T * unmap_process_state;

   unmap_process_state = &sequence->command_specific_data.unmap_process_state;

   // Determine if this is the first step in the unmap sequence
   if ( sequence->state == SATI_SEQUENCE_STATE_INITIAL )
   {
       status = sati_unmap_initial_processing(sequence,scsi_io,ata_io);
       if (status != SATI_COMPLETE)
       {
          return status;
       }
   }
   // Translate the next portion of the UNMAP request
   return sati_unmap_process(sequence, scsi_io, ata_io);
}