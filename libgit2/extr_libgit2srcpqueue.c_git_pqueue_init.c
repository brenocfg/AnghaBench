#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_vector_cmp ;
struct TYPE_4__ {int flags; size_t _alloc_size; } ;
typedef  TYPE_1__ git_pqueue ;

/* Variables and functions */
 int GIT_PQUEUE_FIXED_SIZE ; 
 int git_vector_init (TYPE_1__*,size_t,int /*<<< orphan*/ ) ; 

int git_pqueue_init(
	git_pqueue *pq,
	uint32_t flags,
	size_t init_size,
	git_vector_cmp cmp)
{
	int error = git_vector_init(pq, init_size, cmp);

	if (!error) {
		/* mix in our flags */
		pq->flags |= flags;

		/* if fixed size heap, pretend vector is exactly init_size elements */
		if ((flags & GIT_PQUEUE_FIXED_SIZE) && init_size > 0)
			pq->_alloc_size = init_size;
	}

	return error;
}