#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  pd_handle; } ;
typedef  TYPE_1__ pdinfo_t ;

/* Variables and functions */
 scalar_t__ efizfs_get_guid_by_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int probe_zfs_currdev (int /*<<< orphan*/ ) ; 
 int sanity_check_currdev () ; 
 int /*<<< orphan*/  set_currdev_pdinfo (TYPE_1__*) ; 

__attribute__((used)) static bool
try_as_currdev(pdinfo_t *hd, pdinfo_t *pp)
{
	uint64_t guid;

#ifdef EFI_ZFS_BOOT
	/*
	 * If there's a zpool on this device, try it as a ZFS
	 * filesystem, which has somewhat different setup than all
	 * other types of fs due to imperfect loader integration.
	 * This all stems from ZFS being both a device (zpool) and
	 * a filesystem, plus the boot env feature.
	 */
	if (efizfs_get_guid_by_handle(pp->pd_handle, &guid))
		return (probe_zfs_currdev(guid));
#endif
	/*
	 * All other filesystems just need the pdinfo
	 * initialized in the standard way.
	 */
	set_currdev_pdinfo(pp);
	return (sanity_check_currdev());
}