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
struct tree {int flags; } ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct restore_time {int mtime_nsec; int atime_nsec; scalar_t__ filetype; int /*<<< orphan*/  name; int /*<<< orphan*/  atime; int /*<<< orphan*/  mtime; scalar_t__ noatime; } ;

/* Variables and functions */
 scalar_t__ AE_IFLNK ; 
 int close (int) ; 
 scalar_t__ futimens (int,struct timespec*) ; 
 scalar_t__ futimes (int,struct timeval*) ; 
 scalar_t__ futimesat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ lutimes (int /*<<< orphan*/ ,struct timeval*) ; 
 int needsRestoreTimes ; 
 int /*<<< orphan*/  tree_current_dir_fd (struct tree*) ; 
 scalar_t__ utimes (int /*<<< orphan*/ ,struct timeval*) ; 

__attribute__((used)) static int
close_and_restore_time(int fd, struct tree *t, struct restore_time *rt)
{
#ifndef HAVE_UTIMES
	(void)t; /* UNUSED */
	(void)rt; /* UNUSED */
	return (close(fd));
#else
#if defined(HAVE_FUTIMENS) && !defined(__CYGWIN__)
	struct timespec timespecs[2];
#endif
	struct timeval times[2];

	if ((t->flags & needsRestoreTimes) == 0 || rt->noatime) {
		if (fd >= 0)
			return (close(fd));
		else
			return (0);
	}

#if defined(HAVE_FUTIMENS) && !defined(__CYGWIN__)
	timespecs[1].tv_sec = rt->mtime;
	timespecs[1].tv_nsec = rt->mtime_nsec;

	timespecs[0].tv_sec = rt->atime;
	timespecs[0].tv_nsec = rt->atime_nsec;
	/* futimens() is defined in POSIX.1-2008. */
	if (futimens(fd, timespecs) == 0)
		return (close(fd));
#endif

	times[1].tv_sec = rt->mtime;
	times[1].tv_usec = rt->mtime_nsec / 1000;

	times[0].tv_sec = rt->atime;
	times[0].tv_usec = rt->atime_nsec / 1000;

#if !defined(HAVE_FUTIMENS) && defined(HAVE_FUTIMES) && !defined(__CYGWIN__)
	if (futimes(fd, times) == 0)
		return (close(fd));
#endif
	close(fd);
#if defined(HAVE_FUTIMESAT)
	if (futimesat(tree_current_dir_fd(t), rt->name, times) == 0)
		return (0);
#endif
#ifdef HAVE_LUTIMES
	if (lutimes(rt->name, times) != 0)
#else
	if (AE_IFLNK != rt->filetype && utimes(rt->name, times) != 0)
#endif
		return (-1);
#endif
	return (0);
}