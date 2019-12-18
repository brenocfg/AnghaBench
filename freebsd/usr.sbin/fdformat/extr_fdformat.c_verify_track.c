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

/* Variables and functions */
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int FDOPT_NORETRY ; 
 int /*<<< orphan*/  FD_GOPTS ; 
 int /*<<< orphan*/  FD_SOPTS ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ lseek (int,long,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
verify_track(int fd, int track, int tracksize)
{
	static char *buf;
	static int bufsz;
	int fdopts = -1, ofdopts, rv = 0;

	if (ioctl(fd, FD_GOPTS, &fdopts) < 0)
		warn("warning: ioctl(FD_GOPTS)");
	else {
		ofdopts = fdopts;
		fdopts |= FDOPT_NORETRY;
		(void)ioctl(fd, FD_SOPTS, &fdopts);
	}

	if (bufsz < tracksize)
		buf = realloc(buf, bufsz = tracksize);
	if (buf == NULL)
		errx(EX_UNAVAILABLE, "out of memory");
	if (lseek (fd, (long) track * tracksize, 0) < 0)
		rv = -1;
	/* try twice reading it, without using the normal retrier */
	else if (read (fd, buf, tracksize) != tracksize
		 && read (fd, buf, tracksize) != tracksize)
		rv = -1;
	if (fdopts != -1)
		(void)ioctl(fd, FD_SOPTS, &ofdopts);
	return (rv);
}