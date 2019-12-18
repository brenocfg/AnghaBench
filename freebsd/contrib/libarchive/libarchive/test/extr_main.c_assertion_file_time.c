#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_11__ {long long tv_nsec; } ;
struct TYPE_10__ {long long tv_nsec; } ;
struct TYPE_9__ {long long tv_nsec; } ;
struct stat {long long st_atime; long long st_mtime; long long st_birthtime; TYPE_3__ st_mtimespec; TYPE_2__ st_birthtimespec; TYPE_1__ st_atimespec; } ;
struct TYPE_12__ {int QuadPart; scalar_t__ HighPart; scalar_t__ LowPart; } ;
typedef  TYPE_4__ ULARGE_INTEGER ;
struct TYPE_13__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_5__ FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EPOC_TIME ; 
 int /*<<< orphan*/  FILE_FLAG_BACKUP_SEMANTICS ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int GetFileTime (scalar_t__,TYPE_5__*,TYPE_5__*,TYPE_5__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char) ; 
 int lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
assertion_file_time(const char *file, int line,
    const char *pathname, long t, long nsec, char type, int recent)
{
	long long filet, filet_nsec;
	int r;

#if defined(_WIN32) && !defined(__CYGWIN__)
#define EPOC_TIME	(116444736000000000ULL)
	FILETIME fxtime, fbirthtime, fatime, fmtime;
	ULARGE_INTEGER wintm;
	HANDLE h;
	fxtime.dwLowDateTime = 0;
	fxtime.dwHighDateTime = 0;

	assertion_count(file, line);
	/* Note: FILE_FLAG_BACKUP_SEMANTICS applies to open
	 * a directory file. If not, CreateFile() will fail when
	 * the pathname is a directory. */
	h = CreateFile(pathname, FILE_READ_ATTRIBUTES, 0, NULL,
	    OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (h == INVALID_HANDLE_VALUE) {
		failure_start(file, line, "Can't access %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	r = GetFileTime(h, &fbirthtime, &fatime, &fmtime);
	switch (type) {
	case 'a': fxtime = fatime; break;
	case 'b': fxtime = fbirthtime; break;
	case 'm': fxtime = fmtime; break;
	}
	CloseHandle(h);
	if (r == 0) {
		failure_start(file, line, "Can't GetFileTime %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	wintm.LowPart = fxtime.dwLowDateTime;
	wintm.HighPart = fxtime.dwHighDateTime;
	filet = (wintm.QuadPart - EPOC_TIME) / 10000000;
	filet_nsec = ((wintm.QuadPart - EPOC_TIME) % 10000000) * 100;
	nsec = (nsec / 100) * 100; /* Round the request */
#else
	struct stat st;

	assertion_count(file, line);
	r = lstat(pathname, &st);
	if (r != 0) {
		failure_start(file, line, "Can't stat %s\n", pathname);
		failure_finish(NULL);
		return (0);
	}
	switch (type) {
	case 'a': filet = st.st_atime; break;
	case 'm': filet = st.st_mtime; break;
	case 'b': filet = 0; break;
	default: fprintf(stderr, "INTERNAL: Bad type %c for file time", type);
		exit(1);
	}
#if defined(__FreeBSD__)
	switch (type) {
	case 'a': filet_nsec = st.st_atimespec.tv_nsec; break;
	case 'b': filet = st.st_birthtime;
		/* FreeBSD filesystems that don't support birthtime
		 * (e.g., UFS1) always return -1 here. */
		if (filet == -1) {
			return (1);
		}
		filet_nsec = st.st_birthtimespec.tv_nsec; break;
	case 'm': filet_nsec = st.st_mtimespec.tv_nsec; break;
	default: fprintf(stderr, "INTERNAL: Bad type %c for file time", type);
		exit(1);
	}
	/* FreeBSD generally only stores to microsecond res, so round. */
	filet_nsec = (filet_nsec / 1000) * 1000;
	nsec = (nsec / 1000) * 1000;
#else
	filet_nsec = nsec = 0;	/* Generic POSIX only has whole seconds. */
	if (type == 'b') return (1); /* Generic POSIX doesn't have birthtime */
#if defined(__HAIKU__)
	if (type == 'a') return (1); /* Haiku doesn't have atime. */
#endif
#endif
#endif
	if (recent) {
		/* Check that requested time is up-to-date. */
		time_t now = time(NULL);
		if (filet < now - 10 || filet > now + 1) {
			failure_start(file, line,
			    "File %s has %ctime %lld, %lld seconds ago\n",
			    pathname, type, filet, now - filet);
			failure_finish(NULL);
			return (0);
		}
	} else if (filet != t || filet_nsec != nsec) {
		failure_start(file, line,
		    "File %s has %ctime %lld.%09lld, expected %lld.%09lld",
		    pathname, type, filet, filet_nsec, t, nsec);
		failure_finish(NULL);
		return (0);
	}
	return (1);
}