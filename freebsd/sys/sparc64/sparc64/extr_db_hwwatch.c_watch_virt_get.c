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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  AA_DMMU_VWPR ; 
 int /*<<< orphan*/  ASI_DMMU ; 
 int /*<<< orphan*/  ASI_LSU_CTL_REG ; 
 int LSU_VM_MASK ; 
 int LSU_VM_SHIFT ; 
 int ldxa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watch_virt_active () ; 

vm_offset_t
watch_virt_get(int *bm)
{
	u_long va;
	u_long lsucr;
	
	if (!watch_virt_active())
		return (0);

	va = ldxa(AA_DMMU_VWPR, ASI_DMMU);
	lsucr = ldxa(0, ASI_LSU_CTL_REG);
	*bm = (lsucr & LSU_VM_MASK) >> LSU_VM_SHIFT;
	
	return ((vm_offset_t)va);
}