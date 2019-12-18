#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {unsigned int length; scalar_t__ signature; } ;
typedef  TYPE_1__ boot_header_t ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int BOOT_FLASH_BOOT_ADDR ; 
 unsigned int BOOT_MAX_SIZE ; 
 unsigned int BOOT_MIN_SIZE ; 
 scalar_t__ BOOT_SIGNATURE ; 
 unsigned int BOOT_SIZE_INC ; 
 int /*<<< orphan*/  CH_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int EFBIG ; 
 int EINVAL ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int t3_flash_erase_sectors (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int t3_write_flash (int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int t3_load_boot(adapter_t *adapter, u8 *boot_data, unsigned int size)
{
	boot_header_t *header = (boot_header_t *)boot_data;
	int ret;
	unsigned int addr;
	unsigned int boot_sector = BOOT_FLASH_BOOT_ADDR >> 16;
	unsigned int boot_end = (BOOT_FLASH_BOOT_ADDR + size - 1) >> 16;

	/*
	 * Perform some primitive sanity testing to avoid accidentally
	 * writing garbage over the boot sectors.  We ought to check for
	 * more but it's not worth it for now ...
	 */
	if (size < BOOT_MIN_SIZE || size > BOOT_MAX_SIZE) {
		CH_ERR(adapter, "boot image too small/large\n");
		return -EFBIG;
	}
	if (le16_to_cpu(*(u16*)header->signature) != BOOT_SIGNATURE) {
		CH_ERR(adapter, "boot image missing signature\n");
		return -EINVAL;
	}
	if (header->length * BOOT_SIZE_INC != size) {
		CH_ERR(adapter, "boot image header length != image length\n");
		return -EINVAL;
	}

	ret = t3_flash_erase_sectors(adapter, boot_sector, boot_end);
	if (ret)
		goto out;

	for (addr = BOOT_FLASH_BOOT_ADDR; size; ) {
		unsigned int chunk_size = min(size, 256U);

		ret = t3_write_flash(adapter, addr, chunk_size, boot_data, 0);
		if (ret)
			goto out;

		addr += chunk_size;
		boot_data += chunk_size;
		size -= chunk_size;
	}

out:
	if (ret)
		CH_ERR(adapter, "boot image download failed, error %d\n", ret);
	return ret;
}