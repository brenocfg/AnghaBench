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
typedef  int /*<<< orphan*/  zfs_secpolicy_func_t ;
typedef  int /*<<< orphan*/  zfs_ioc_t ;
typedef  int /*<<< orphan*/  zfs_ioc_legacy_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DATASET_NAME ; 
 int /*<<< orphan*/  POOL_CHECK_SUSPENDED ; 
 int /*<<< orphan*/  zfs_ioctl_register_legacy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zfs_ioctl_register_dataset_read_secpolicy(zfs_ioc_t ioc,
    zfs_ioc_legacy_func_t *func, zfs_secpolicy_func_t *secpolicy)
{
	zfs_ioctl_register_legacy(ioc, func, secpolicy,
	    DATASET_NAME, B_FALSE, POOL_CHECK_SUSPENDED);
}