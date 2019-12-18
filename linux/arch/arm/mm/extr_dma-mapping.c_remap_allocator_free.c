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
struct arm_dma_free_args {int /*<<< orphan*/  size; int /*<<< orphan*/  page; int /*<<< orphan*/  cpu_addr; scalar_t__ want_vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dma_free_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_common_free_remap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remap_allocator_free(struct arm_dma_free_args *args)
{
	if (args->want_vaddr)
		dma_common_free_remap(args->cpu_addr, args->size);

	__dma_free_buffer(args->page, args->size);
}