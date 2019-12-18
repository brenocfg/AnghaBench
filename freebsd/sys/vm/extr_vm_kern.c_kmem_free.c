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
struct vmem {int dummy; } ;

/* Variables and functions */
 struct vmem* _kmem_unback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_object ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_free (struct vmem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kmem_free(vm_offset_t addr, vm_size_t size)
{
	struct vmem *arena;

	size = round_page(size);
	arena = _kmem_unback(kernel_object, addr, size);
	if (arena != NULL)
		vmem_free(arena, addr, size);
}