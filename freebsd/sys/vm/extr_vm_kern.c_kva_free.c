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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_arena ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kva_free(vm_offset_t addr, vm_size_t size)
{

	size = round_page(size);
	vmem_free(kernel_arena, addr, size);
}