#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int last; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ isc_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_HEAP (TYPE_1__*) ; 
 int /*<<< orphan*/  sink_down (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 

void
isc_heap_decreased(isc_heap_t *heap, unsigned int index) {
	REQUIRE(VALID_HEAP(heap));
	REQUIRE(index >= 1 && index <= heap->last);

	sink_down(heap, index, heap->array[index]);
}