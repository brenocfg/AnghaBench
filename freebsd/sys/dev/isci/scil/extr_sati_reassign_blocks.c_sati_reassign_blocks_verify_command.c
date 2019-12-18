#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_6__ {TYPE_1__* device; } ;
struct TYPE_5__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_READ_VERIFY_SECTORS ; 
 int /*<<< orphan*/  ATA_READ_VERIFY_SECTORS_EXT ; 
 int SATI_DEVICE_CAP_48BIT_ENABLE ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  sati_ata_non_data_command (void*,TYPE_2__*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_set_ata_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
SATI_STATUS sati_reassign_blocks_verify_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   sati_ata_non_data_command(ata_io, sequence);

   // Ensure the device supports the 48 bit feature set.
   if (sequence->device->capabilities & SATI_DEVICE_CAP_48BIT_ENABLE)
      sati_set_ata_command(register_fis, ATA_READ_VERIFY_SECTORS_EXT);
   else
      sati_set_ata_command(register_fis, ATA_READ_VERIFY_SECTORS);

   return SATI_SUCCESS;
}