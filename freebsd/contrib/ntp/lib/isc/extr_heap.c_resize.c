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
struct TYPE_4__ {size_t size; size_t size_increment; void** array; int /*<<< orphan*/  mctx; } ;
typedef  TYPE_1__ isc_heap_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_HEAP (TYPE_1__*) ; 
 void** isc_mem_get (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 

__attribute__((used)) static isc_boolean_t
resize(isc_heap_t *heap) {
	void **new_array;
	size_t new_size;

	REQUIRE(VALID_HEAP(heap));

	new_size = heap->size + heap->size_increment;
	new_array = isc_mem_get(heap->mctx, new_size * sizeof(void *));
	if (new_array == NULL)
		return (ISC_FALSE);
	if (heap->array != NULL) {
		memcpy(new_array, heap->array, heap->size * sizeof(void *));
		isc_mem_put(heap->mctx, heap->array,
			    heap->size * sizeof(void *));
	}
	heap->size = new_size;
	heap->array = new_array;

	return (ISC_TRUE);
}