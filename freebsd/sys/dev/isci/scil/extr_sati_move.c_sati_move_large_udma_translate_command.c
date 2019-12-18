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
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_5__ {scalar_t__ data_direction; int /*<<< orphan*/  protocol; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SATI_DATA_DIRECTION_IN ; 
 int /*<<< orphan*/  SAT_PROTOCOL_UDMA_DATA_IN ; 
 int /*<<< orphan*/  SAT_PROTOCOL_UDMA_DATA_OUT ; 
 int /*<<< orphan*/  sati_move_set_ata_command (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_move_set_sector_count (TYPE_1__*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SATI_STATUS sati_move_large_udma_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U32                          sector_count,
   U8                           write_opcode,
   U8                           read_opcode
)
{
   sati_move_set_ata_command(sequence, ata_io, write_opcode, read_opcode);

   if (sequence->data_direction == SATI_DATA_DIRECTION_IN)
      sequence->protocol = SAT_PROTOCOL_UDMA_DATA_IN;
   else
      sequence->protocol = SAT_PROTOCOL_UDMA_DATA_OUT;

   return sati_move_set_sector_count(
             sequence, scsi_io, ata_io, sector_count, FALSE
          );
}