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
typedef  int ssize_t ;
typedef  int off_t ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int dev_bsize ; 
 int fsmodified ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int pwrite (int,char*,int,int) ; 
 scalar_t__ resolved ; 
 int /*<<< orphan*/  rwerror (char*,int) ; 

void
blwrite(int fd, char *buf, ufs2_daddr_t blk, ssize_t size)
{
	int i;
	char *cp;
	off_t offset;

	if (fd < 0)
		return;
	offset = blk;
	offset *= dev_bsize;
	if (pwrite(fd, buf, size, offset) == size) {
		fsmodified = 1;
		return;
	}
	resolved = 0;
	rwerror("WRITE BLK", blk);
	printf("THE FOLLOWING SECTORS COULD NOT BE WRITTEN:");
	for (cp = buf, i = 0; i < size; i += dev_bsize, cp += dev_bsize)
		if (pwrite(fd, cp, dev_bsize, offset + i) != dev_bsize)
			printf(" %jd,", (intmax_t)blk + i / dev_bsize);
	printf("\n");
	return;
}