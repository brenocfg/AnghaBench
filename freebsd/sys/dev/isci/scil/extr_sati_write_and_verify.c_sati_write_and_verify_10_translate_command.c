#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  type; int /*<<< orphan*/  is_translate_response_required; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_FAILURE ; 
 scalar_t__ SATI_SEQUENCE_STATE_AWAIT_RESPONSE ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 
 scalar_t__ SATI_SEQUENCE_STATE_INITIAL ; 
 int /*<<< orphan*/  SATI_SEQUENCE_WRITE_AND_VERIFY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sati_verify_10_translate_command (TYPE_1__*,void*,void*) ; 
 int /*<<< orphan*/  sati_write_10_translate_command (TYPE_1__*,void*,void*) ; 

SATI_STATUS sati_write_and_verify_10_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   SATI_STATUS status;

   if(sequence->state == SATI_SEQUENCE_STATE_INITIAL)
   {
      status = sati_write_10_translate_command(sequence, scsi_io, ata_io);
      sequence->state = SATI_SEQUENCE_STATE_INCOMPLETE;
      sequence->is_translate_response_required = TRUE;
   }
   else if(sequence->state == SATI_SEQUENCE_STATE_INCOMPLETE)
   {
      status = sati_verify_10_translate_command(sequence, scsi_io, ata_io);
      sequence->state = SATI_SEQUENCE_STATE_AWAIT_RESPONSE;
   }
   else
   {
      //SATI sequence is in the wrong state
      return SATI_FAILURE;
   }

   sequence->type = SATI_SEQUENCE_WRITE_AND_VERIFY;
   return status;
}