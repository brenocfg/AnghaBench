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
 scalar_t__ RDMA_USER_CM_MAX_ABI_VERSION ; 
 scalar_t__ RDMA_USER_CM_MIN_ABI_VERSION ; 
 scalar_t__ abi_ver ; 
 int /*<<< orphan*/  ibv_get_sysfs_path () ; 
 scalar_t__ ibv_read_sysfs_file (int /*<<< orphan*/ ,char*,char*,int) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int check_abi_version(void)
{
	char value[8];

	if ((ibv_read_sysfs_file(ibv_get_sysfs_path(),
				 "class/misc/rdma_cm/abi_version",
				 value, sizeof value) < 0) &&
	    (ibv_read_sysfs_file(ibv_get_sysfs_path(),
				 "class/infiniband_ucma/abi_version",
				 value, sizeof value) < 0)) {
		/*
		 * Older version of Linux do not have class/misc.  To support
		 * backports, assume the most recent version of the ABI.  If
		 * we're wrong, we'll simply fail later when calling the ABI.
		 */
		return 0;
	}

	abi_ver = strtol(value, NULL, 10);
	if (abi_ver < RDMA_USER_CM_MIN_ABI_VERSION ||
	    abi_ver > RDMA_USER_CM_MAX_ABI_VERSION) {
		return -1;
	}
	return 0;
}