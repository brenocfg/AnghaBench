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
typedef  long ufs2_daddr_t ;
typedef  long off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIT ; 
 long MIN (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  ZEROBUFSIZE ; 
 char* calloc (int /*<<< orphan*/ ,int) ; 
 long dev_bsize ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ lseek (int,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwerror (char*,long) ; 
 long write (int,char*,long) ; 

void
blzero(int fd, ufs2_daddr_t blk, long size)
{
	static char *zero;
	off_t offset, len;

	if (fd < 0)
		return;
	if (zero == NULL) {
		zero = calloc(ZEROBUFSIZE, 1);
		if (zero == NULL)
			errx(EEXIT, "cannot allocate buffer pool");
	}
	offset = blk * dev_bsize;
	if (lseek(fd, offset, 0) < 0)
		rwerror("SEEK BLK", blk);
	while (size > 0) {
		len = MIN(ZEROBUFSIZE, size);
		if (write(fd, zero, len) != len)
			rwerror("WRITE BLK", blk);
		blk += len / dev_bsize;
		size -= len;
	}
}