#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
#define  SATI_SEQUENCE_UNMAP 128 
 int /*<<< orphan*/  sati_unmap_terminate (TYPE_1__*,void*,void*) ; 

void sati_sequence_terminate(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   // Decode the sequence type to determine how to handle the termination
   // of the translation method.
   switch (sequence->type)
   {
   case SATI_SEQUENCE_UNMAP:
      sati_unmap_terminate(sequence,scsi_io,ata_io);
   break;
   }
}