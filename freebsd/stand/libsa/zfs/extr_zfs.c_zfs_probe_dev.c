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
typedef  scalar_t__ uint64_t ;
struct zfs_probe_args {int fd; scalar_t__ secsz; char const* devname; scalar_t__* pool_guid; } ;
struct ptable {int dummy; } ;
struct disk_devdesc {int d_partition; int d_slice; } ;
struct TYPE_2__ {scalar_t__ (* arch_getdev ) (void**,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int D_PARTNONE ; 
 int D_SLICENONE ; 
 int ENXIO ; 
 int /*<<< orphan*/  O_RDONLY ; 
 TYPE_1__ archsw ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct disk_devdesc*) ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptable_close (struct ptable*) ; 
 int /*<<< orphan*/  ptable_iterate (struct ptable*,struct zfs_probe_args*,int /*<<< orphan*/ ) ; 
 struct ptable* ptable_open (struct zfs_probe_args*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (void**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_diskread ; 
 int zfs_probe (int,scalar_t__*) ; 
 int /*<<< orphan*/  zfs_probe_partition ; 

int
zfs_probe_dev(const char *devname, uint64_t *pool_guid)
{
	struct disk_devdesc *dev;
	struct ptable *table;
	struct zfs_probe_args pa;
	uint64_t mediasz;
	int ret;

	if (pool_guid)
		*pool_guid = 0;
	pa.fd = open(devname, O_RDONLY);
	if (pa.fd == -1)
		return (ENXIO);
	/*
	 * We will not probe the whole disk, we can not boot from such
	 * disks and some systems will misreport the disk sizes and will
	 * hang while accessing the disk.
	 */
	if (archsw.arch_getdev((void **)&dev, devname, NULL) == 0) {
		int partition = dev->d_partition;
		int slice = dev->d_slice;

		free(dev);
		if (partition != D_PARTNONE && slice != D_SLICENONE) {
			ret = zfs_probe(pa.fd, pool_guid);
			if (ret == 0)
				return (0);
		}
	}

	/* Probe each partition */
	ret = ioctl(pa.fd, DIOCGMEDIASIZE, &mediasz);
	if (ret == 0)
		ret = ioctl(pa.fd, DIOCGSECTORSIZE, &pa.secsz);
	if (ret == 0) {
		pa.devname = devname;
		pa.pool_guid = pool_guid;
		table = ptable_open(&pa, mediasz / pa.secsz, pa.secsz,
		    zfs_diskread);
		if (table != NULL) {
			ptable_iterate(table, &pa, zfs_probe_partition);
			ptable_close(table);
		}
	}
	close(pa.fd);
	if (pool_guid && *pool_guid == 0)
		ret = ENXIO;
	return (ret);
}