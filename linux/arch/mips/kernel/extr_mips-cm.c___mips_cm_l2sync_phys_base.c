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
typedef  int u32 ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int CM_GCR_L2_ONLY_SYNC_BASE_SYNCBASE ; 
 int CM_GCR_L2_ONLY_SYNC_BASE_SYNCEN ; 
 int MIPS_CM_GCR_SIZE ; 
 int mips_cm_phys_base () ; 
 int read_gcr_l2_only_sync_base () ; 

phys_addr_t __mips_cm_l2sync_phys_base(void)
{
	u32 base_reg;

	/*
	 * If the L2-only sync region is already enabled then leave it at it's
	 * current location.
	 */
	base_reg = read_gcr_l2_only_sync_base();
	if (base_reg & CM_GCR_L2_ONLY_SYNC_BASE_SYNCEN)
		return base_reg & CM_GCR_L2_ONLY_SYNC_BASE_SYNCBASE;

	/* Default to following the CM */
	return mips_cm_phys_base() + MIPS_CM_GCR_SIZE;
}