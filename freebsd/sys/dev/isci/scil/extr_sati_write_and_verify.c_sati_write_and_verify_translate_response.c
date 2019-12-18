#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_FAILURE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_INCOMPLETE ; 
 scalar_t__ SATI_SEQUENCE_STATE_AWAIT_RESPONSE ; 
 scalar_t__ SATI_SEQUENCE_STATE_FINAL ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 

SATI_STATUS sati_write_and_verify_translate_response(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   if(sequence->state == SATI_SEQUENCE_STATE_INCOMPLETE)
   {
      return SATI_SEQUENCE_INCOMPLETE;
   }
   else if(sequence->state == SATI_SEQUENCE_STATE_AWAIT_RESPONSE)
   {
      sequence->state = SATI_SEQUENCE_STATE_FINAL;
      return SATI_COMPLETE;
   }

   return SATI_FAILURE;
}