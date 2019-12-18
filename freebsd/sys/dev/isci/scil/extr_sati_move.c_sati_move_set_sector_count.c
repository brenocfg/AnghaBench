#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ U8 ;
typedef  int U32 ;
struct TYPE_5__ {int move_sector_count; } ;
struct TYPE_7__ {TYPE_1__ command_specific_data; TYPE_2__* device; } ;
struct TYPE_6__ {int capabilities; } ;
typedef  TYPE_3__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SATI_COMPLETE ; 
 int SATI_DEVICE_CAP_48BIT_ENABLE ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 scalar_t__* sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_set_ata_features (scalar_t__*,int) ; 
 int /*<<< orphan*/  sati_set_ata_features_exp (scalar_t__*,int) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count (scalar_t__*,int) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count_exp (scalar_t__*,int) ; 

SATI_STATUS sati_move_set_sector_count(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U32                          sector_count,
   U8                           is_fpdma_command
)
{
   U32  max_sector_count;
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   if (sequence->device->capabilities & SATI_DEVICE_CAP_48BIT_ENABLE)
      max_sector_count = 65536;
   else
      max_sector_count = 256;

   // Check the CDB transfer length count and set the register FIS sector
   // count fields
   if (0 == sector_count)
   {
      // A SCSI sector count of 0 for 10-byte CDBs and larger indicate no data
      // transfer, so simply complete the command immediately.
      return SATI_COMPLETE;
   }
   else if (sector_count >= max_sector_count)
   {
      // We have to perform multiple SATA commands to satisfy the sector
      // count specified in the SCSI command.
      sequence->command_specific_data.move_sector_count =
         sector_count - max_sector_count;

      // In ATA a sector count of 0 indicates use the maximum allowed for
      // the command (i.e. 0 == 2^16 or 2^8).
      sector_count = 0;
   }

   if (is_fpdma_command)
   {
      sati_set_ata_features(register_fis, sector_count & 0xFF);
      sati_set_ata_features_exp(register_fis, (sector_count >> 8) & 0xFF);
   }
   else
   {
      sati_set_ata_sector_count(register_fis, sector_count & 0xFF);
      sati_set_ata_sector_count_exp(register_fis, (sector_count >> 8) & 0xFF);
   }

   return SATI_SUCCESS;
}