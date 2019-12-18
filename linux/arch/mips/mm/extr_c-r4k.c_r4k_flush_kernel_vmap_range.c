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
struct flush_kernel_vmap_range_args {unsigned long vaddr; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  R4K_HIT ; 
 int /*<<< orphan*/  R4K_INDEX ; 
 int dcache_size ; 
 int /*<<< orphan*/  local_r4k_flush_kernel_vmap_range ; 
 int /*<<< orphan*/  local_r4k_flush_kernel_vmap_range_index ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flush_kernel_vmap_range_args*) ; 

__attribute__((used)) static void r4k_flush_kernel_vmap_range(unsigned long vaddr, int size)
{
	struct flush_kernel_vmap_range_args args;

	args.vaddr = (unsigned long) vaddr;
	args.size = size;

	if (size >= dcache_size)
		r4k_on_each_cpu(R4K_INDEX,
				local_r4k_flush_kernel_vmap_range_index, NULL);
	else
		r4k_on_each_cpu(R4K_HIT, local_r4k_flush_kernel_vmap_range,
				&args);
}