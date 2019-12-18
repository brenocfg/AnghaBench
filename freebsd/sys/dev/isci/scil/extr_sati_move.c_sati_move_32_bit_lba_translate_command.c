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
typedef  int /*<<< orphan*/  SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  sati_move_translate_32_bit_lba (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  sati_move_translate_command (int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_move_32_bit_lba_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U8                           device_head
)
{
   sati_move_translate_32_bit_lba(sequence, scsi_io, ata_io);
   sati_move_translate_command(sequence, scsi_io, ata_io, device_head);

   return SATI_SUCCESS;
}