#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *serf_bucket_mem_calloc(
    serf_bucket_alloc_t *allocator,
    apr_size_t size)
{
    void *mem;
    mem = serf_bucket_mem_alloc(allocator, size);
    if (mem == NULL)
        return NULL;
    memset(mem, 0, size);
    return mem;
}