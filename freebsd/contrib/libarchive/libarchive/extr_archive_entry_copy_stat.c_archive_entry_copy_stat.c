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
struct TYPE_14__ {int /*<<< orphan*/  tv_nsec; } ;
struct TYPE_13__ {int tv_nsec; } ;
struct TYPE_12__ {int tv_nsec; } ;
struct TYPE_11__ {int tv_nsec; } ;
struct TYPE_10__ {int tv_nsec; } ;
struct TYPE_9__ {int tv_nsec; } ;
struct TYPE_8__ {int tv_nsec; } ;
struct stat {int st_atime_nsec; int st_ctime_nsec; int st_mtime_nsec; int st_atime_n; int st_ctime_n; int st_mtime_n; int st_uatime; int st_uctime; int st_umtime; int st_atime_usec; int st_ctime_usec; int st_mtime_usec; int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_birthtime; TYPE_7__ st_birthtimespec; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_atime; TYPE_6__ st_mtim; TYPE_5__ st_ctim; TYPE_4__ st_atim; TYPE_3__ st_mtimespec; TYPE_2__ st_ctimespec; TYPE_1__ st_atimespec; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_set_atime (struct archive_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_set_birthtime (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_set_dev (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_ino (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_set_nlink (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_rdev (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_unset_birthtime (struct archive_entry*) ; 

void
archive_entry_copy_stat(struct archive_entry *entry, const struct stat *st)
{
#if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC
	archive_entry_set_atime(entry, st->st_atime, st->st_atimespec.tv_nsec);
	archive_entry_set_ctime(entry, st->st_ctime, st->st_ctimespec.tv_nsec);
	archive_entry_set_mtime(entry, st->st_mtime, st->st_mtimespec.tv_nsec);
#elif HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
	archive_entry_set_atime(entry, st->st_atime, st->st_atim.tv_nsec);
	archive_entry_set_ctime(entry, st->st_ctime, st->st_ctim.tv_nsec);
	archive_entry_set_mtime(entry, st->st_mtime, st->st_mtim.tv_nsec);
#elif HAVE_STRUCT_STAT_ST_MTIME_NSEC
	archive_entry_set_atime(entry, st->st_atime, st->st_atime_nsec);
	archive_entry_set_ctime(entry, st->st_ctime, st->st_ctime_nsec);
	archive_entry_set_mtime(entry, st->st_mtime, st->st_mtime_nsec);
#elif HAVE_STRUCT_STAT_ST_MTIME_N
	archive_entry_set_atime(entry, st->st_atime, st->st_atime_n);
	archive_entry_set_ctime(entry, st->st_ctime, st->st_ctime_n);
	archive_entry_set_mtime(entry, st->st_mtime, st->st_mtime_n);
#elif HAVE_STRUCT_STAT_ST_UMTIME
	archive_entry_set_atime(entry, st->st_atime, st->st_uatime * 1000);
	archive_entry_set_ctime(entry, st->st_ctime, st->st_uctime * 1000);
	archive_entry_set_mtime(entry, st->st_mtime, st->st_umtime * 1000);
#elif HAVE_STRUCT_STAT_ST_MTIME_USEC
	archive_entry_set_atime(entry, st->st_atime, st->st_atime_usec * 1000);
	archive_entry_set_ctime(entry, st->st_ctime, st->st_ctime_usec * 1000);
	archive_entry_set_mtime(entry, st->st_mtime, st->st_mtime_usec * 1000);
#else
	archive_entry_set_atime(entry, st->st_atime, 0);
	archive_entry_set_ctime(entry, st->st_ctime, 0);
	archive_entry_set_mtime(entry, st->st_mtime, 0);
#endif
#if HAVE_STRUCT_STAT_ST_BIRTHTIMESPEC_TV_NSEC
	archive_entry_set_birthtime(entry, st->st_birthtime, st->st_birthtimespec.tv_nsec);
#elif HAVE_STRUCT_STAT_ST_BIRTHTIME
	archive_entry_set_birthtime(entry, st->st_birthtime, 0);
#else
	archive_entry_unset_birthtime(entry);
#endif
	archive_entry_set_dev(entry, st->st_dev);
	archive_entry_set_gid(entry, st->st_gid);
	archive_entry_set_uid(entry, st->st_uid);
	archive_entry_set_ino(entry, st->st_ino);
	archive_entry_set_nlink(entry, st->st_nlink);
	archive_entry_set_rdev(entry, st->st_rdev);
	archive_entry_set_size(entry, st->st_size);
	archive_entry_set_mode(entry, st->st_mode);
}