#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ flags; scalar_t__ addr; int /*<<< orphan*/ * ovfl; } ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ BUFHEAD ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_REMOVE (TYPE_1__*) ; 
 int /*<<< orphan*/  LRU_INSERT (TYPE_1__*) ; 

void
__reclaim_buf(HTAB *hashp, BUFHEAD *bp)
{
	bp->ovfl = NULL;
	bp->addr = 0;
	bp->flags = 0;
	BUF_REMOVE(bp);
	LRU_INSERT(bp);
}