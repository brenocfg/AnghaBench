#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  Header; } ;
struct mpt_raid_disk {TYPE_3__ config_page; } ;
struct TYPE_4__ {int /*<<< orphan*/  PhysDiskNum; } ;
typedef  TYPE_1__ IOC_3_PHYS_DISK ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_RAID_PHYSDISK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mpt2host_config_page_raid_phys_disk_0 (TYPE_3__*) ; 
 int /*<<< orphan*/  mpt_prt (struct mpt_softc*,char*,int /*<<< orphan*/ ) ; 
 int mpt_read_cfg_header (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mpt_read_cur_cfg_page (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_refresh_raid_disk(struct mpt_softc *mpt, struct mpt_raid_disk *mpt_disk,
		      IOC_3_PHYS_DISK *ioc_disk)
{
	int rv;

	rv = mpt_read_cfg_header(mpt, MPI_CONFIG_PAGETYPE_RAID_PHYSDISK,
				 /*PageNumber*/0, ioc_disk->PhysDiskNum,
				 &mpt_disk->config_page.Header,
				 /*sleep_ok*/TRUE, /*timeout_ms*/5000);
	if (rv != 0) {
		mpt_prt(mpt, "mpt_refresh_raid_disk: "
			"Failed to read RAID Disk Hdr(%d)\n",
		 	ioc_disk->PhysDiskNum);
		return;
	}
	rv = mpt_read_cur_cfg_page(mpt, ioc_disk->PhysDiskNum,
				   &mpt_disk->config_page.Header,
				   sizeof(mpt_disk->config_page),
				   /*sleep_ok*/TRUE, /*timeout_ms*/5000);
	if (rv != 0)
		mpt_prt(mpt, "mpt_refresh_raid_disk: "
			"Failed to read RAID Disk Page(%d)\n",
		 	ioc_disk->PhysDiskNum);
	mpt2host_config_page_raid_phys_disk_0(&mpt_disk->config_page);
}