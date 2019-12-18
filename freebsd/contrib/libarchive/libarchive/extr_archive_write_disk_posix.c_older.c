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
struct TYPE_4__ {int tv_nsec; } ;
struct TYPE_3__ {int tv_nsec; } ;
struct stat {int st_mtime_n; int st_umtime; int st_mtime_usec; TYPE_2__ st_mtim; TYPE_1__ st_mtimespec; int /*<<< orphan*/  st_mtime; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int archive_entry_mtime_nsec (struct archive_entry*) ; 
 scalar_t__ to_int64_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
older(struct stat *st, struct archive_entry *entry)
{
	/* First, test the seconds and return if we have a definite answer. */
	/* Definitely older. */
	if (to_int64_time(st->st_mtime) < to_int64_time(archive_entry_mtime(entry)))
		return (1);
	/* Definitely younger. */
	if (to_int64_time(st->st_mtime) > to_int64_time(archive_entry_mtime(entry)))
		return (0);
	/* If this platform supports fractional seconds, try those. */
#if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC
	/* Definitely older. */
	if (st->st_mtimespec.tv_nsec < archive_entry_mtime_nsec(entry))
		return (1);
#elif HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC
	/* Definitely older. */
	if (st->st_mtim.tv_nsec < archive_entry_mtime_nsec(entry))
		return (1);
#elif HAVE_STRUCT_STAT_ST_MTIME_N
	/* older. */
	if (st->st_mtime_n < archive_entry_mtime_nsec(entry))
		return (1);
#elif HAVE_STRUCT_STAT_ST_UMTIME
	/* older. */
	if (st->st_umtime * 1000 < archive_entry_mtime_nsec(entry))
		return (1);
#elif HAVE_STRUCT_STAT_ST_MTIME_USEC
	/* older. */
	if (st->st_mtime_usec * 1000 < archive_entry_mtime_nsec(entry))
		return (1);
#else
	/* This system doesn't have high-res timestamps. */
#endif
	/* Same age or newer, so not older. */
	return (0);
}