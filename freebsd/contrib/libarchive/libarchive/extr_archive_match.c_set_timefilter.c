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
typedef  void* time_t ;
struct archive_match {int newer_mtime_filter; long newer_mtime_nsec; int older_mtime_filter; long older_mtime_nsec; int newer_ctime_filter; long newer_ctime_nsec; int older_ctime_filter; long older_ctime_nsec; int /*<<< orphan*/  setflag; void* older_ctime_sec; void* newer_ctime_sec; void* older_mtime_sec; void* newer_mtime_sec; } ;

/* Variables and functions */
 int ARCHIVE_MATCH_CTIME ; 
 int ARCHIVE_MATCH_MTIME ; 
 int ARCHIVE_MATCH_NEWER ; 
 int ARCHIVE_MATCH_OLDER ; 
 int ARCHIVE_OK ; 
 scalar_t__ JUST_EQUAL (int) ; 
 int /*<<< orphan*/  TIME_IS_SET ; 

__attribute__((used)) static int
set_timefilter(struct archive_match *a, int timetype,
    time_t mtime_sec, long mtime_nsec, time_t ctime_sec, long ctime_nsec)
{
	if (timetype & ARCHIVE_MATCH_MTIME) {
		if ((timetype & ARCHIVE_MATCH_NEWER) || JUST_EQUAL(timetype)) {
			a->newer_mtime_filter = timetype;
			a->newer_mtime_sec = mtime_sec;
			a->newer_mtime_nsec = mtime_nsec;
			a->setflag |= TIME_IS_SET;
		}
		if ((timetype & ARCHIVE_MATCH_OLDER) || JUST_EQUAL(timetype)) {
			a->older_mtime_filter = timetype;
			a->older_mtime_sec = mtime_sec;
			a->older_mtime_nsec = mtime_nsec;
			a->setflag |= TIME_IS_SET;
		}
	}
	if (timetype & ARCHIVE_MATCH_CTIME) {
		if ((timetype & ARCHIVE_MATCH_NEWER) || JUST_EQUAL(timetype)) {
			a->newer_ctime_filter = timetype;
			a->newer_ctime_sec = ctime_sec;
			a->newer_ctime_nsec = ctime_nsec;
			a->setflag |= TIME_IS_SET;
		}
		if ((timetype & ARCHIVE_MATCH_OLDER) || JUST_EQUAL(timetype)) {
			a->older_ctime_filter = timetype;
			a->older_ctime_sec = ctime_sec;
			a->older_ctime_nsec = ctime_nsec;
			a->setflag |= TIME_IS_SET;
		}
	}
	return (ARCHIVE_OK);
}