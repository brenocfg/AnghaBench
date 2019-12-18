#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,scalar_t__,int /*<<< orphan*/ ) ; 

void sati_copy_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * destination_scsi_io,
   U32                          destination_offset,
   U8                         * source_buffer,
   U32                          length
)
{
   while (length > 0)
   {
      sati_set_data_byte(
         sequence, destination_scsi_io, destination_offset, *source_buffer
      );

      destination_offset++;
      source_buffer++;
      length--;
   }
}