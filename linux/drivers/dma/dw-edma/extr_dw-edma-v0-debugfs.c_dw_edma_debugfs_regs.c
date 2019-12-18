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
struct dentry {int dummy; } ;
struct debugfs_entries {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct debugfs_entries const*) ; 
 struct debugfs_entries const REGISTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGISTERS_STR ; 
 int /*<<< orphan*/  base_dir ; 
 int /*<<< orphan*/  ctrl ; 
 int /*<<< orphan*/  ctrl_data_arb_prior ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_edma_debugfs_create_x32 (struct debugfs_entries const*,int,struct dentry*) ; 
 int /*<<< orphan*/  dw_edma_debugfs_regs_rd (struct dentry*) ; 
 int /*<<< orphan*/  dw_edma_debugfs_regs_wr (struct dentry*) ; 

__attribute__((used)) static void dw_edma_debugfs_regs(void)
{
	const struct debugfs_entries debugfs_regs[] = {
		REGISTER(ctrl_data_arb_prior),
		REGISTER(ctrl),
	};
	struct dentry *regs_dir;
	int nr_entries;

	regs_dir = debugfs_create_dir(REGISTERS_STR, base_dir);
	if (!regs_dir)
		return;

	nr_entries = ARRAY_SIZE(debugfs_regs);
	dw_edma_debugfs_create_x32(debugfs_regs, nr_entries, regs_dir);

	dw_edma_debugfs_regs_wr(regs_dir);
	dw_edma_debugfs_regs_rd(regs_dir);
}