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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 size_t NPV_LIST_LOCKS ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 size_t pa_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pv_invl_gen ; 

__attribute__((used)) static u_long *
pmap_delayed_invl_genp(vm_page_t m)
{

	return (&pv_invl_gen[pa_index(VM_PAGE_TO_PHYS(m)) % NPV_LIST_LOCKS]);
}