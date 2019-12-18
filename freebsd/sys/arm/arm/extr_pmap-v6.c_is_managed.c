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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct TYPE_3__ {int oflags; } ;

/* Variables and functions */
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int VPO_UNMANAGED ; 

__attribute__((used)) static __inline bool
is_managed(vm_paddr_t pa)
{
	vm_page_t m;

	m = PHYS_TO_VM_PAGE(pa);
	if (m == NULL)
		return (false);
	return ((m->oflags & VPO_UNMANAGED) == 0);
}