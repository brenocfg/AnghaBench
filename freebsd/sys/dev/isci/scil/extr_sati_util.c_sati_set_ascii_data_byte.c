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
typedef  int U8 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
void sati_set_ascii_data_byte(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * destination_scsi_io,
   U32                          destination_offset,
   U8                           source_value,
   BOOL                         use_printable_chars
)
{
   // if the user requests that the copied data be ascii printable, then
   // default to " " (i.e. 0x20) for all non-ascii printable characters.
   if((use_printable_chars == TRUE)
     && ((source_value < 0x20) || (source_value > 0x7E)))
   {
      source_value = 0x20;
   }

   sati_set_data_byte(
      sequence, destination_scsi_io, destination_offset, source_value
   );
}