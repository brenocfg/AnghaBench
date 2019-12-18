#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct TYPE_14__ {int /*<<< orphan*/  tv_nsec; } ;
struct TYPE_13__ {int tv_nsec; } ;
struct TYPE_12__ {int tv_nsec; } ;
struct TYPE_11__ {int tv_nsec; } ;
struct TYPE_10__ {int tv_nsec; } ;
struct TYPE_9__ {int tv_nsec; } ;
struct TYPE_8__ {int tv_nsec; } ;
typedef  struct stat {int st_atime_n; int st_ctime_n; int st_mtime_n; int st_uatime; int st_uctime; int st_umtime; int st_atime_usec; int st_ctime_usec; int st_mtime_usec; TYPE_7__ st_birthtimespec; TYPE_6__ st_mtim; TYPE_5__ st_ctim; TYPE_4__ st_atim; TYPE_3__ st_mtimespec; TYPE_2__ st_ctimespec; TYPE_1__ st_atimespec; int /*<<< orphan*/  st_mode; scalar_t__ st_size; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_nlink; scalar_t__ st_ino; scalar_t__ st_uid; scalar_t__ st_gid; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_birthtime; int /*<<< orphan*/  st_atime; } const stat ;
struct archive_entry {int stat_valid; struct stat const* stat; } ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_atime (struct archive_entry*) ; 
 int archive_entry_atime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_birthtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_birthtime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_ctime (struct archive_entry*) ; 
 int archive_entry_ctime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_dev (struct archive_entry*) ; 
 scalar_t__ archive_entry_gid (struct archive_entry*) ; 
 scalar_t__ archive_entry_ino64 (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int archive_entry_mtime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_nlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_rdev (struct archive_entry*) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 scalar_t__ archive_entry_uid (struct archive_entry*) ; 
 struct stat const* calloc (int,int) ; 

const struct stat *
archive_entry_stat(struct archive_entry *entry)
{
	struct stat *st;
	if (entry->stat == NULL) {
		entry->stat = calloc(1, sizeof(*st));
		if (entry->stat == NULL)
			return (NULL);
		entry->stat_valid = 0;
	}

	/*
	 * If none of the underlying fields have been changed, we
	 * don't need to regenerate.  In theory, we could use a bitmap
	 * here to flag only those items that have changed, but the
	 * extra complexity probably isn't worth it.  It will be very
	 * rare for anyone to change just one field then request a new
	 * stat structure.
	 */
	if (entry->stat_valid)
		return (entry->stat);

	st = entry->stat;
	/*
	 * Use the public interfaces to extract items, so that
	 * the appropriate conversions get invoked.
	 */
	st->st_atime = archive_entry_atime(entry);
#if HAVE_STRUCT_STAT_ST_BIRTHTIME
	st->st_birthtime = archive_entry_birthtime(entry);
#endif
	st->st_ctime = archive_entry_ctime(entry);
	st->st_mtime = archive_entry_mtime(entry);
	st->st_dev = archive_entry_dev(entry);
	st->st_gid = (gid_t)archive_entry_gid(entry);
	st->st_uid = (uid_t)archive_entry_uid(entry);
	st->st_ino = (ino_t)archive_entry_ino64(entry);
	st->st_nlink = archive_entry_nlink(entry);
	st->st_rdev = archive_entry_rdev(entry);
	st->st_size = (off_t)archive_entry_size(entry);
	st->st_mode = archive_entry_mode(entry);

	/*
	 * On systems that support high-res timestamps, copy that
	 * information into struct stat.
	 */
#if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC
	st->st_atimespec.tv_nsec = archive_entry_atime_nsec(entry);
	st->st_ctimespec.tv_nsec = archive_entry_ctime_nsec(entry);
	st->st_mtimespec.tv_nsec = archive_entry_mtime_nsec(entry);
#elif HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
	st->st_atim.tv_nsec = archive_entry_atime_nsec(entry);
	st->st_ctim.tv_nsec = archive_entry_ctime_nsec(entry);
	st->st_mtim.tv_nsec = archive_entry_mtime_nsec(entry);
#elif HAVE_STRUCT_STAT_ST_MTIME_N
	st->st_atime_n = archive_entry_atime_nsec(entry);
	st->st_ctime_n = archive_entry_ctime_nsec(entry);
	st->st_mtime_n = archive_entry_mtime_nsec(entry);
#elif HAVE_STRUCT_STAT_ST_UMTIME
	st->st_uatime = archive_entry_atime_nsec(entry) / 1000;
	st->st_uctime = archive_entry_ctime_nsec(entry) / 1000;
	st->st_umtime = archive_entry_mtime_nsec(entry) / 1000;
#elif HAVE_STRUCT_STAT_ST_MTIME_USEC
	st->st_atime_usec = archive_entry_atime_nsec(entry) / 1000;
	st->st_ctime_usec = archive_entry_ctime_nsec(entry) / 1000;
	st->st_mtime_usec = archive_entry_mtime_nsec(entry) / 1000;
#endif
#if HAVE_STRUCT_STAT_ST_BIRTHTIMESPEC_TV_NSEC
	st->st_birthtimespec.tv_nsec = archive_entry_birthtime_nsec(entry);
#endif

	/*
	 * TODO: On Linux, store 32 or 64 here depending on whether
	 * the cached stat structure is a stat32 or a stat64.  This
	 * will allow us to support both variants interchangeably.
	 */
	entry->stat_valid = 1;

	return (st);
}