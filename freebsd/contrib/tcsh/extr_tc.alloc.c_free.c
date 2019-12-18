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
union overhead {scalar_t__ ov_magic; int ov_index; union overhead* ov_next; scalar_t__ ov_size; } ;
typedef  int /*<<< orphan*/ * ptr_t ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ U_int ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/  CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MAGIC ; 
 scalar_t__ MEMALIGN (int) ; 
 int NBUCKETS ; 
 scalar_t__ RMAGIC ; 
 scalar_t__ RSLOP ; 
 scalar_t__ dont_free ; 
 scalar_t__ membot ; 
 scalar_t__ memtop ; 
 union overhead** nextf ; 
 int /*<<< orphan*/ * nmalloc ; 

void
free(ptr_t cp)
{
#ifndef lint
    int size;
    union overhead *op;

    /*
     * the don't free flag is there so that we avoid os bugs in routines
     * that free invalid pointers!
     */
    if (cp == NULL || dont_free)
	return;
    CHECK(!memtop || !membot,
	  CGETS(19, 2, "free(%p) called before any allocations."), cp);
    CHECK(cp > (ptr_t) memtop,
	  CGETS(19, 3, "free(%p) above top of memory."), cp);
    CHECK(cp < (ptr_t) membot,
	  CGETS(19, 4, "free(%p) below bottom of memory."), cp);
    op = (union overhead *) (((caddr_t) cp) - MEMALIGN(sizeof(union overhead)));
    CHECK(op->ov_magic != MAGIC,
	  CGETS(19, 5, "free(%p) bad block."), cp);

#ifdef RCHECK
    if (op->ov_index <= 13)
	CHECK(*(U_int *) ((caddr_t) op + op->ov_size + 1 - RSLOP) != RMAGIC,
	      CGETS(19, 6, "free(%p) bad range check."), cp);
#endif
    CHECK(op->ov_index >= NBUCKETS,
	  CGETS(19, 7, "free(%p) bad block index."), cp);
    size = op->ov_index;
    op->ov_next = nextf[size];
    nextf[size] = op;

    nmalloc[size]--;

#else
    if (cp == NULL)
	return;
#endif
}