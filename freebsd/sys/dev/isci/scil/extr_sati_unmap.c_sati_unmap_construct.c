#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U8 ;
typedef  int U32 ;
struct TYPE_3__ {int /*<<< orphan*/  is_translate_response_required; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data_direction; } ;
typedef  TYPE_1__ SATI_TRANSLATOR_SEQUENCE_T ;
typedef  int /*<<< orphan*/  SATI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ATA_DATA_SET_MANAGEMENT ; 
 int /*<<< orphan*/  ATA_DEV_HEAD_REG_LBA_MODE_ENABLE ; 
 int /*<<< orphan*/  SATI_DATA_DIRECTION_OUT ; 
 int /*<<< orphan*/  SATI_SUCCESS ; 
 int /*<<< orphan*/  SAT_PROTOCOL_UDMA_DATA_OUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * sati_cb_get_d2h_register_fis_address (void*) ; 
 int /*<<< orphan*/ * sati_cb_get_h2d_register_fis_address (void*) ; 
 int /*<<< orphan*/  sati_set_ata_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_device_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_features (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sati_set_ata_sector_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sati_set_ata_status (int /*<<< orphan*/ *,int) ; 

SATI_STATUS sati_unmap_construct(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   void                       * scsi_io,
   void                       * ata_io,
   U32                          sector_count
)
{
   U8 * h2d_register_fis = sati_cb_get_h2d_register_fis_address(ata_io);
   U8 * d2h_register_fis = sati_cb_get_d2h_register_fis_address(ata_io);

   sati_set_ata_command(h2d_register_fis, ATA_DATA_SET_MANAGEMENT);
   sati_set_ata_features(h2d_register_fis, 0x01);
   sati_set_ata_sector_count(h2d_register_fis, (U8)sector_count);
   sati_set_ata_device_head(h2d_register_fis, ATA_DEV_HEAD_REG_LBA_MODE_ENABLE);

   // Set the completion status since the core will not do that for
   // the udma fast path.
   sati_set_ata_status(d2h_register_fis, 0x00);

   // Set up the direction and protocol for SCIC
   sequence->data_direction                 = SATI_DATA_DIRECTION_OUT;
   sequence->protocol                       = SAT_PROTOCOL_UDMA_DATA_OUT;
   // The UNMAP translation will always require a callback
   // on every response so it can free memory if an error
   // occurs.
   sequence->is_translate_response_required = TRUE;

   ASSERT(sector_count < 0x100);

   return SATI_SUCCESS;
}