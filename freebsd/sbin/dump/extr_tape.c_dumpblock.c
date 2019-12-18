#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ufs2_daddr_t ;
struct TYPE_6__ {TYPE_1__* req; } ;
struct TYPE_5__ {int c_tapea; } ;
struct TYPE_4__ {int dblk; int count; } ;

/* Variables and functions */
 int MIN (int,size_t) ; 
 int dev_bshift ; 
 int /*<<< orphan*/  flushtape () ; 
 int fsbtodb (int /*<<< orphan*/ ,int) ; 
 size_t ntrec ; 
 int /*<<< orphan*/  sblock ; 
 TYPE_3__* slp ; 
 TYPE_2__ spcl ; 
 int tp_bshift ; 
 size_t trecno ; 

void
dumpblock(ufs2_daddr_t blkno, int size)
{
	int avail, tpblks;
	ufs2_daddr_t dblkno;

	dblkno = fsbtodb(sblock, blkno);
	tpblks = size >> tp_bshift;
	while ((avail = MIN(tpblks, ntrec - trecno)) > 0) {
		slp->req[trecno].dblk = dblkno;
		slp->req[trecno].count = avail;
		trecno += avail;
		spcl.c_tapea += avail;
		if (trecno >= ntrec)
			flushtape();
		dblkno += avail << (tp_bshift - dev_bshift);
		tpblks -= avail;
	}
}