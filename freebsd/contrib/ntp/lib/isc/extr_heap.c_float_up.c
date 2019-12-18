#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void** array; int /*<<< orphan*/  (* index ) (void*,unsigned int) ;scalar_t__ (* compare ) (void*,void*) ;} ;
typedef  TYPE_1__ isc_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEAPCONDITION (unsigned int) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 unsigned int heap_parent (unsigned int) ; 
 scalar_t__ stub1 (void*,void*) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (void*,unsigned int) ; 

__attribute__((used)) static void
float_up(isc_heap_t *heap, unsigned int i, void *elt) {
	unsigned int p;

	for (p = heap_parent(i) ;
	     i > 1 && heap->compare(elt, heap->array[p]) ;
	     i = p, p = heap_parent(i)) {
		heap->array[i] = heap->array[p];
		if (heap->index != NULL)
			(heap->index)(heap->array[i], i);
	}
	heap->array[i] = elt;
	if (heap->index != NULL)
		(heap->index)(heap->array[i], i);

	INSIST(HEAPCONDITION(i));
}