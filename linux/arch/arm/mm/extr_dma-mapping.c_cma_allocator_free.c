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
struct arm_dma_free_args {int /*<<< orphan*/  want_vaddr; int /*<<< orphan*/  size; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  page; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_from_contiguous (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cma_allocator_free(struct arm_dma_free_args *args)
{
	__free_from_contiguous(args->dev, args->page, args->cpu_addr,
			       args->size, args->want_vaddr);
}