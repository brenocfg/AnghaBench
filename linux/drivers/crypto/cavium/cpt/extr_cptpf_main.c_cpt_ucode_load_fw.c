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
typedef  void u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct ucode_header {int /*<<< orphan*/  code_length; } ;
struct microcode {void* version; int code_size; int is_ae; unsigned long long core_mask; int num_cores; int phys_base; int is_mc_valid; scalar_t__ code; } ;
struct firmware {scalar_t__ data; } ;
struct device {int dummy; } ;
struct cpt_device {size_t next_mc_idx; TYPE_1__* pdev; struct microcode* mcode; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int CPT_UCODE_VERSION_SZ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int cpu_to_be64 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,void*) ; 
 scalar_t__ dma_alloc_coherent (struct device*,int,int*,int /*<<< orphan*/ ) ; 
 int do_cpt_init (struct cpt_device*,struct microcode*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,void const*,struct device*) ; 

__attribute__((used)) static int cpt_ucode_load_fw(struct cpt_device *cpt, const u8 *fw, bool is_ae)
{
	const struct firmware *fw_entry;
	struct device *dev = &cpt->pdev->dev;
	struct ucode_header *ucode;
	struct microcode *mcode;
	int j, ret = 0;

	ret = request_firmware(&fw_entry, fw, dev);
	if (ret)
		return ret;

	ucode = (struct ucode_header *)fw_entry->data;
	mcode = &cpt->mcode[cpt->next_mc_idx];
	memcpy(mcode->version, (u8 *)fw_entry->data, CPT_UCODE_VERSION_SZ);
	mcode->code_size = ntohl(ucode->code_length) * 2;
	if (!mcode->code_size) {
		ret = -EINVAL;
		goto fw_release;
	}

	mcode->is_ae = is_ae;
	mcode->core_mask = 0ULL;
	mcode->num_cores = is_ae ? 6 : 10;

	/*  Allocate DMAable space */
	mcode->code = dma_alloc_coherent(&cpt->pdev->dev, mcode->code_size,
					 &mcode->phys_base, GFP_KERNEL);
	if (!mcode->code) {
		dev_err(dev, "Unable to allocate space for microcode");
		ret = -ENOMEM;
		goto fw_release;
	}

	memcpy((void *)mcode->code, (void *)(fw_entry->data + sizeof(*ucode)),
	       mcode->code_size);

	/* Byte swap 64-bit */
	for (j = 0; j < (mcode->code_size / 8); j++)
		((u64 *)mcode->code)[j] = cpu_to_be64(((u64 *)mcode->code)[j]);
	/*  MC needs 16-bit swap */
	for (j = 0; j < (mcode->code_size / 2); j++)
		((u16 *)mcode->code)[j] = cpu_to_be16(((u16 *)mcode->code)[j]);

	dev_dbg(dev, "mcode->code_size = %u\n", mcode->code_size);
	dev_dbg(dev, "mcode->is_ae = %u\n", mcode->is_ae);
	dev_dbg(dev, "mcode->num_cores = %u\n", mcode->num_cores);
	dev_dbg(dev, "mcode->code = %llx\n", (u64)mcode->code);
	dev_dbg(dev, "mcode->phys_base = %llx\n", mcode->phys_base);

	ret = do_cpt_init(cpt, mcode);
	if (ret) {
		dev_err(dev, "do_cpt_init failed with ret: %d\n", ret);
		goto fw_release;
	}

	dev_info(dev, "Microcode Loaded %s\n", mcode->version);
	mcode->is_mc_valid = 1;
	cpt->next_mc_idx++;

fw_release:
	release_firmware(fw_entry);

	return ret;
}