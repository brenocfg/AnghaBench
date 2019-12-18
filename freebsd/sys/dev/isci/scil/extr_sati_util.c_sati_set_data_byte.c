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
typedef  int /*<<< orphan*/  U8 ;
typedef  scalar_t__ U32 ;
struct TYPE_3__ {scalar_t__ allocation_length; int /*<<< orphan*/  number_data_bytes_set; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_cb_set_data_byte (void*,scalar_t__,int /*<<< orphan*/ ) ; 

void sati_set_data_byte(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   U32                          byte_offset,
   U8                           value
)
{
   if (byte_offset < sequence->allocation_length)
   {
      sequence->number_data_bytes_set++;
      sati_cb_set_data_byte(scsi_io, byte_offset, value);
   }
}