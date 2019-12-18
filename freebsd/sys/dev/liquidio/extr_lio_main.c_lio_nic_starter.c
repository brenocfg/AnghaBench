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
struct octeon_device {scalar_t__ app_mode; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_DEV_RUNNING ; 
 scalar_t__ LIO_DRV_NIC_APP ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,...) ; 
 scalar_t__ lio_init_nic_module (struct octeon_device*) ; 
 scalar_t__ octeon_enable_sriov (struct octeon_device*) ; 

__attribute__((used)) static int
lio_nic_starter(struct octeon_device *oct)
{
	int	ret = 0;

	atomic_store_rel_int(&oct->status, LIO_DEV_RUNNING);

	if (oct->app_mode && oct->app_mode == LIO_DRV_NIC_APP) {
		if (lio_init_nic_module(oct)) {
			lio_dev_err(oct, "NIC initialization failed\n");
			ret = -1;
#ifdef CAVIUM_ONiLY_23XX_VF
		} else {
			if (octeon_enable_sriov(oct) < 0)
				ret = -1;
#endif
		}
	} else {
		lio_dev_err(oct,
			    "Unexpected application running on NIC (%d). Check firmware.\n",
			    oct->app_mode);
		ret = -1;
	}

	return (ret);
}