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
struct TYPE_3__ {scalar_t__ state; scalar_t__ number_data_bytes_set; scalar_t__ allocation_length; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int /*<<< orphan*/  SATI_COMPLETE_IO_DONE_EARLY ; 
 int /*<<< orphan*/  SATI_SEQUENCE_INCOMPLETE ; 
 scalar_t__ SATI_SEQUENCE_STATE_INCOMPLETE ; 

__attribute__((used)) static
SATI_STATUS sati_check_data_io(
   SATI_TRANSLATOR_SEQUENCE_T * sequence
)
{
   if(sequence->state == SATI_SEQUENCE_STATE_INCOMPLETE)
   {
      return SATI_SEQUENCE_INCOMPLETE;
   }
   else if(sequence->number_data_bytes_set < sequence->allocation_length)
   {
      return SATI_COMPLETE_IO_DONE_EARLY;
   }
   else
   {
      return SATI_COMPLETE;
   }
}