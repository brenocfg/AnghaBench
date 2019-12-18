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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  sati_set_ascii_data_byte (int /*<<< orphan*/ *,void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sati_ata_identify_device_copy_data(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * destination_scsi_io,
   U32                          destination_offset,
   U8                         * source_buffer,
   U32                          source_offset,
   U32                          length,
   BOOL                         use_printable_chars
)
{
   source_buffer += source_offset;
   while (length > 0)
   {
      sati_set_ascii_data_byte(
         sequence,
         destination_scsi_io,
         destination_offset,
         *(source_buffer+1),
         use_printable_chars
      );

      sati_set_ascii_data_byte(
         sequence,
         destination_scsi_io,
         destination_offset+1,
         *source_buffer,
         use_printable_chars
      );

      destination_offset += 2;
      source_buffer      += 2;
      length             -= 2;
   }
}