#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {scalar_t__ (* avl_compar ) (void*,void*) ;} ;
typedef  TYPE_1__ avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* AVL_NEXT (TYPE_1__*,void*) ; 
 void* AVL_PREV (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  AVL_REINSERT (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ stub1 (void*,void*) ; 
 scalar_t__ stub2 (void*,void*) ; 

boolean_t
avl_update_gt(avl_tree_t *t, void *obj)
{
	void *neighbor;

	ASSERT(((neighbor = AVL_PREV(t, obj)) == NULL) ||
	    (t->avl_compar(obj, neighbor) >= 0));

	neighbor = AVL_NEXT(t, obj);
	if ((neighbor != NULL) && (t->avl_compar(obj, neighbor) > 0)) {
		AVL_REINSERT(t, obj);
		return (B_TRUE);
	}

	return (B_FALSE);
}