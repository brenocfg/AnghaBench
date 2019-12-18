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
struct TYPE_6__ {unsigned int last; int /*<<< orphan*/ ** array; scalar_t__ (* compare ) (void*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ isc_heap_t ;
typedef  scalar_t__ isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_HEAP (TYPE_1__*) ; 
 int /*<<< orphan*/  float_up (TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sink_down (TYPE_1__*,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (void*,int /*<<< orphan*/ *) ; 

void
isc_heap_delete(isc_heap_t *heap, unsigned int index) {
	void *elt;
	isc_boolean_t less;

	REQUIRE(VALID_HEAP(heap));
	REQUIRE(index >= 1 && index <= heap->last);

	if (index == heap->last) {
		heap->array[heap->last] = NULL;
		heap->last--;
	} else {
		elt = heap->array[heap->last];
		heap->array[heap->last] = NULL;
		heap->last--;

		less = heap->compare(elt, heap->array[index]);
		heap->array[index] = elt;
		if (less)
			float_up(heap, index, heap->array[index]);
		else
			sink_down(heap, index, heap->array[index]);
	}
}