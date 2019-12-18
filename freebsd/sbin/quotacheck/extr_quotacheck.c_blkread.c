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
typedef  scalar_t__ ufs2_daddr_t ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int dev_bsize ; 
 int /*<<< orphan*/  errx (int,char*,long) ; 
 int /*<<< orphan*/  fi ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 long read (int /*<<< orphan*/ ,char*,long) ; 

void
blkread(ufs2_daddr_t bno, char *buf, long cnt)
{

	if (lseek(fi, (off_t)bno * dev_bsize, SEEK_SET) < 0 ||
	    read(fi, buf, cnt) != cnt)
		errx(1, "blkread failed on block %ld", (long)bno);
}