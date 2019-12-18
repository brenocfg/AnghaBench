#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  allocator; TYPE_3__* freelist; int /*<<< orphan*/  num_alloc; } ;
typedef  TYPE_2__ serf_bucket_alloc_t ;
struct TYPE_5__ {int /*<<< orphan*/  memnode; TYPE_3__* next; } ;
struct TYPE_7__ {scalar_t__ size; TYPE_1__ u; } ;
typedef  TYPE_3__ node_header_t ;

/* Variables and functions */
 char* SIZEOF_NODE_HEADER_T ; 
 scalar_t__ STANDARD_NODE_SIZE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  apr_allocator_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void serf_bucket_mem_free(
    serf_bucket_alloc_t *allocator,
    void *block)
{
    node_header_t *node;

    --allocator->num_alloc;

    node = (node_header_t *)((char *)block - SIZEOF_NODE_HEADER_T);

    if (node->size == STANDARD_NODE_SIZE) {
        /* put the node onto our free list */
        node->u.next = allocator->freelist;
        allocator->freelist = node;

#ifdef DEBUG_DOUBLE_FREE
        /* note that this thing was freed. */
        node->size = 0;
    }
    else if (node->size == 0) {
        /* damn thing was freed already. */
        abort();
#endif
    }
    else {
#ifdef DEBUG_DOUBLE_FREE
        /* note that this thing was freed. */
        node->size = 0;
#endif

        /* now free it */
        apr_allocator_free(allocator->allocator, node->u.memnode);
    }
}