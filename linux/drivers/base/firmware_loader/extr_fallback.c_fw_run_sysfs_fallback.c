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
typedef  enum fw_opt { ____Placeholder_fw_opt } fw_opt ;
struct TYPE_2__ {scalar_t__ ignore_sysfs_fallback; } ;

/* Variables and functions */
 int FW_OPT_NOFALLBACK ; 
 int /*<<< orphan*/  LOADING_FIRMWARE ; 
 TYPE_1__ fw_fallback_config ; 
 int fw_force_sysfs_fallback (int) ; 
 int /*<<< orphan*/  pr_info_once (char*) ; 
 int security_kernel_load_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fw_run_sysfs_fallback(enum fw_opt opt_flags)
{
	int ret;

	if (fw_fallback_config.ignore_sysfs_fallback) {
		pr_info_once("Ignoring firmware sysfs fallback due to sysctl knob\n");
		return false;
	}

	if ((opt_flags & FW_OPT_NOFALLBACK))
		return false;

	/* Also permit LSMs and IMA to fail firmware sysfs fallback */
	ret = security_kernel_load_data(LOADING_FIRMWARE);
	if (ret < 0)
		return false;

	return fw_force_sysfs_fallback(opt_flags);
}