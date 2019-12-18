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
struct TYPE_3__ {struct st_h2o_mem_recycle_chunk_t* _link; int /*<<< orphan*/  cnt; } ;
typedef  TYPE_1__ h2o_mem_recycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_h2o_mem_recycle_chunk_t*) ; 

void h2o_mem_clear_recycle(h2o_mem_recycle_t *allocator)
{
    struct st_h2o_mem_recycle_chunk_t *chunk;

    while (allocator->cnt-- > 0) {
        chunk = allocator->_link;
        allocator->_link = allocator->_link->next;
        free(chunk);
    }
}