#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct TYPE_3__ {int code_type; int indicator; scalar_t__ device_id; } ;
typedef  TYPE_1__ pcir_data_t ;
struct TYPE_4__ {int cksum; int size512; scalar_t__ pcir_offset; } ;
typedef  TYPE_2__ legacy_pci_exp_rom_header_t ;

/* Variables and functions */
 size_t le16_to_cpu (int) ; 

__attribute__((used)) static void modify_device_id(int device_id, u8 *boot_data)
{
	legacy_pci_exp_rom_header_t *header;
	pcir_data_t *pcir_header;
	u32 cur_header = 0;

	/*
	 * Loop through all chained images and change the device ID's
	 */
	while (1) {
		header = (legacy_pci_exp_rom_header_t *) &boot_data[cur_header];
		pcir_header = (pcir_data_t *) &boot_data[cur_header +
			      le16_to_cpu(*(u16*)header->pcir_offset)];

		/*
		 * Only modify the Device ID if code type is Legacy or HP.
		 * 0x00: Okay to modify
		 * 0x01: FCODE. Do not be modify
		 * 0x03: Okay to modify
		 * 0x04-0xFF: Do not modify
		 */
		if (pcir_header->code_type == 0x00) {
			u8 csum = 0;
			int i;

			/*
			 * Modify Device ID to match current adatper
			 */
			*(u16*) pcir_header->device_id = device_id;

			/*
			 * Set checksum temporarily to 0.
			 * We will recalculate it later.
			 */
			header->cksum = 0x0;

			/*
			 * Calculate and update checksum
			 */
			for (i = 0; i < (header->size512 * 512); i++)
				csum += (u8)boot_data[cur_header + i];

			/*
			 * Invert summed value to create the checksum
			 * Writing new checksum value directly to the boot data
			 */
			boot_data[cur_header + 7] = -csum;

		} else if (pcir_header->code_type == 0x03) {

			/*
			 * Modify Device ID to match current adatper
			 */
			*(u16*) pcir_header->device_id = device_id;

		}


		/*
		 * Check indicator element to identify if this is the last
		 * image in the ROM.
		 */
		if (pcir_header->indicator & 0x80)
			break;

		/*
		 * Move header pointer up to the next image in the ROM.
		 */
		cur_header += header->size512 * 512;
	}
}