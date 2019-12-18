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

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  firmware_debugfs_root ; 
 int /*<<< orphan*/  fops_zynqmp_pm_dbgfs ; 

void zynqmp_pm_api_debugfs_init(void)
{
	/* Initialize debugfs interface */
	firmware_debugfs_root = debugfs_create_dir("zynqmp-firmware", NULL);
	debugfs_create_file("pm", 0660, firmware_debugfs_root, NULL,
			    &fops_zynqmp_pm_dbgfs);
}