#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timeval {long tv_sec; long tv_usec; } ;
struct TYPE_8__ {long tv_nsec; } ;
struct TYPE_7__ {long tv_nsec; } ;
struct stat {long st_mtime; long st_atime; TYPE_2__ st_atimespec; TYPE_1__ st_mtimespec; } ;
struct TYPE_9__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; void* QuadPart; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
struct TYPE_10__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_4__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int SetFileTime (scalar_t__,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 void* WINTIME (long,long) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*) ; 
 int lstat (char const*,struct stat*) ; 
 int lutimes (char const*,struct timeval*) ; 
 int utimes (char const*,struct timeval*) ; 

int
assertion_utimes(const char *file, int line,
    const char *pathname, long at, long at_nsec, long mt, long mt_nsec)
{
	int r;

#if defined(_WIN32) && !defined(__CYGWIN__)
#define WINTIME(sec, nsec) ((Int32x32To64(sec, 10000000) + EPOC_TIME)\
	 + (((nsec)/1000)*10))
	HANDLE h;
	ULARGE_INTEGER wintm;
	FILETIME fatime, fmtime;
	FILETIME *pat, *pmt;

	assertion_count(file, line);
	h = CreateFileA(pathname,GENERIC_READ | GENERIC_WRITE,
		    FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		    FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		failure_start(file, line, "Can't access %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}

	if (at > 0 || at_nsec > 0) {
		wintm.QuadPart = WINTIME(at, at_nsec);
		fatime.dwLowDateTime = wintm.LowPart;
		fatime.dwHighDateTime = wintm.HighPart;
		pat = &fatime;
	} else
		pat = NULL;
	if (mt > 0 || mt_nsec > 0) {
		wintm.QuadPart = WINTIME(mt, mt_nsec);
		fmtime.dwLowDateTime = wintm.LowPart;
		fmtime.dwHighDateTime = wintm.HighPart;
		pmt = &fmtime;
	} else
		pmt = NULL;
	if (pat != NULL || pmt != NULL)
		r = SetFileTime(h, NULL, pat, pmt);
	else
		r = 1;
	CloseHandle(h);
	if (r == 0) {
		failure_start(file, line, "Can't SetFileTime %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	return (1);
#else /* defined(_WIN32) && !defined(__CYGWIN__) */
	struct stat st;
	struct timeval times[2];

#if !defined(__FreeBSD__)
	mt_nsec = at_nsec = 0;	/* Generic POSIX only has whole seconds. */
#endif
	if (mt == 0 && mt_nsec == 0 && at == 0 && at_nsec == 0)
		return (1);

	r = lstat(pathname, &st);
	if (r < 0) {
		failure_start(file, line, "Can't stat %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}

	if (mt == 0 && mt_nsec == 0) {
		mt = st.st_mtime;
#if defined(__FreeBSD__)
		mt_nsec = st.st_mtimespec.tv_nsec;
		/* FreeBSD generally only stores to microsecond res, so round. */
		mt_nsec = (mt_nsec / 1000) * 1000;
#endif
	}
	if (at == 0 && at_nsec == 0) {
		at = st.st_atime;
#if defined(__FreeBSD__)
		at_nsec = st.st_atimespec.tv_nsec;
		/* FreeBSD generally only stores to microsecond res, so round. */
		at_nsec = (at_nsec / 1000) * 1000;
#endif
	}

	times[1].tv_sec = mt;
	times[1].tv_usec = mt_nsec / 1000;

	times[0].tv_sec = at;
	times[0].tv_usec = at_nsec / 1000;

#ifdef HAVE_LUTIMES
	r = lutimes(pathname, times);
#else
	r = utimes(pathname, times);
#endif
	if (r < 0) {
		failure_start(file, line, "Can't utimes %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	return (1);
#endif /* defined(_WIN32) && !defined(__CYGWIN__) */
}