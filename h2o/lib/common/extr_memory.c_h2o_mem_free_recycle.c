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
struct st_h2o_mem_recycle_chunk_t {struct st_h2o_mem_recycle_chunk_t* next; } ;
struct TYPE_3__ {scalar_t__ cnt; scalar_t__ max; struct st_h2o_mem_recycle_chunk_t* _link; } ;
typedef  TYPE_1__ h2o_mem_recycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 

void h2o_mem_free_recycle(h2o_mem_recycle_t *allocator, void *p)
{
    struct st_h2o_mem_recycle_chunk_t *chunk;
    if (allocator->cnt == allocator->max) {
        free(p);
        return;
    }
    /* register the pointer to the pool */
    chunk = p;
    chunk->next = allocator->_link;
    allocator->_link = chunk;
    ++allocator->cnt;
}