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
typedef  scalar_t__ vm_paddr_t ;
struct vmspace {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_map_remove (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void
vmm_mmio_free(struct vmspace *vmspace, vm_paddr_t gpa, size_t len)
{

	vm_map_remove(&vmspace->vm_map, gpa, gpa + len);
}