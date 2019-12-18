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
typedef  int /*<<< orphan*/  time_t ;
struct archive_write_disk {int /*<<< orphan*/  name; int /*<<< orphan*/  mode; int /*<<< orphan*/  fd; int /*<<< orphan*/  entry; int /*<<< orphan*/  start_time; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_atime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_atime_is_set (int /*<<< orphan*/ ) ; 
 long archive_entry_atime_nsec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_birthtime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_birthtime_is_set (int /*<<< orphan*/ ) ; 
 long archive_entry_birthtime_nsec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_ctime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_ctime_is_set (int /*<<< orphan*/ ) ; 
 long archive_entry_ctime_nsec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_mtime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_mtime_is_set (int /*<<< orphan*/ ) ; 
 long archive_entry_mtime_nsec (int /*<<< orphan*/ ) ; 
 int set_times (struct archive_write_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int
set_times_from_entry(struct archive_write_disk *a)
{
	time_t atime, birthtime, mtime, cctime;
	long atime_nsec, birthtime_nsec, mtime_nsec, ctime_nsec;

	/* Suitable defaults. */
	atime = birthtime = mtime = cctime = a->start_time;
	atime_nsec = birthtime_nsec = mtime_nsec = ctime_nsec = 0;

	/* If no time was provided, we're done. */
	if (!archive_entry_atime_is_set(a->entry)
#if HAVE_STRUCT_STAT_ST_BIRTHTIME
	    && !archive_entry_birthtime_is_set(a->entry)
#endif
	    && !archive_entry_mtime_is_set(a->entry))
		return (ARCHIVE_OK);

	if (archive_entry_atime_is_set(a->entry)) {
		atime = archive_entry_atime(a->entry);
		atime_nsec = archive_entry_atime_nsec(a->entry);
	}
	if (archive_entry_birthtime_is_set(a->entry)) {
		birthtime = archive_entry_birthtime(a->entry);
		birthtime_nsec = archive_entry_birthtime_nsec(a->entry);
	}
	if (archive_entry_mtime_is_set(a->entry)) {
		mtime = archive_entry_mtime(a->entry);
		mtime_nsec = archive_entry_mtime_nsec(a->entry);
	}
	if (archive_entry_ctime_is_set(a->entry)) {
		cctime = archive_entry_ctime(a->entry);
		ctime_nsec = archive_entry_ctime_nsec(a->entry);
	}

	return set_times(a, a->fd, a->mode, a->name,
			 atime, atime_nsec,
			 birthtime, birthtime_nsec,
			 mtime, mtime_nsec,
			 cctime, ctime_nsec);
}