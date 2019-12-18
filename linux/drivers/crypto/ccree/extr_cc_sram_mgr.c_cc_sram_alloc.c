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
typedef  int u32 ;
struct device {int dummy; } ;
struct cc_sram_ctx {int sram_free_offset; } ;
struct cc_drvdata {struct cc_sram_ctx* sram_mgr_handle; } ;
typedef  int cc_sram_addr_t ;

/* Variables and functions */
 int CC_CC_SRAM_SIZE ; 
 int NULL_SRAM_ADDR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 

cc_sram_addr_t cc_sram_alloc(struct cc_drvdata *drvdata, u32 size)
{
	struct cc_sram_ctx *smgr_ctx = drvdata->sram_mgr_handle;
	struct device *dev = drvdata_to_dev(drvdata);
	cc_sram_addr_t p;

	if ((size & 0x3)) {
		dev_err(dev, "Requested buffer size (%u) is not multiple of 4",
			size);
		return NULL_SRAM_ADDR;
	}
	if (size > (CC_CC_SRAM_SIZE - smgr_ctx->sram_free_offset)) {
		dev_err(dev, "Not enough space to allocate %u B (at offset %llu)\n",
			size, smgr_ctx->sram_free_offset);
		return NULL_SRAM_ADDR;
	}

	p = smgr_ctx->sram_free_offset;
	smgr_ctx->sram_free_offset += size;
	dev_dbg(dev, "Allocated %u B @ %u\n", size, (unsigned int)p);
	return p;
}