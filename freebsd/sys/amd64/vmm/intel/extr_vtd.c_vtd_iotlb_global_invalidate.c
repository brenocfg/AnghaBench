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
typedef  int uint64_t ;
struct vtdmap {int /*<<< orphan*/  ext_cap; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int VTD_ECAP_IRO (int /*<<< orphan*/ ) ; 
 int volatile VTD_IIR_DRAIN_READS ; 
 int volatile VTD_IIR_DRAIN_WRITES ; 
 int volatile VTD_IIR_IIRG_GLOBAL ; 
 int volatile VTD_IIR_IVT ; 
 int /*<<< orphan*/  vtd_wbflush (struct vtdmap*) ; 

__attribute__((used)) static void
vtd_iotlb_global_invalidate(struct vtdmap *vtdmap)
{
	int offset;
	volatile uint64_t *iotlb_reg, val;

	vtd_wbflush(vtdmap);

	offset = VTD_ECAP_IRO(vtdmap->ext_cap) * 16;
	iotlb_reg = (volatile uint64_t *)((caddr_t)vtdmap + offset + 8);
	
	*iotlb_reg =  VTD_IIR_IVT | VTD_IIR_IIRG_GLOBAL |
		      VTD_IIR_DRAIN_READS | VTD_IIR_DRAIN_WRITES;

	while (1) {
		val = *iotlb_reg;
		if ((val & VTD_IIR_IVT) == 0)
			break;
	}
}