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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_cfg_fname_kset ; 
 int /*<<< orphan*/  fw_cfg_io_cleanup () ; 
 int /*<<< orphan*/  fw_cfg_kobj_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_cfg_kset_unregister_recursive (int /*<<< orphan*/ ) ; 
 TYPE_1__ fw_cfg_rev_attr ; 
 int /*<<< orphan*/  fw_cfg_sel_ko ; 
 int /*<<< orphan*/  fw_cfg_sysfs_cache_cleanup () ; 
 int /*<<< orphan*/  fw_cfg_top_ko ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fw_cfg_sysfs_remove(struct platform_device *pdev)
{
	pr_debug("fw_cfg: unloading.\n");
	fw_cfg_sysfs_cache_cleanup();
	sysfs_remove_file(fw_cfg_top_ko, &fw_cfg_rev_attr.attr);
	fw_cfg_io_cleanup();
	fw_cfg_kset_unregister_recursive(fw_cfg_fname_kset);
	fw_cfg_kobj_cleanup(fw_cfg_sel_ko);
	return 0;
}