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
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; } ;
struct TYPE_4__ {int BSIZE; int BSHIFT; int nbufs; TYPE_2__ bufhead; } ;
typedef  TYPE_1__ HTAB ;
typedef  TYPE_2__ BUFHEAD ;

/* Variables and functions */
 int MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_BUFFERS ; 

void
__buf_init(HTAB *hashp, int nbytes)
{
	BUFHEAD *bfp;
	int npages;

	bfp = &(hashp->bufhead);
	npages = (nbytes + hashp->BSIZE - 1) >> hashp->BSHIFT;
	npages = MAX(npages, MIN_BUFFERS);

	hashp->nbufs = npages;
	bfp->next = bfp;
	bfp->prev = bfp;
	/*
	 * This space is calloc'd so these are already null.
	 *
	 * bfp->ovfl = NULL;
	 * bfp->flags = 0;
	 * bfp->page = NULL;
	 * bfp->addr = 0;
	 */
}