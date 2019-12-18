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
typedef  scalar_t__ U8 ;
typedef  int U16 ;
struct TYPE_6__ {int capabilities1; int command_set_supported1; int command_set_supported0; int command_set_enabled0; int serial_ata_capabilities; int queue_depth; int general_config_bits; int command_set_supported2; int physical_logical_sector_info; int command_set_supported_extention; int nominal_media_rotation_rate; int* words_per_logical_sector; int data_set_management; scalar_t__ max_lba_range_entry_blocks; int additional_supported; int /*<<< orphan*/  max_num_blocks_per_microcode; int /*<<< orphan*/  min_num_blocks_per_microcode; } ;
struct TYPE_5__ {int capabilities; int logical_block_size; scalar_t__ max_lba_range_entry_blocks; int /*<<< orphan*/  max_blocks_per_microcode_command; int /*<<< orphan*/  min_blocks_per_microcode_command; int /*<<< orphan*/  ncq_depth; } ;
typedef  TYPE_1__ SATI_DEVICE_T ;
typedef  TYPE_2__ ATA_IDENTIFY_DEVICE_DATA_T ;

/* Variables and functions */
 int ATA_IDENTIFY_CAPABILITIES1_NORMAL_DMA_ENABLE ; 
 int ATA_IDENTIFY_CAPABILITIES1_STANDBY_ENABLE ; 
 int ATA_IDENTIFY_COMMAND_ADDL_SUPPORTED_DETERMINISTIC_READ ; 
 int ATA_IDENTIFY_COMMAND_ADDL_SUPPORTED_READ_ZERO ; 
 int ATA_IDENTIFY_COMMAND_SET_DSM_TRIM_SUPPORTED ; 
 int ATA_IDENTIFY_COMMAND_SET_SMART_SELF_TEST_SUPPORTED ; 
 int ATA_IDENTIFY_COMMAND_SET_SUPPORTED0_SMART_ENABLE ; 
 int ATA_IDENTIFY_COMMAND_SET_SUPPORTED1_48BIT_ENABLE ; 
 int ATA_IDENTIFY_LOGICAL_SECTOR_PER_PHYSICAL_SECTOR_ENABLE ; 
 int ATA_IDENTIFY_NCQ_QUEUE_DEPTH_ENABLE ; 
 int ATA_IDENTIFY_REMOVABLE_MEDIA_ENABLE ; 
 int ATA_IDENTIFY_SATA_CAPABILITIES_NCQ_ENABLE ; 
 int ATA_IDENTIFY_WRITE_UNCORRECTABLE_SUPPORT ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int SATI_DEVICE_CAP_48BIT_ENABLE ; 
 int SATI_DEVICE_CAP_DETERMINISTIC_READ_AFTER_TRIM ; 
 int SATI_DEVICE_CAP_DMA_FUA_ENABLE ; 
 int SATI_DEVICE_CAP_DSM_TRIM_SUPPORT ; 
 int SATI_DEVICE_CAP_IGNORE_FUA ; 
 int SATI_DEVICE_CAP_MULTIPLE_SECTORS_PER_PHYSCIAL_SECTOR ; 
 int SATI_DEVICE_CAP_NCQ_REQUESTED_ENABLE ; 
 int SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE ; 
 int SATI_DEVICE_CAP_READ_ZERO_AFTER_TRIM ; 
 int SATI_DEVICE_CAP_REMOVABLE_MEDIA ; 
 int SATI_DEVICE_CAP_SMART_ENABLE ; 
 int SATI_DEVICE_CAP_SMART_SELF_TEST_SUPPORT ; 
 int SATI_DEVICE_CAP_SMART_SUPPORT ; 
 int SATI_DEVICE_CAP_SSD ; 
 int SATI_DEVICE_CAP_STANDBY_ENABLE ; 
 int SATI_DEVICE_CAP_UDMA_ENABLE ; 
 int SATI_DEVICE_CAP_WRITE_UNCORRECTABLE_ENABLE ; 

