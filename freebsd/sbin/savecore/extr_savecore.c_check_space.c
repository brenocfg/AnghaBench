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
struct statfs {int f_bsize; scalar_t__ f_bfree; scalar_t__ f_bavail; } ;
typedef  int off_t ;
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fstatfs (int,struct statfs*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ saved_dump_size (int,int) ; 
 int strtoll (char*,char**,int) ; 
 int /*<<< orphan*/ * xfopenat (int,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
check_space(const char *savedir, int savedirfd, off_t dumpsize, int bounds)
{
	char buf[100];
	struct statfs fsbuf;
	FILE *fp;
	off_t available, minfree, spacefree, totfree, needed;

	if (fstatfs(savedirfd, &fsbuf) < 0) {
		logmsg(LOG_ERR, "%s: %m", savedir);
		exit(1);
	}
	spacefree = ((off_t) fsbuf.f_bavail * fsbuf.f_bsize) / 1024;
	totfree = ((off_t) fsbuf.f_bfree * fsbuf.f_bsize) / 1024;

	if ((fp = xfopenat(savedirfd, "minfree", O_RDONLY, "r")) == NULL)
		minfree = 0;
	else {
		if (fgets(buf, sizeof(buf), fp) == NULL)
			minfree = 0;
		else {
			char *endp;

			errno = 0;
			minfree = strtoll(buf, &endp, 10);
			if (minfree == 0 && errno != 0)
				minfree = -1;
			else {
				while (*endp != '\0' && isspace(*endp))
					endp++;
				if (*endp != '\0' || minfree < 0)
					minfree = -1;
			}
			if (minfree < 0)
				logmsg(LOG_WARNING,
				    "`minfree` didn't contain a valid size "
				    "(`%s`). Defaulting to 0", buf);
		}
		(void)fclose(fp);
	}

	available = minfree > 0 ? spacefree - minfree : totfree;
	needed = dumpsize / 1024 + 2;	/* 2 for info file */
	needed -= saved_dump_size(savedirfd, bounds);
	if (available < needed) {
		logmsg(LOG_WARNING,
		    "no dump: not enough free space on device (need at least "
		    "%jdkB for dump; %jdkB available; %jdkB reserved)",
		    (intmax_t)needed,
		    (intmax_t)available + minfree,
		    (intmax_t)minfree);
		return (0);
	}
	if (spacefree - needed < 0)
		logmsg(LOG_WARNING,
		    "dump performed, but free space threshold crossed");
	return (1);
}