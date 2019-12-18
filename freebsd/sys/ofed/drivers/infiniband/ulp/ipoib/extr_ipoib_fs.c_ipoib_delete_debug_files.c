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
struct ipoib_dev_priv {scalar_t__ path_dentry; scalar_t__ mcg_dentry; } ;
struct ifnet {struct ipoib_dev_priv* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (scalar_t__) ; 

void ipoib_delete_debug_files(struct ifnet *dev)
{
	struct ipoib_dev_priv *priv = dev->if_softc;

	if (priv->mcg_dentry)
		debugfs_remove(priv->mcg_dentry);
	if (priv->path_dentry)
		debugfs_remove(priv->path_dentry);
}