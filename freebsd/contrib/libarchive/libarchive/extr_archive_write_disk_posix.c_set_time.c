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
struct utimbuf {void* modtime; void* actime; } ;
struct timeval {long tv_usec; void* tv_sec; } ;
struct timespec {long tv_nsec; void* tv_sec; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 scalar_t__ S_ISLNK (int) ; 
 int futimens (int,struct timespec*) ; 
 int futimes (int,struct timeval*) ; 
 int lutimes (char const*,struct timeval*) ; 
 int utime (char const*,struct utimbuf*) ; 
 int utimensat (int /*<<< orphan*/ ,char const*,struct timespec*,int /*<<< orphan*/ ) ; 
 int utimes (char const*,struct timeval*) ; 

__attribute__((used)) static int
set_time(int fd, int mode, const char *name,
    time_t atime, long atime_nsec,
    time_t mtime, long mtime_nsec)
{
	/* Select the best implementation for this platform. */
#if defined(HAVE_UTIMENSAT) && defined(HAVE_FUTIMENS)
	/*
	 * utimensat() and futimens() are defined in
	 * POSIX.1-2008. They support ns resolution and setting times
	 * on fds and symlinks.
	 */
	struct timespec ts[2];
	(void)mode; /* UNUSED */
	ts[0].tv_sec = atime;
	ts[0].tv_nsec = atime_nsec;
	ts[1].tv_sec = mtime;
	ts[1].tv_nsec = mtime_nsec;
	if (fd >= 0)
		return futimens(fd, ts);
	return utimensat(AT_FDCWD, name, ts, AT_SYMLINK_NOFOLLOW);

#elif HAVE_UTIMES
	/*
	 * The utimes()-family functions support µs-resolution and
	 * setting times fds and symlinks.  utimes() is documented as
	 * LEGACY by POSIX, futimes() and lutimes() are not described
	 * in POSIX.
	 */
	struct timeval times[2];

	times[0].tv_sec = atime;
	times[0].tv_usec = atime_nsec / 1000;
	times[1].tv_sec = mtime;
	times[1].tv_usec = mtime_nsec / 1000;

#ifdef HAVE_FUTIMES
	if (fd >= 0)
		return (futimes(fd, times));
#else
	(void)fd; /* UNUSED */
#endif
#ifdef HAVE_LUTIMES
	(void)mode; /* UNUSED */
	return (lutimes(name, times));
#else
	if (S_ISLNK(mode))
		return (0);
	return (utimes(name, times));
#endif

#elif defined(HAVE_UTIME)
	/*
	 * utime() is POSIX-standard but only supports 1s resolution and
	 * does not support fds or symlinks.
	 */
	struct utimbuf times;
	(void)fd; /* UNUSED */
	(void)name; /* UNUSED */
	(void)atime_nsec; /* UNUSED */
	(void)mtime_nsec; /* UNUSED */
	times.actime = atime;
	times.modtime = mtime;
	if (S_ISLNK(mode))
		return (ARCHIVE_OK);
	return (utime(name, &times));

#else
	/*
	 * We don't know how to set the time on this platform.
	 */
	(void)fd; /* UNUSED */
	(void)mode; /* UNUSED */
	(void)name; /* UNUSED */
	(void)atime_nsec; /* UNUSED */
	(void)mtime_nsec; /* UNUSED */
	return (ARCHIVE_WARN);
#endif
}