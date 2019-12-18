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

/* Variables and functions */
 unsigned long APIC_DM_INIT ; 
 unsigned long APIC_DM_STARTUP ; 
 int /*<<< orphan*/  UVH_IPI_INT ; 
 int UVH_IPI_INT_APIC_ID_SHFT ; 
 unsigned long UVH_IPI_INT_SEND_SHFT ; 
 unsigned long UVH_IPI_INT_VECTOR_SHFT ; 
 int uv_apicid_hibits ; 
 int uv_apicid_to_pnode (int) ; 
 int /*<<< orphan*/  uv_write_global_mmr64 (int,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int uv_wakeup_secondary(int phys_apicid, unsigned long start_rip)
{
	unsigned long val;
	int pnode;

	pnode = uv_apicid_to_pnode(phys_apicid);
	phys_apicid |= uv_apicid_hibits;

	val = (1UL << UVH_IPI_INT_SEND_SHFT) |
	    (phys_apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	    ((start_rip << UVH_IPI_INT_VECTOR_SHFT) >> 12) |
	    APIC_DM_INIT;

	uv_write_global_mmr64(pnode, UVH_IPI_INT, val);

	val = (1UL << UVH_IPI_INT_SEND_SHFT) |
	    (phys_apicid << UVH_IPI_INT_APIC_ID_SHFT) |
	    ((start_rip << UVH_IPI_INT_VECTOR_SHFT) >> 12) |
	    APIC_DM_STARTUP;

	uv_write_global_mmr64(pnode, UVH_IPI_INT, val);

	return 0;
}