#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t fts_nitems; TYPE_1__** fts_array; } ;
struct TYPE_9__ {struct TYPE_9__* fts_link; } ;
typedef  TYPE_1__ FTSENT ;
typedef  TYPE_2__ FTS ;

/* Variables and functions */
 int /*<<< orphan*/  fts_compar ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_1__** reallocf (TYPE_1__**,int) ; 

__attribute__((used)) static FTSENT *
fts_sort(FTS *sp, FTSENT *head, size_t nitems)
{
	FTSENT **ap, *p;

	/*
	 * Construct an array of pointers to the structures and call qsort(3).
	 * Reassemble the array in the order returned by qsort.  If unable to
	 * sort for memory reasons, return the directory entries in their
	 * current order.  Allocate enough space for the current needs plus
	 * 40 so don't realloc one entry at a time.
	 */
	if (nitems > sp->fts_nitems) {
		sp->fts_nitems = nitems + 40;
		if ((sp->fts_array = reallocf(sp->fts_array,
		    sp->fts_nitems * sizeof(FTSENT *))) == NULL) {
			sp->fts_nitems = 0;
			return (head);
		}
	}
	for (ap = sp->fts_array, p = head; p; p = p->fts_link)
		*ap++ = p;
	qsort(sp->fts_array, nitems, sizeof(FTSENT *), fts_compar);
	for (head = *(ap = sp->fts_array); --nitems; ++ap)
		ap[0]->fts_link = ap[1];
	ap[0]->fts_link = NULL;
	return (head);
}