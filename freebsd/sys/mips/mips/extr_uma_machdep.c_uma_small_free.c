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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_DIRECT_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_drop_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 

void
uma_small_free(void *mem, vm_size_t size, u_int8_t flags)
{
	vm_page_t m;
	vm_paddr_t pa;

	pa = MIPS_DIRECT_TO_PHYS((vm_offset_t)mem);
	dump_drop_page(pa);
	m = PHYS_TO_VM_PAGE(pa);
	vm_page_unwire_noq(m);
	vm_page_free(m);
}