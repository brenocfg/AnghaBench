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
struct TYPE_5__ {int size; int /*<<< orphan*/  mctx; scalar_t__ magic; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ isc_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_HEAP (TYPE_1__*) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isc_mem_putanddetach (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

void
isc_heap_destroy(isc_heap_t **heapp) {
	isc_heap_t *heap;

	REQUIRE(heapp != NULL);
	heap = *heapp;
	REQUIRE(VALID_HEAP(heap));

	if (heap->array != NULL)
		isc_mem_put(heap->mctx, heap->array,
			    heap->size * sizeof(void *));
	heap->magic = 0;
	isc_mem_putanddetach(&heap->mctx, heap, sizeof(*heap));

	*heapp = NULL;
}