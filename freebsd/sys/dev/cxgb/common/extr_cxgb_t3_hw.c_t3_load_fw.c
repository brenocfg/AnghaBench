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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  csum ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ERR (int /*<<< orphan*/ *,char*,int) ; 
 int EFBIG ; 
 int EINVAL ; 
 int FW_FLASH_BOOT_ADDR ; 
 unsigned int FW_MAX_SIZE ; 
 unsigned int FW_MAX_SIZE_PRE8 ; 
 unsigned int FW_MIN_SIZE ; 
 int FW_VERS_ADDR ; 
 int FW_VERS_ADDR_PRE8 ; 
 int G_FW_VERSION_MAJOR (int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int ntohl (int const) ; 
 int t3_flash_erase_sectors (int /*<<< orphan*/ *,int,int) ; 
 int t3_write_flash (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const*,int) ; 

int t3_load_fw(adapter_t *adapter, const u8 *fw_data, unsigned int size)
{
	u32 version, csum, fw_version_addr;
	unsigned int i;
	const u32 *p = (const u32 *)fw_data;
	int ret, addr, fw_sector = FW_FLASH_BOOT_ADDR >> 16;

	if ((size & 3) || size < FW_MIN_SIZE)
		return -EINVAL;
	if (size - 8 > FW_MAX_SIZE)
		return -EFBIG;

	version = ntohl(*(const u32 *)(fw_data + size - 8));
	if (G_FW_VERSION_MAJOR(version) < 8) {

		fw_version_addr = FW_VERS_ADDR_PRE8;

		if (size - 8 > FW_MAX_SIZE_PRE8)
			return -EFBIG;
	} else
		fw_version_addr = FW_VERS_ADDR;

	for (csum = 0, i = 0; i < size / sizeof(csum); i++)
		csum += ntohl(p[i]);
	if (csum != 0xffffffff) {
		CH_ERR(adapter, "corrupted firmware image, checksum %u\n",
		       csum);
		return -EINVAL;
	}

	ret = t3_flash_erase_sectors(adapter, fw_sector, fw_sector);
	if (ret)
		goto out;

	size -= 8;  /* trim off version and checksum */
	for (addr = FW_FLASH_BOOT_ADDR; size; ) {
		unsigned int chunk_size = min(size, 256U);

		ret = t3_write_flash(adapter, addr, chunk_size, fw_data, 1);
		if (ret)
			goto out;

		addr += chunk_size;
		fw_data += chunk_size;
		size -= chunk_size;
	}

	ret = t3_write_flash(adapter, fw_version_addr, 4, fw_data, 1);
out:
	if (ret)
		CH_ERR(adapter, "firmware download failed, error %d\n", ret);
	return ret;
}