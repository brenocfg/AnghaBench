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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 scalar_t__ DMAP_BASE_ADDRESS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PSL_DR ; 
 int mfmsr () ; 
 int /*<<< orphan*/  pmap_bootstrapped ; 

vm_offset_t
pmap_early_io_map(vm_paddr_t pa, vm_size_t size)
{
	KASSERT(!pmap_bootstrapped, ("Not available after PMAP started!"));

	/*
	 * If we have the MMU up in early boot, assume it is 1:1. Otherwise,
	 * try to get the address in a memory region compatible with the
	 * direct map for efficiency later.
	 */
	if (mfmsr() & PSL_DR)
		return (pa);
	else
		return (DMAP_BASE_ADDRESS + pa);
}