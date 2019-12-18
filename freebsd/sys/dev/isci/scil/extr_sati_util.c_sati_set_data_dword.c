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
typedef  int U32 ;
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  sati_set_data_byte (int /*<<< orphan*/ *,void*,int,int) ; 

void sati_set_data_dword(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   U32                          byte_offset,
   U32                          value
)
{
   /// @todo Check to ensure that the bytes appear correctly (SAS Address).

   sati_set_data_byte(sequence, scsi_io, byte_offset, (U8)value & 0xFF);
       byte_offset++;
   sati_set_data_byte(sequence, scsi_io, byte_offset, (U8)(value >> 8) & 0xFF);
       byte_offset++;
   sati_set_data_byte(sequence, scsi_io, byte_offset, (U8)(value >> 16) & 0xFF);
       byte_offset++;
   sati_set_data_byte(sequence, scsi_io, byte_offset, (U8)(value >> 24) & 0xFF);
}