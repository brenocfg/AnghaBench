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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {int last; unsigned int size; } ;
typedef  TYPE_1__ isc_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMEMORY ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  VALID_HEAP (TYPE_1__*) ; 
 int /*<<< orphan*/  float_up (TYPE_1__*,unsigned int,void*) ; 
 int /*<<< orphan*/  resize (TYPE_1__*) ; 

isc_result_t
isc_heap_insert(isc_heap_t *heap, void *elt) {
	unsigned int new_last;

	REQUIRE(VALID_HEAP(heap));

	new_last = heap->last + 1;
	RUNTIME_CHECK(new_last > 0); /* overflow check */
	if (new_last >= heap->size && !resize(heap))
		return (ISC_R_NOMEMORY);
	heap->last = new_last;

	float_up(heap, new_last, elt);

	return (ISC_R_SUCCESS);
}