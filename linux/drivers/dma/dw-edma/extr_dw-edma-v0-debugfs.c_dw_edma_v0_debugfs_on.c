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
struct dw_edma_chip {TYPE_2__* dw; } ;
struct TYPE_3__ {int /*<<< orphan*/  vaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  rd_ch_cnt; int /*<<< orphan*/  wr_ch_cnt; int /*<<< orphan*/  mode; int /*<<< orphan*/  version; int /*<<< orphan*/  name; TYPE_1__ rg_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  base_dir ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_u16 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* dw ; 
 int /*<<< orphan*/  dw_edma_debugfs_regs () ; 
 int /*<<< orphan*/  regs ; 

void dw_edma_v0_debugfs_on(struct dw_edma_chip *chip)
{
	dw = chip->dw;
	if (!dw)
		return;

	regs = dw->rg_region.vaddr;
	if (!regs)
		return;

	base_dir = debugfs_create_dir(dw->name, 0);
	if (!base_dir)
		return;

	debugfs_create_u32("version", 0444, base_dir, &dw->version);
	debugfs_create_u32("mode", 0444, base_dir, &dw->mode);
	debugfs_create_u16("wr_ch_cnt", 0444, base_dir, &dw->wr_ch_cnt);
	debugfs_create_u16("rd_ch_cnt", 0444, base_dir, &dw->rd_ch_cnt);

	dw_edma_debugfs_regs();
}