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
struct bufobj {int dummy; } ;
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BO_RLOCK (struct bufobj*) ; 
 int /*<<< orphan*/  BO_RUNLOCK (struct bufobj*) ; 
 struct buf* gbincore (struct bufobj*,int /*<<< orphan*/ ) ; 

struct buf *
incore(struct bufobj *bo, daddr_t blkno)
{
	struct buf *bp;

	BO_RLOCK(bo);
	bp = gbincore(bo, blkno);
	BO_RUNLOCK(bo);
	return (bp);
}