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
struct TYPE_2__ {int /*<<< orphan*/  Reserved3; } ;
typedef  int /*<<< orphan*/  CONFIG_PAGE_IOC_2 ;

/* Variables and functions */
 int /*<<< orphan*/  CapabilitiesFlags ; 
 int MPI_IOC_PAGE_2_RAID_VOLUME_MAX ; 
 int /*<<< orphan*/  MPT_2_HOST16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* RaidVolume ; 

void
mpt2host_config_page_ioc2(CONFIG_PAGE_IOC_2 *ioc2)
{
	int i;

	MPT_2_HOST32(ioc2, CapabilitiesFlags);
	for (i = 0; i < MPI_IOC_PAGE_2_RAID_VOLUME_MAX; i++) {
		MPT_2_HOST16(ioc2, RaidVolume[i].Reserved3);
	}
}