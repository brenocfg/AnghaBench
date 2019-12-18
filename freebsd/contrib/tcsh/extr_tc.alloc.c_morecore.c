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
union overhead {union overhead* ov_next; } ;
typedef  scalar_t__ caddr_t ;
typedef  int U_long ;

/* Variables and functions */
 int ROUNDUP ; 
 char* membot ; 
 char* memtop ; 
 union overhead** nextf ; 
 char* sbrk (int) ; 

__attribute__((used)) static void
morecore(int bucket)
{
    union overhead *op;
    int rnu;		/* 2^rnu bytes will be requested */
    int nblks;		/* become nblks blocks of the desired size */
    int siz;

    if (nextf[bucket])
	return;
    /*
     * Insure memory is allocated on a page boundary.  Should make getpageize
     * call?
     */
    op = (union overhead *) sbrk(0);
    memtop = (char *) op;
    if (membot == NULL)
	membot = memtop;
    if ((long) op & 0x3ff) {
	memtop = sbrk((int) (1024 - ((long) op & 0x3ff)));
	memtop += (long) (1024 - ((long) op & 0x3ff));
    }

    /* take 2k unless the block is bigger than that */
    rnu = (bucket <= 8) ? 11 : bucket + 3;
    nblks = 1 << (rnu - (bucket + 3));	/* how many blocks to get */
    memtop = sbrk(1 << rnu);	/* PWP */
    op = (union overhead *) memtop;
    /* no more room! */
    if ((long) op == -1)
	return;
    memtop += (long) (1 << rnu);
    /*
     * Round up to minimum allocation size boundary and deduct from block count
     * to reflect.
     */
    if (((U_long) op) & ROUNDUP) {
	op = (union overhead *) (((U_long) op + (ROUNDUP + 1)) & ~ROUNDUP);
	nblks--;
    }
    /*
     * Add new memory allocated to that on free list for this hash bucket.
     */
    nextf[bucket] = op;
    siz = 1 << (bucket + 3);
    while (--nblks > 0) {
	op->ov_next = (union overhead *) (((caddr_t) op) + siz);
	op = (union overhead *) (((caddr_t) op) + siz);
    }
    op->ov_next = NULL;
}