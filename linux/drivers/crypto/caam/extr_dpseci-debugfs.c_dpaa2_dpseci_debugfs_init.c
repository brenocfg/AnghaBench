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
struct dpaa2_caam_priv {int /*<<< orphan*/  dfs_root; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct dpaa2_caam_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpseci_dbg_fq_ops ; 

void dpaa2_dpseci_debugfs_init(struct dpaa2_caam_priv *priv)
{
	priv->dfs_root = debugfs_create_dir(dev_name(priv->dev), NULL);

	debugfs_create_file("fq_stats", 0444, priv->dfs_root, priv,
			    &dpseci_dbg_fq_ops);
}