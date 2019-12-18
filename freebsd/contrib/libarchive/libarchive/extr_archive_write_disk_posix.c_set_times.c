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
typedef  scalar_t__ time_t ;
struct archive_write_disk {scalar_t__ user_uid; int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int set_time (int,int,char const*,scalar_t__,long,scalar_t__,long) ; 
 scalar_t__ set_time_tru64 (int,int,char const*,scalar_t__,long,scalar_t__,long,scalar_t__,long) ; 

__attribute__((used)) static int
set_times(struct archive_write_disk *a,
    int fd, int mode, const char *name,
    time_t atime, long atime_nanos,
    time_t birthtime, long birthtime_nanos,
    time_t mtime, long mtime_nanos,
    time_t cctime, long ctime_nanos)
{
	/* Note: set_time doesn't use libarchive return conventions!
	 * It uses syscall conventions.  So 0 here instead of ARCHIVE_OK. */
	int r1 = 0, r2 = 0;

#ifdef F_SETTIMES
	 /*
	 * on Tru64 try own fcntl first which can restore even the
	 * ctime, fall back to default code path below if it fails
	 * or if we are not running as root
	 */
	if (a->user_uid == 0 &&
	    set_time_tru64(fd, mode, name,
			   atime, atime_nanos, mtime,
			   mtime_nanos, cctime, ctime_nanos) == 0) {
		return (ARCHIVE_OK);
	}
#else /* Tru64 */
	(void)cctime; /* UNUSED */
	(void)ctime_nanos; /* UNUSED */
#endif /* Tru64 */

#ifdef HAVE_STRUCT_STAT_ST_BIRTHTIME
	/*
	 * If you have struct stat.st_birthtime, we assume BSD
	 * birthtime semantics, in which {f,l,}utimes() updates
	 * birthtime to earliest mtime.  So we set the time twice,
	 * first using the birthtime, then using the mtime.  If
	 * birthtime == mtime, this isn't necessary, so we skip it.
	 * If birthtime > mtime, then this won't work, so we skip it.
	 */
	if (birthtime < mtime
	    || (birthtime == mtime && birthtime_nanos < mtime_nanos))
		r1 = set_time(fd, mode, name,
			      atime, atime_nanos,
			      birthtime, birthtime_nanos);
#else
	(void)birthtime; /* UNUSED */
	(void)birthtime_nanos; /* UNUSED */
#endif
	r2 = set_time(fd, mode, name,
		      atime, atime_nanos,
		      mtime, mtime_nanos);
	if (r1 != 0 || r2 != 0) {
		archive_set_error(&a->archive, errno,
				  "Can't restore time");
		return (ARCHIVE_WARN);
	}
	return (ARCHIVE_OK);
}