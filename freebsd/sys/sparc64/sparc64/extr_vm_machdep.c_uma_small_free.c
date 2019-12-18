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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLB_DIRECT_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_nsmall_free ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 

void
uma_small_free(void *mem, vm_size_t size, u_int8_t flags)
{
	vm_page_t m;

	PMAP_STATS_INC(uma_nsmall_free);
	m = PHYS_TO_VM_PAGE(TLB_DIRECT_TO_PHYS((vm_offset_t)mem));
	vm_page_unwire_noq(m);
	vm_page_free(m);
}