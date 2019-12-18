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
typedef  int ufs2_daddr_t ;
typedef  int off_t ;
typedef  int intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIT ; 
 scalar_t__ bkgrdflag ; 
 int dev_bsize ; 
 int /*<<< orphan*/  diskreads ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pfatal (char*,long) ; 
 int pread (int,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ resolved ; 
 int /*<<< orphan*/  rwerror (char*,int) ; 
 int secsize ; 
 int /*<<< orphan*/  slowio_end () ; 
 int /*<<< orphan*/  slowio_start () ; 
 scalar_t__ surrender ; 
 int /*<<< orphan*/  totalreads ; 

int
blread(int fd, char *buf, ufs2_daddr_t blk, long size)
{
	char *cp;
	int i, errs;
	off_t offset;

	offset = blk;
	offset *= dev_bsize;
	if (bkgrdflag)
		slowio_start();
	totalreads++;
	diskreads++;
	if (pread(fd, buf, (int)size, offset) == size) {
		if (bkgrdflag)
			slowio_end();
		return (0);
	}

	/*
	 * This is handled specially here instead of in rwerror because
	 * rwerror is used for all sorts of errors, not just true read/write
	 * errors.  It should be refactored and fixed.
	 */
	if (surrender) {
		pfatal("CANNOT READ_BLK: %ld", (long)blk);
		errx(EEXIT, "ABORTING DUE TO READ ERRORS");
	} else
		rwerror("READ BLK", blk);

	errs = 0;
	memset(buf, 0, (size_t)size);
	printf("THE FOLLOWING DISK SECTORS COULD NOT BE READ:");
	for (cp = buf, i = 0; i < size; i += secsize, cp += secsize) {
		if (pread(fd, cp, (int)secsize, offset + i) != secsize) {
			if (secsize != dev_bsize && dev_bsize != 1)
				printf(" %jd (%jd),",
				    (intmax_t)(blk * dev_bsize + i) / secsize,
				    (intmax_t)blk + i / dev_bsize);
			else
				printf(" %jd,", (intmax_t)blk + i / dev_bsize);
			errs++;
		}
	}
	printf("\n");
	if (errs)
		resolved = 0;
	return (errs);
}