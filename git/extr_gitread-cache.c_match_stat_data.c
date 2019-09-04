#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int sec; } ;
struct TYPE_3__ {unsigned int sec; } ;
struct stat_data {unsigned int sd_uid; unsigned int sd_gid; unsigned int sd_ino; unsigned int sd_size; TYPE_2__ sd_ctime; TYPE_1__ sd_mtime; } ;
struct stat {scalar_t__ st_size; scalar_t__ st_ino; scalar_t__ st_gid; scalar_t__ st_uid; scalar_t__ st_ctime; scalar_t__ st_mtime; } ;

/* Variables and functions */
 int CTIME_CHANGED ; 
 int DATA_CHANGED ; 
 int INODE_CHANGED ; 
 int MTIME_CHANGED ; 
 int OWNER_CHANGED ; 
 scalar_t__ check_stat ; 
 scalar_t__ trust_ctime ; 

int match_stat_data(const struct stat_data *sd, struct stat *st)
{
	int changed = 0;

	if (sd->sd_mtime.sec != (unsigned int)st->st_mtime)
		changed |= MTIME_CHANGED;
	if (trust_ctime && check_stat &&
	    sd->sd_ctime.sec != (unsigned int)st->st_ctime)
		changed |= CTIME_CHANGED;

#ifdef USE_NSEC
	if (check_stat && sd->sd_mtime.nsec != ST_MTIME_NSEC(*st))
		changed |= MTIME_CHANGED;
	if (trust_ctime && check_stat &&
	    sd->sd_ctime.nsec != ST_CTIME_NSEC(*st))
		changed |= CTIME_CHANGED;
#endif

	if (check_stat) {
		if (sd->sd_uid != (unsigned int) st->st_uid ||
			sd->sd_gid != (unsigned int) st->st_gid)
			changed |= OWNER_CHANGED;
		if (sd->sd_ino != (unsigned int) st->st_ino)
			changed |= INODE_CHANGED;
	}

#ifdef USE_STDEV
	/*
	 * st_dev breaks on network filesystems where different
	 * clients will have different views of what "device"
	 * the filesystem is on
	 */
	if (check_stat && sd->sd_dev != (unsigned int) st->st_dev)
			changed |= INODE_CHANGED;
#endif

	if (sd->sd_size != (unsigned int) st->st_size)
		changed |= DATA_CHANGED;

	return changed;
}