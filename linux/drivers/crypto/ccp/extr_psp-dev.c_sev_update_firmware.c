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
typedef  int u64 ;
struct sev_data_download_firmware {int len; int /*<<< orphan*/  address; } ;
struct page {int dummy; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEV_CMD_DOWNLOAD_FIRMWARE ; 
 int /*<<< orphan*/  __free_pages (struct page*,int) ; 
 int /*<<< orphan*/  __psp_pa (struct sev_data_download_firmware*) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  memcpy (struct sev_data_download_firmware*,int /*<<< orphan*/ ,int) ; 
 struct sev_data_download_firmware* page_address (struct page*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int sev_do_cmd (int /*<<< orphan*/ ,struct sev_data_download_firmware*,int*) ; 
 int /*<<< orphan*/  sev_get_firmware (struct device*,struct firmware const**) ; 

__attribute__((used)) static int sev_update_firmware(struct device *dev)
{
	struct sev_data_download_firmware *data;
	const struct firmware *firmware;
	int ret, error, order;
	struct page *p;
	u64 data_size;

	if (sev_get_firmware(dev, &firmware) == -ENOENT) {
		dev_dbg(dev, "No SEV firmware file present\n");
		return -1;
	}

	/*
	 * SEV FW expects the physical address given to it to be 32
	 * byte aligned. Memory allocated has structure placed at the
	 * beginning followed by the firmware being passed to the SEV
	 * FW. Allocate enough memory for data structure + alignment
	 * padding + SEV FW.
	 */
	data_size = ALIGN(sizeof(struct sev_data_download_firmware), 32);

	order = get_order(firmware->size + data_size);
	p = alloc_pages(GFP_KERNEL, order);
	if (!p) {
		ret = -1;
		goto fw_err;
	}

	/*
	 * Copy firmware data to a kernel allocated contiguous
	 * memory region.
	 */
	data = page_address(p);
	memcpy(page_address(p) + data_size, firmware->data, firmware->size);

	data->address = __psp_pa(page_address(p) + data_size);
	data->len = firmware->size;

	ret = sev_do_cmd(SEV_CMD_DOWNLOAD_FIRMWARE, data, &error);
	if (ret)
		dev_dbg(dev, "Failed to update SEV firmware: %#x\n", error);
	else
		dev_info(dev, "SEV firmware update successful\n");

	__free_pages(p, order);

fw_err:
	release_firmware(firmware);

	return ret;
}