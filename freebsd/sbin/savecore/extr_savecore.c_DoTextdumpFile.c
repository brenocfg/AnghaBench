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
typedef  int off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nerr ; 
 int pread (int,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned long long) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
DoTextdumpFile(int fd, off_t dumpsize, off_t lasthd, char *buf,
    const char *device, const char *filename, FILE *fp)
{
	int nr, nw, wl;
	off_t dmpcnt, totsize;

	totsize = dumpsize;
	dmpcnt = 0;
	wl = 512;
	if ((dumpsize % wl) != 0) {
		logmsg(LOG_ERR, "textdump uneven multiple of 512 on %s",
		    device);
		nerr++;
		return (-1);
	}
	while (dumpsize > 0) {
		nr = pread(fd, buf, wl, lasthd - (totsize - dumpsize) - wl);
		if (nr != wl) {
			if (nr == 0)
				logmsg(LOG_WARNING,
				    "WARNING: EOF on dump device");
			else
				logmsg(LOG_ERR, "read error on %s: %m", device);
			nerr++;
			return (-1);
		}
		nw = fwrite(buf, 1, wl, fp);
		if (nw != wl) {
			logmsg(LOG_ERR,
			    "write error on %s file: %m", filename);
			logmsg(LOG_WARNING,
			    "WARNING: textdump may be incomplete");
			nerr++;
			return (-1);
		}
		if (verbose) {
			dmpcnt += wl;
			printf("%llu\r", (unsigned long long)dmpcnt);
			fflush(stdout);
		}
		dumpsize -= wl;
	}
	return (0);
}