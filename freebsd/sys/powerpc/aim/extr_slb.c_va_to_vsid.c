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
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;
struct slb {int slbv; } ;
typedef  scalar_t__ pmap_t ;

/* Variables and functions */
 uintptr_t ADDR_SR_SHFT ; 
 int KERNEL_VSID (uintptr_t) ; 
 int SLBV_VSID_MASK ; 
 int SLBV_VSID_SHIFT ; 
 int allocate_user_vsid (scalar_t__,uintptr_t,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_pmap ; 
 struct slb* user_va_to_slb_entry (scalar_t__,scalar_t__) ; 

uint64_t
va_to_vsid(pmap_t pm, vm_offset_t va)
{
	struct slb *entry;

	/* Shortcut kernel case */
	if (pm == kernel_pmap)
		return (KERNEL_VSID((uintptr_t)va >> ADDR_SR_SHFT));

	/*
	 * If there is no vsid for this VA, we need to add a new entry
	 * to the PMAP's segment table.
	 */

	entry = user_va_to_slb_entry(pm, va);

	if (entry == NULL)
		return (allocate_user_vsid(pm,
		    (uintptr_t)va >> ADDR_SR_SHFT, 0));

	return ((entry->slbv & SLBV_VSID_MASK) >> SLBV_VSID_SHIFT);
}