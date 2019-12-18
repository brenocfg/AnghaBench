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
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_4__ {scalar_t__ data_direction; int /*<<< orphan*/  protocol; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */
 scalar_t__ SATI_DATA_DIRECTION_IN ; 
 int /*<<< orphan*/  SAT_PROTOCOL_UDMA_DATA_IN ; 
 int /*<<< orphan*/  SAT_PROTOCOL_UDMA_DATA_OUT ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_move_set_ata_command (TYPE_1__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void sati_move_small_udma_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U8                           write_opcode,
   U8                           read_opcode
)
{
   U8 * cdb          = sati_cb_get_cdb_address(scsi_io);
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   sati_move_set_ata_command(sequence, ata_io, write_opcode, read_opcode);
   sati_set_ata_sector_count(register_fis, sati_get_cdb_byte(cdb, 4));

   if (sequence->data_direction == SATI_DATA_DIRECTION_IN)
      sequence->protocol = SAT_PROTOCOL_UDMA_DATA_IN;
   else
      sequence->protocol = SAT_PROTOCOL_UDMA_DATA_OUT;
}