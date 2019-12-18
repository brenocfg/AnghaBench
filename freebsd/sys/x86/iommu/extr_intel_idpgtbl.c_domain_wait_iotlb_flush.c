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
struct dmar_unit {int dummy; } ;

/* Variables and functions */
 int DMAR_IOTLB_DR ; 
 int DMAR_IOTLB_DW ; 
 int DMAR_IOTLB_IVT ; 
 scalar_t__ DMAR_IOTLB_REG_OFF ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int dmar_read8 (struct dmar_unit*,scalar_t__) ; 
 int /*<<< orphan*/  dmar_write8 (struct dmar_unit*,scalar_t__,int) ; 

__attribute__((used)) static inline uint64_t
domain_wait_iotlb_flush(struct dmar_unit *unit, uint64_t wt, int iro)
{
	uint64_t iotlbr;

	dmar_write8(unit, iro + DMAR_IOTLB_REG_OFF, DMAR_IOTLB_IVT |
	    DMAR_IOTLB_DR | DMAR_IOTLB_DW | wt);
	for (;;) {
		iotlbr = dmar_read8(unit, iro + DMAR_IOTLB_REG_OFF);
		if ((iotlbr & DMAR_IOTLB_IVT) == 0)
			break;
		cpu_spinwait();
	}
	return (iotlbr);
}