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
struct mem_ctl_info {int /*<<< orphan*/  debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EDAC_DEBUG ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  edac_debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mem_ctl_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_edac_mc_debug_inject_fops ; 

__attribute__((used)) static void xgene_edac_mc_create_debugfs_node(struct mem_ctl_info *mci)
{
	if (!IS_ENABLED(CONFIG_EDAC_DEBUG))
		return;

	if (!mci->debugfs)
		return;

	edac_debugfs_create_file("inject_ctrl", S_IWUSR, mci->debugfs, mci,
				 &xgene_edac_mc_debug_inject_fops);
}