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
struct ipoib_dev_priv {void* path_dentry; void* mcg_dentry; } ;
struct ifnet {struct ipoib_dev_priv* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 void* debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ifnet*,int /*<<< orphan*/ *) ; 
 char* if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ipoib_mcg_fops ; 
 int /*<<< orphan*/  ipoib_path_fops ; 
 int /*<<< orphan*/  ipoib_root ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

void ipoib_create_debug_files(struct ifnet *dev)
{
	struct ipoib_dev_priv *priv = dev->if_softc;
	char name[IFNAMSIZ + sizeof "_path"];

	snprintf(name, sizeof name, "%s_mcg", if_name(dev));
	priv->mcg_dentry = debugfs_create_file(name, S_IFREG | S_IRUGO,
					       ipoib_root, dev, &ipoib_mcg_fops);
	if (!priv->mcg_dentry)
		ipoib_warn(priv, "failed to create mcg debug file\n");

	snprintf(name, sizeof name, "%s_path", if_name(dev));
	priv->path_dentry = debugfs_create_file(name, S_IFREG | S_IRUGO,
						ipoib_root, dev, &ipoib_path_fops);
	if (!priv->path_dentry)
		ipoib_warn(priv, "failed to create path debug file\n");
}