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
struct hci_dev {int /*<<< orphan*/  debugfs; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dnld_rdy; int /*<<< orphan*/  hsmode; int /*<<< orphan*/  gpio_gap; int /*<<< orphan*/  psmode; } ;
struct btmrvl_private {TYPE_2__ btmrvl_dev; TYPE_1__* adapter; struct btmrvl_debugfs_data* debugfs_data; } ;
struct btmrvl_debugfs_data {void* status_dir; void* config_dir; } ;
struct TYPE_3__ {int /*<<< orphan*/  hs_state; int /*<<< orphan*/  ps_state; int /*<<< orphan*/  psmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  btmrvl_hscfgcmd_fops ; 
 int /*<<< orphan*/  btmrvl_hscmd_fops ; 
 int /*<<< orphan*/  btmrvl_pscmd_fops ; 
 void* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,void*,struct btmrvl_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x16 (char*,int,void*,int /*<<< orphan*/ *) ; 
 struct btmrvl_private* hci_get_drvdata (struct hci_dev*) ; 
 struct btmrvl_debugfs_data* kzalloc (int,int /*<<< orphan*/ ) ; 

void btmrvl_debugfs_init(struct hci_dev *hdev)
{
	struct btmrvl_private *priv = hci_get_drvdata(hdev);
	struct btmrvl_debugfs_data *dbg;

	if (!hdev->debugfs)
		return;

	dbg = kzalloc(sizeof(*dbg), GFP_KERNEL);
	priv->debugfs_data = dbg;

	if (!dbg) {
		BT_ERR("Can not allocate memory for btmrvl_debugfs_data.");
		return;
	}

	dbg->config_dir = debugfs_create_dir("config", hdev->debugfs);

	debugfs_create_u8("psmode", 0644, dbg->config_dir,
			  &priv->btmrvl_dev.psmode);
	debugfs_create_file("pscmd", 0644, dbg->config_dir,
			    priv, &btmrvl_pscmd_fops);
	debugfs_create_x16("gpiogap", 0644, dbg->config_dir,
			   &priv->btmrvl_dev.gpio_gap);
	debugfs_create_u8("hsmode", 0644, dbg->config_dir,
			  &priv->btmrvl_dev.hsmode);
	debugfs_create_file("hscmd", 0644, dbg->config_dir,
			    priv, &btmrvl_hscmd_fops);
	debugfs_create_file("hscfgcmd", 0644, dbg->config_dir,
			    priv, &btmrvl_hscfgcmd_fops);

	dbg->status_dir = debugfs_create_dir("status", hdev->debugfs);
	debugfs_create_u8("curpsmode", 0444, dbg->status_dir,
			  &priv->adapter->psmode);
	debugfs_create_u8("psstate", 0444, dbg->status_dir,
			  &priv->adapter->ps_state);
	debugfs_create_u8("hsstate", 0444, dbg->status_dir,
			  &priv->adapter->hs_state);
	debugfs_create_u8("txdnldready", 0444, dbg->status_dir,
			  &priv->btmrvl_dev.tx_dnld_rdy);
}