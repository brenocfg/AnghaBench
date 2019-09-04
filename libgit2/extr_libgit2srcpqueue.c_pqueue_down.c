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
struct TYPE_4__ {scalar_t__ (* _cmp ) (void*,void*) ;void** contents; } ;
typedef  TYPE_1__ git_pqueue ;

/* Variables and functions */
 size_t PQUEUE_LCHILD_OF (size_t) ; 
 void* git_vector_get (TYPE_1__*,size_t) ; 
 scalar_t__ stub1 (void*,void*) ; 
 scalar_t__ stub2 (void*,void*) ; 

__attribute__((used)) static void pqueue_down(git_pqueue *pq, size_t el)
{
	void *parent = git_vector_get(pq, el), *kid, *rkid;

	while (1) {
		size_t kid_el = PQUEUE_LCHILD_OF(el);

		if ((kid = git_vector_get(pq, kid_el)) == NULL)
			break;

		if ((rkid = git_vector_get(pq, kid_el + 1)) != NULL &&
			pq->_cmp(kid, rkid) > 0) {
			kid    = rkid;
			kid_el += 1;
		}

		if (pq->_cmp(parent, kid) <= 0)
			break;

		pq->contents[el] = kid;
		el = kid_el;
	}

	pq->contents[el] = parent;
}