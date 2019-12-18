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
struct page {int dummy; } ;
struct arm_dma_alloc_args {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 void* __alloc_from_pool (int /*<<< orphan*/ ,struct page**) ; 

__attribute__((used)) static void *pool_allocator_alloc(struct arm_dma_alloc_args *args,
				  struct page **ret_page)
{
	return __alloc_from_pool(args->size, ret_page);
}