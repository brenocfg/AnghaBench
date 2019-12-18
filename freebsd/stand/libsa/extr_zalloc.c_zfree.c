#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_5__ {uintptr_t mr_Bytes; struct TYPE_5__* mr_Next; } ;
struct TYPE_4__ {uintptr_t mp_Used; TYPE_2__* mp_First; scalar_t__ mp_End; scalar_t__ mp_Base; } ;
typedef  TYPE_1__ MemPool ;
typedef  TYPE_2__ MemNode ;

/* Variables and functions */
 uintptr_t MEMNODE_SIZE_MASK ; 
 int /*<<< orphan*/  panic (char*,void*,int /*<<< orphan*/ ) ; 

void
zfree(MemPool *mp, void *ptr, uintptr_t bytes)
{
	MemNode **pmn;
	MemNode *mn;

	/*
	 * align according to pool object size (can be 0).  This is
	 * inclusive of the MEMNODE_SIZE_MASK minimum alignment.
	 */
	bytes = (bytes + MEMNODE_SIZE_MASK) & ~MEMNODE_SIZE_MASK;

	if (bytes == 0)
		return;

	/*
	 * panic if illegal pointer
	 */

	if ((char *)ptr < (char *)mp->mp_Base ||
	    (char *)ptr + bytes > (char *)mp->mp_End ||
	    ((uintptr_t)ptr & MEMNODE_SIZE_MASK) != 0)
		panic("zfree(%p,%ju): wild pointer", ptr, (uintmax_t)bytes);

	/*
	 * free the segment
	 */
	mp->mp_Used -= bytes;

	for (pmn = &mp->mp_First; (mn = *pmn) != NULL; pmn = &mn->mr_Next) {
		/*
		 * If area between last node and current node
		 *  - check range
		 *  - check merge with next area
		 *  - check merge with previous area
		 */
		if ((char *)ptr <= (char *)mn) {
			/*
			 * range check
			 */
			if ((char *)ptr + bytes > (char *)mn) {
				panic("zfree(%p,%ju): corrupt memlist1", ptr,
				    (uintmax_t)bytes);
			}

			/*
			 * merge against next area or create independant area
			 */

			if ((char *)ptr + bytes == (char *)mn) {
				((MemNode *)ptr)->mr_Next = mn->mr_Next;
				((MemNode *)ptr)->mr_Bytes =
				    bytes + mn->mr_Bytes;
			} else {
				((MemNode *)ptr)->mr_Next = mn;
				((MemNode *)ptr)->mr_Bytes = bytes;
			}
			*pmn = mn = (MemNode *)ptr;

			/*
			 * merge against previous area (if there is a previous
			 * area).
			 */

			if (pmn != &mp->mp_First) {
				if ((char *)pmn + ((MemNode*)pmn)->mr_Bytes ==
				    (char *)ptr) {
					((MemNode *)pmn)->mr_Next = mn->mr_Next;
					((MemNode *)pmn)->mr_Bytes +=
					    mn->mr_Bytes;
					mn = (MemNode *)pmn;
				}
			}
			return;
		}
		if ((char *)ptr < (char *)mn + mn->mr_Bytes) {
			panic("zfree(%p,%ju): corrupt memlist2", ptr,
			    (uintmax_t)bytes);
		}
	}
	/*
	 * We are beyond the last MemNode, append new MemNode.  Merge against
	 * previous area if possible.
	 */
	if (pmn == &mp->mp_First ||
	    (char *)pmn + ((MemNode *)pmn)->mr_Bytes != (char *)ptr) {
		((MemNode *)ptr)->mr_Next = NULL;
		((MemNode *)ptr)->mr_Bytes = bytes;
		*pmn = (MemNode *)ptr;
		mn = (MemNode *)ptr;
	} else {
		((MemNode *)pmn)->mr_Bytes += bytes;
		mn = (MemNode *)pmn;
	}
}