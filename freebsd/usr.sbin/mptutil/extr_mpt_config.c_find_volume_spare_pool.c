#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pool_count ;
typedef  int /*<<< orphan*/  U8 ;
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_10__ {int /*<<< orphan*/  VolumeID; int /*<<< orphan*/  VolumeBus; } ;
struct TYPE_8__ {int HotSparePool; } ;
struct TYPE_9__ {int NumActiveVolumes; TYPE_1__ VolumeSettings; TYPE_3__* RaidVolume; } ;
typedef  TYPE_2__ CONFIG_PAGE_RAID_VOL_0 ;
typedef  TYPE_3__ CONFIG_PAGE_IOC_2_RAID_VOL ;
typedef  TYPE_2__ CONFIG_PAGE_IOC_2 ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS ; 
 int MPI_RAID_HOT_SPARE_POOL_0 ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int errno ; 
 int ffs (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int mpt_lookup_volume (int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mpt_raid_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* mpt_read_ioc_page (int,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* mpt_vol_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_volume_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnc (int,char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_volume_spare_pool(int fd, const char *name, int *pool)
{
	CONFIG_PAGE_RAID_VOL_0 *info;
	CONFIG_PAGE_IOC_2 *ioc2;
	CONFIG_PAGE_IOC_2_RAID_VOL *vol;
	U8 VolumeBus, VolumeID;
	int error, i, j, new_pool, pool_count[7];

	error = mpt_lookup_volume(fd, name, &VolumeBus, &VolumeID);
	if (error) {
		warnc(error, "Invalid volume %s", name);
		return (error);
	}

	info = mpt_vol_info(fd, VolumeBus, VolumeID, NULL);
	if (info == NULL)
		return (errno);

	/*
	 * Check for an existing pool other than pool 0 (used for
	 * global spares).
	 */
	if ((info->VolumeSettings.HotSparePool & ~MPI_RAID_HOT_SPARE_POOL_0) !=
	    0) {
		*pool = 1 << (ffs(info->VolumeSettings.HotSparePool &
		    ~MPI_RAID_HOT_SPARE_POOL_0) - 1);
		free(info);
		return (0);
	}
	free(info);

	/*
	 * Try to find a free pool.  First, figure out which pools are
	 * in use.
	 */
	ioc2 = mpt_read_ioc_page(fd, 2, NULL);
	if (ioc2 == NULL) {
		error = errno;
		warn("Failed to fetch volume list");
		return (error);
	}
	bzero(pool_count, sizeof(pool_count));	
	vol = ioc2->RaidVolume;
	for (i = 0; i < ioc2->NumActiveVolumes; vol++, i++) {
		info = mpt_vol_info(fd, vol->VolumeBus, vol->VolumeID, NULL);
		if (info == NULL)
			return (errno);
		for (j = 0; j < 7; j++)
			if (info->VolumeSettings.HotSparePool & (1 << (j + 1)))
				pool_count[j]++;
		free(info);
	}
	free(ioc2);

	/* Find the pool with the lowest use count. */
	new_pool = 0;
	for (i = 1; i < 7; i++)
		if (pool_count[i] < pool_count[new_pool])
			new_pool = i;
	new_pool++;

	/* Add this pool to the volume. */
	info = mpt_vol_info(fd, VolumeBus, VolumeID, NULL);
	if (info == NULL)
		return (error);
	info->VolumeSettings.HotSparePool |= (1 << new_pool);
	error = mpt_raid_action(fd, MPI_RAID_ACTION_CHANGE_VOLUME_SETTINGS,
	    VolumeBus, VolumeID, 0, *(U32 *)&info->VolumeSettings, NULL, 0,
	    NULL, NULL, 0, NULL, NULL, 0);
	if (error) {
		warnx("Failed to add spare pool %d to %s", new_pool,
		    mpt_volume_name(VolumeBus, VolumeID));
		free(info);
		return (error);
	}
	free(info);

	*pool = (1 << new_pool);
	return (0);
}