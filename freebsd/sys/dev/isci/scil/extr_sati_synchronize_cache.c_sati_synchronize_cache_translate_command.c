#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_5__ {TYPE_1__* device; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int capabilities; } ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_FLUSH_CACHE ; 
 int /*<<< orphan*/  ATA_FLUSH_CACHE_EXT ; 
 int /*<<< orphan*/  SATI_DATA_DIRECTION_NONE ; 
 int SATI_DEVICE_CAP_48BIT_ENABLE ; 
 int /*<<< orphan*/  SATI_SEQUENCE_SYNCHRONIZE_CACHE ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SAT_PROTOCOL_NON_DATA ; 
 int SCSI_SYNCHRONIZE_CACHE_IMMED_ENABLED ; 
 int /*<<< orphan*/ * sati_cb_get_cdb_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int sati_get_cdb_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_set_ata_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

SATI_STATUS sati_synchronize_cache_translate_command(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io
)
{
   U8 * cdb          = sati_cb_get_cdb_address(scsi_io);
   U8 * register_fis = sati_cb_get_h2d_register_fis_address(ata_io);

   sequence->type           = SATI_SEQUENCE_SYNCHRONIZE_CACHE;
   sequence->protocol       = SAT_PROTOCOL_NON_DATA;
   sequence->data_direction = SATI_DATA_DIRECTION_NONE;

   if (sati_get_cdb_byte(cdb, 1) & SCSI_SYNCHRONIZE_CACHE_IMMED_ENABLED)
   {
      //currently we ignore immed bit.
      ;
   }

   // Ensure the device supports the 48 bit feature set.
   if (sequence->device->capabilities & SATI_DEVICE_CAP_48BIT_ENABLE)
      sati_set_ata_command(register_fis, ATA_FLUSH_CACHE_EXT);
   else
      sati_set_ata_command(register_fis, ATA_FLUSH_CACHE);

   return SATI_SUCCESS;
}