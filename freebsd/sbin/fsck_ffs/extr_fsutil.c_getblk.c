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
typedef  scalar_t__ ufs2_daddr_t ;
struct timespec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  b_buf; } ;
struct bufarea {scalar_t__ b_bno; size_t b_type; long b_size; TYPE_1__ b_un; int /*<<< orphan*/  b_errs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME_PRECISE ; 
 int /*<<< orphan*/  blread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,long) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ,struct bufarea*) ; 
 scalar_t__ fsbtodb (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fsreadfd ; 
 int /*<<< orphan*/  fswritefd ; 
 int /*<<< orphan*/ * readcnt ; 
 int /*<<< orphan*/ * readtime ; 
 int /*<<< orphan*/  sblock ; 
 int /*<<< orphan*/  timespecadd (int /*<<< orphan*/ *,struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  totalreads ; 

void
getblk(struct bufarea *bp, ufs2_daddr_t blk, long size)
{
	ufs2_daddr_t dblk;
	struct timespec start, finish;

	dblk = fsbtodb(&sblock, blk);
	if (bp->b_bno == dblk) {
		totalreads++;
	} else {
		flush(fswritefd, bp);
		if (debug) {
			readcnt[bp->b_type]++;
			clock_gettime(CLOCK_REALTIME_PRECISE, &start);
		}
		bp->b_errs = blread(fsreadfd, bp->b_un.b_buf, dblk, size);
		if (debug) {
			clock_gettime(CLOCK_REALTIME_PRECISE, &finish);
			timespecsub(&finish, &start, &finish);
			timespecadd(&readtime[bp->b_type], &finish,
			    &readtime[bp->b_type]);
		}
		bp->b_bno = dblk;
		bp->b_size = size;
	}
}