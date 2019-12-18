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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
struct TYPE_3__ {int /*<<< orphan*/ * buffer_p; int /*<<< orphan*/  capacity; scalar_t__ item_count; } ;
typedef  TYPE_1__ ecma_collection_t ;

/* Variables and functions */
 int ECMA_COLLECTION_ALLOCATED_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECMA_COLLECTION_INITIAL_CAPACITY ; 
 scalar_t__ jmem_heap_alloc_block (int const) ; 

ecma_collection_t *
ecma_new_collection (void)
{
  ecma_collection_t *collection_p;
  collection_p = (ecma_collection_t *) jmem_heap_alloc_block (sizeof (ecma_collection_t));

  collection_p->item_count = 0;
  collection_p->capacity = ECMA_COLLECTION_INITIAL_CAPACITY;
  const uint32_t size = ECMA_COLLECTION_ALLOCATED_SIZE (ECMA_COLLECTION_INITIAL_CAPACITY);
  collection_p->buffer_p = (ecma_value_t *) jmem_heap_alloc_block (size);

  return collection_p;
}