void sati_device_update_capabilities(
   SATI_DEVICE_T              * device,
   ATA_IDENTIFY_DEVICE_DATA_T * identify
)
{
   U16 capabilities = 0;

   if (identify->capabilities1 & ATA_IDENTIFY_CAPABILITIES1_NORMAL_DMA_ENABLE)
      capabilities |= SATI_DEVICE_CAP_UDMA_ENABLE;

   if (identify->command_set_supported1
       & ATA_IDENTIFY_COMMAND_SET_SUPPORTED1_48BIT_ENABLE)
   {
      capabilities |= SATI_DEVICE_CAP_48BIT_ENABLE;
   }

   if (identify->command_set_supported0
       & ATA_IDENTIFY_COMMAND_SET_SUPPORTED0_SMART_ENABLE)
   {
      capabilities |= SATI_DEVICE_CAP_SMART_SUPPORT;
   }

   if (identify->command_set_enabled0
       & ATA_IDENTIFY_COMMAND_SET_SUPPORTED0_SMART_ENABLE)
   {
       capabilities |= SATI_DEVICE_CAP_SMART_ENABLE;
   }

   // Save the NCQ related capabilities information.
   if (identify->serial_ata_capabilities
       & ATA_IDENTIFY_SATA_CAPABILITIES_NCQ_ENABLE)
   {
      if (device->capabilities & SATI_DEVICE_CAP_NCQ_REQUESTED_ENABLE)
      {
         capabilities      |= SATI_DEVICE_CAP_NCQ_REQUESTED_ENABLE;
         capabilities      |= SATI_DEVICE_CAP_NCQ_SUPPORTED_ENABLE;
         capabilities      |= SATI_DEVICE_CAP_DMA_FUA_ENABLE;
         device->ncq_depth  = MIN(
                                 device->ncq_depth,
                                 (U8) (identify->queue_depth
                                 & ATA_IDENTIFY_NCQ_QUEUE_DEPTH_ENABLE) + 1
                              );
      }
   }

   // if the user requested that FUA is ignored; transfer it so we don't lose on update.
   if (device->capabilities & SATI_DEVICE_CAP_IGNORE_FUA)
	   capabilities |= SATI_DEVICE_CAP_IGNORE_FUA;

   if (identify->general_config_bits & ATA_IDENTIFY_REMOVABLE_MEDIA_ENABLE)
      capabilities |= SATI_DEVICE_CAP_REMOVABLE_MEDIA;

   if(identify->command_set_supported2 & ATA_IDENTIFY_WRITE_UNCORRECTABLE_SUPPORT )
   {
      capabilities |= SATI_DEVICE_CAP_WRITE_UNCORRECTABLE_ENABLE;
   }

   if(identify->physical_logical_sector_info &
      ATA_IDENTIFY_LOGICAL_SECTOR_PER_PHYSICAL_SECTOR_ENABLE)
   {
      capabilities |= SATI_DEVICE_CAP_MULTIPLE_SECTORS_PER_PHYSCIAL_SECTOR;
   }

   if(identify->command_set_supported_extention &
      ATA_IDENTIFY_COMMAND_SET_SMART_SELF_TEST_SUPPORTED)
   {
      capabilities |= SATI_DEVICE_CAP_SMART_SELF_TEST_SUPPORT;
   }

   if (identify->nominal_media_rotation_rate == 1)
   {
       capabilities |= SATI_DEVICE_CAP_SSD;
   }

   // Save off the logical block size reported by the drive
   // See if Word 106 is valid and reports a logical sector size
   if ((identify->physical_logical_sector_info & 0x5000) == 0x5000)
   {
       device->logical_block_size = (identify->words_per_logical_sector[3] << 24) |
                                    (identify->words_per_logical_sector[2] << 16) |
                                    (identify->words_per_logical_sector[1] << 8) |
                                    (identify->words_per_logical_sector[0]);
   }
   else
   {
       device->logical_block_size = 512;
   }

   // Determine DSM TRIM capabilities
   // Defend against SSDs which report TRIM support, but set
   //  max_lba_range_entry_blocks to zero, by disabling TRIM for
   //  those SSDs.
   if (
     (identify->data_set_management & ATA_IDENTIFY_COMMAND_SET_DSM_TRIM_SUPPORTED)
     && (identify->max_lba_range_entry_blocks > 0)
      )
   {
      capabilities |= SATI_DEVICE_CAP_DSM_TRIM_SUPPORT;
      device->max_lba_range_entry_blocks = identify->max_lba_range_entry_blocks;
   }

   if (identify->additional_supported
       & ATA_IDENTIFY_COMMAND_ADDL_SUPPORTED_DETERMINISTIC_READ)
   {
      capabilities |= SATI_DEVICE_CAP_DETERMINISTIC_READ_AFTER_TRIM;
   }

   if (identify->additional_supported
       & ATA_IDENTIFY_COMMAND_ADDL_SUPPORTED_READ_ZERO)
   {
      capabilities |= SATI_DEVICE_CAP_READ_ZERO_AFTER_TRIM;
   }

   if (identify->capabilities1
       & ATA_IDENTIFY_CAPABILITIES1_STANDBY_ENABLE)
   {
       capabilities |= SATI_DEVICE_CAP_STANDBY_ENABLE;
   }

   device->min_blocks_per_microcode_command = identify->min_num_blocks_per_microcode;
   device->max_blocks_per_microcode_command = identify->max_num_blocks_per_microcode;

   device->capabilities = capabilities;
}