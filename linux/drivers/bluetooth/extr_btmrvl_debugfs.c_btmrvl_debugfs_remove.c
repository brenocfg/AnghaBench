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
struct hci_dev {int dummy; } ;
struct btmrvl_private {struct btmrvl_debugfs_data* debugfs_data; } ;
struct btmrvl_debugfs_data {int /*<<< orphan*/  status_dir; int /*<<< orphan*/  config_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct btmrvl_private* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree (struct btmrvl_debugfs_data*) ; 

void btmrvl_debugfs_remove(struct hci_dev *hdev)
{
	struct btmrvl_private *priv = hci_get_drvdata(hdev);
	struct btmrvl_debugfs_data *dbg = priv->debugfs_data;

	if (!dbg)
		return;

	debugfs_remove_recursive(dbg->config_dir);
	debugfs_remove_recursive(dbg->status_dir);

	kfree(dbg);
}