#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct buf {int b_blkno; long long b_bcount; int /*<<< orphan*/  b_data; TYPE_1__* b_fs; } ;
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int sectorsize; int /*<<< orphan*/  fd; scalar_t__ offset; } ;
typedef  TYPE_1__ fsinfo_t ;

/* Variables and functions */
 int DEBUG_BUF_BWRITE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int debug ; 
 int errno ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,long long,long long,long long) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long) ; 

int
bwrite(struct buf *bp)
{
	off_t	offset;
	ssize_t	rv;
	fsinfo_t *fs = bp->b_fs;

	assert (bp != NULL);
	offset = bp->b_blkno * fs->sectorsize + fs->offset;
	if (debug & DEBUG_BUF_BWRITE)
		printf("bwrite: blkno %lld offset %lld bcount %ld\n",
		    (long long)bp->b_blkno, (long long) offset,
		    bp->b_bcount);
	if (lseek(bp->b_fs->fd, offset, SEEK_SET) == -1)
		return (errno);
	rv = write(bp->b_fs->fd, bp->b_data, bp->b_bcount);
	if (debug & DEBUG_BUF_BWRITE)
		printf("bwrite: write %ld (offset %lld) returned %lld\n",
		    bp->b_bcount, (long long)offset, (long long)rv);
	if (rv == bp->b_bcount)
		return (0);
	else if (rv == -1)		/* write error */
		return (errno);
	else				/* short write ? */
		return (EAGAIN);
}