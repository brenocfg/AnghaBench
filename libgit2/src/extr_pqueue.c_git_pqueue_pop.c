#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void** contents; scalar_t__ _cmp; } ;
typedef  TYPE_1__ git_pqueue ;

/* Variables and functions */
 void* git_pqueue_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int git_pqueue_size (TYPE_1__*) ; 
 void* git_vector_last (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  pqueue_down (TYPE_1__*,int /*<<< orphan*/ ) ; 

void *git_pqueue_pop(git_pqueue *pq)
{
	void *rval;

	if (!pq->_cmp) {
		rval = git_vector_last(pq);
	} else {
		rval = git_pqueue_get(pq, 0);
	}

	if (git_pqueue_size(pq) > 1 && pq->_cmp) {
		/* move last item to top of heap, shrink, and push item down */
		pq->contents[0] = git_vector_last(pq);
		git_vector_pop(pq);
		pqueue_down(pq, 0);
	} else {
		/* all we need to do is shrink the heap in this case */
		git_vector_pop(pq);
	}

	return rval;
}