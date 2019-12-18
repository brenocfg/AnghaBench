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
struct device {int dummy; } ;
struct cc_sram_ctx {int sram_free_offset; } ;
struct cc_drvdata {scalar_t__ hw_rev; struct cc_sram_ctx* sram_mgr_handle; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ CC_HW_REV_712 ; 
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOST_SEP_SRAM_THRESHOLD ; 
 scalar_t__ cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int*) ; 
 struct cc_sram_ctx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 

int cc_sram_mgr_init(struct cc_drvdata *drvdata)
{
	struct cc_sram_ctx *ctx;
	dma_addr_t start = 0;
	struct device *dev = drvdata_to_dev(drvdata);

	if (drvdata->hw_rev < CC_HW_REV_712) {
		/* Pool starts after ROM bytes */
		start = (dma_addr_t)cc_ioread(drvdata,
					      CC_REG(HOST_SEP_SRAM_THRESHOLD));

		if ((start & 0x3) != 0) {
			dev_err(dev, "Invalid SRAM offset %pad\n", &start);
			return -EINVAL;
		}
	}

	/* Allocate "this" context */
	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);

	if (!ctx)
		return -ENOMEM;

	ctx->sram_free_offset = start;
	drvdata->sram_mgr_handle = ctx;

	return 0;
}