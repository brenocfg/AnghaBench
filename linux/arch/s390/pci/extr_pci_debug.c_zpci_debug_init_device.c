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
struct zpci_dev {int /*<<< orphan*/  debugfs_dev; } ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct zpci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_pci_perf_fops ; 
 int /*<<< orphan*/  debugfs_root ; 

void zpci_debug_init_device(struct zpci_dev *zdev, const char *name)
{
	zdev->debugfs_dev = debugfs_create_dir(name, debugfs_root);

	debugfs_create_file("statistics", S_IFREG | S_IRUGO | S_IWUSR,
			    zdev->debugfs_dev, zdev, &debugfs_pci_perf_fops);
}