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
typedef  size_t u_int ;
struct bcache {TYPE_1__* bcache_ctl; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_2__ {scalar_t__ bc_count; int /*<<< orphan*/  bc_blkno; } ;

/* Variables and functions */
 size_t BHASH (struct bcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcache_bcount ; 

__attribute__((used)) static void
bcache_insert(struct bcache *bc, daddr_t blkno)
{
    u_int	cand;
    
    cand = BHASH(bc, blkno);

    DPRINTF("insert blk %llu -> %u # %d", blkno, cand, bcache_bcount);
    bc->bcache_ctl[cand].bc_blkno = blkno;
    bc->bcache_ctl[cand].bc_count = bcache_bcount++;
}