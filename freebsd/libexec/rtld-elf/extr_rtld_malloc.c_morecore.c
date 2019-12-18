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

/* Variables and functions */
 int FIRST_BUCKET_SIZE ; 
 scalar_t__ NPOOLPAGES ; 
 scalar_t__ morepages (scalar_t__) ; 
 union overhead** nextf ; 
 int pagepool_end ; 
 int pagepool_start ; 
 int pagesz ; 

__attribute__((used)) static void
morecore(int bucket)
{
	union overhead *op;
	int sz;		/* size of desired block */
  	int amt;			/* amount to allocate */
  	int nblks;			/* how many blocks we get */

	sz = FIRST_BUCKET_SIZE << bucket;
	if (sz < pagesz) {
		amt = pagesz;
  		nblks = amt / sz;
	} else {
		amt = sz;
		nblks = 1;
	}
	if (amt > pagepool_end - pagepool_start)
		if (morepages(amt/pagesz + NPOOLPAGES) == 0)
			return;
	op = (union overhead *)pagepool_start;
	pagepool_start += amt;

	/*
	 * Add new memory allocated to that on
	 * free list for this hash bucket.
	 */
  	nextf[bucket] = op;
  	while (--nblks > 0) {
		op->ov_next = (union overhead *)((caddr_t)op + sz);
		op = (union overhead *)((caddr_t)op + sz);
  	}
}