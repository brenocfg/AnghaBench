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
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U16 ;
typedef  int /*<<< orphan*/  CONFIG_PAGE_RAID_VOL_1 ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_RAID_VOLUME ; 
 int /*<<< orphan*/ * mpt_read_config_page (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_vol_pageaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline CONFIG_PAGE_RAID_VOL_1 *
mpt_vol_names(int fd, U8 VolumeBus, U8 VolumeID, U16 *IOCStatus)
{

	return (mpt_read_config_page(fd, MPI_CONFIG_PAGETYPE_RAID_VOLUME, 1,
	    mpt_vol_pageaddr(VolumeBus, VolumeID), IOCStatus));
}