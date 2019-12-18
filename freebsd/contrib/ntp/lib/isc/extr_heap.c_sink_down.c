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
struct TYPE_3__ {unsigned int last; void** array; int /*<<< orphan*/  (* index ) (void*,unsigned int) ;scalar_t__ (* compare ) (void*,void*) ;} ;
typedef  TYPE_1__ isc_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEAPCONDITION (unsigned int) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 unsigned int heap_left (unsigned int) ; 
 scalar_t__ stub1 (void*,void*) ; 
 scalar_t__ stub2 (void*,void*) ; 
 int /*<<< orphan*/  stub3 (void*,unsigned int) ; 
 int /*<<< orphan*/  stub4 (void*,unsigned int) ; 

__attribute__((used)) static void
sink_down(isc_heap_t *heap, unsigned int i, void *elt) {
	unsigned int j, size, half_size;
	size = heap->last;
	half_size = size / 2;
	while (i <= half_size) {
		/* Find the smallest of the (at most) two children. */
		j = heap_left(i);
		if (j < size && heap->compare(heap->array[j+1],
					      heap->array[j]))
			j++;
		if (heap->compare(elt, heap->array[j]))
			break;
		heap->array[i] = heap->array[j];
		if (heap->index != NULL)
			(heap->index)(heap->array[i], i);
		i = j;
	}
	heap->array[i] = elt;
	if (heap->index != NULL)
		(heap->index)(heap->array[i], i);

	INSIST(HEAPCONDITION(i));
}