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
struct mem_ctl_info {int /*<<< orphan*/  dev; TYPE_1__* bus; struct i5100_priv* pvt_info; } ;
struct i5100_priv {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  inject_eccmask2; int /*<<< orphan*/  inject_eccmask1; int /*<<< orphan*/  inject_deviceptr2; int /*<<< orphan*/  inject_deviceptr1; int /*<<< orphan*/  inject_hlinesel; int /*<<< orphan*/  inject_channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  edac_debugfs_create_dir_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_debugfs_create_x16 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_debugfs_create_x8 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i5100_debugfs ; 
 int /*<<< orphan*/  i5100_inject_enable_fops ; 

__attribute__((used)) static int i5100_setup_debugfs(struct mem_ctl_info *mci)
{
	struct i5100_priv *priv = mci->pvt_info;

	if (!i5100_debugfs)
		return -ENODEV;

	priv->debugfs = edac_debugfs_create_dir_at(mci->bus->name, i5100_debugfs);

	if (!priv->debugfs)
		return -ENOMEM;

	edac_debugfs_create_x8("inject_channel", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_channel);
	edac_debugfs_create_x8("inject_hlinesel", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_hlinesel);
	edac_debugfs_create_x8("inject_deviceptr1", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_deviceptr1);
	edac_debugfs_create_x8("inject_deviceptr2", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_deviceptr2);
	edac_debugfs_create_x16("inject_eccmask1", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_eccmask1);
	edac_debugfs_create_x16("inject_eccmask2", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_eccmask2);
	edac_debugfs_create_file("inject_enable", S_IWUSR, priv->debugfs,
				&mci->dev, &i5100_inject_enable_fops);

	return 0;

}