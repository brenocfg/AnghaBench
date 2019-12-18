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
typedef  int u64 ;
struct TYPE_2__ {int base; } ;
struct nfit_blk_mmio {unsigned int size; TYPE_1__ addr; scalar_t__ num_lines; } ;
struct nfit_blk {int cmd_offset; int dimm_flags; int /*<<< orphan*/  nd_region; struct nfit_blk_mmio* mmio; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 size_t DCR ; 
 int L1_CACHE_SHIFT ; 
 int NFIT_BLK_DCR_LATCH ; 
 int /*<<< orphan*/  nvdimm_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readq (int) ; 
 int to_interleave_offset (int,struct nfit_blk_mmio*) ; 
 int /*<<< orphan*/  writeq (int,int) ; 

__attribute__((used)) static void write_blk_ctl(struct nfit_blk *nfit_blk, unsigned int bw,
		resource_size_t dpa, unsigned int len, unsigned int write)
{
	u64 cmd, offset;
	struct nfit_blk_mmio *mmio = &nfit_blk->mmio[DCR];

	enum {
		BCW_OFFSET_MASK = (1ULL << 48)-1,
		BCW_LEN_SHIFT = 48,
		BCW_LEN_MASK = (1ULL << 8) - 1,
		BCW_CMD_SHIFT = 56,
	};

	cmd = (dpa >> L1_CACHE_SHIFT) & BCW_OFFSET_MASK;
	len = len >> L1_CACHE_SHIFT;
	cmd |= ((u64) len & BCW_LEN_MASK) << BCW_LEN_SHIFT;
	cmd |= ((u64) write) << BCW_CMD_SHIFT;

	offset = nfit_blk->cmd_offset + mmio->size * bw;
	if (mmio->num_lines)
		offset = to_interleave_offset(offset, mmio);

	writeq(cmd, mmio->addr.base + offset);
	nvdimm_flush(nfit_blk->nd_region, NULL);

	if (nfit_blk->dimm_flags & NFIT_BLK_DCR_LATCH)
		readq(mmio->addr.base + offset);
}