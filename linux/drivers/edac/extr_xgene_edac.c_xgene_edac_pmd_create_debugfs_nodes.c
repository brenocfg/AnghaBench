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
struct xgene_edac_pmd_ctx {int pmd; TYPE_1__* edac; } ;
struct edac_device_ctl_info {struct xgene_edac_pmd_ctx* pvt_info; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  dfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_EDAC_DEBUG ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IWUSR ; 
 struct dentry* edac_debugfs_create_dir_at (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_debugfs_create_file (char*,int /*<<< orphan*/ ,struct dentry*,struct edac_device_ctl_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * xgene_edac_pmd_debug_inject_fops ; 

__attribute__((used)) static void
xgene_edac_pmd_create_debugfs_nodes(struct edac_device_ctl_info *edac_dev)
{
	struct xgene_edac_pmd_ctx *ctx = edac_dev->pvt_info;
	struct dentry *dbgfs_dir;
	char name[10];

	if (!IS_ENABLED(CONFIG_EDAC_DEBUG) || !ctx->edac->dfs)
		return;

	snprintf(name, sizeof(name), "PMD%d", ctx->pmd);
	dbgfs_dir = edac_debugfs_create_dir_at(name, ctx->edac->dfs);
	if (!dbgfs_dir)
		return;

	edac_debugfs_create_file("l1_inject_ctrl", S_IWUSR, dbgfs_dir, edac_dev,
				 &xgene_edac_pmd_debug_inject_fops[0]);
	edac_debugfs_create_file("l2_inject_ctrl", S_IWUSR, dbgfs_dir, edac_dev,
				 &xgene_edac_pmd_debug_inject_fops[1]);
}