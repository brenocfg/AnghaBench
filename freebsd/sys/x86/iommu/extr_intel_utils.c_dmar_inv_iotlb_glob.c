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
struct dmar_unit {int /*<<< orphan*/  hw_ecap; int /*<<< orphan*/  qi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_ASSERT_LOCKED (struct dmar_unit*) ; 
 int DMAR_ECAP_IRO (int /*<<< orphan*/ ) ; 
 int DMAR_IOTLB_DR ; 
 int DMAR_IOTLB_DW ; 
 int DMAR_IOTLB_IIRG_GLB ; 
 int DMAR_IOTLB_IVT ; 
 int DMAR_IOTLB_IVT32 ; 
 scalar_t__ DMAR_IOTLB_REG_OFF ; 
 int /*<<< orphan*/  DMAR_WAIT_UNTIL (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int dmar_read4 (struct dmar_unit*,scalar_t__) ; 
 int /*<<< orphan*/  dmar_write8 (struct dmar_unit*,scalar_t__,int) ; 

int
dmar_inv_iotlb_glob(struct dmar_unit *unit)
{
	int error, reg;

	DMAR_ASSERT_LOCKED(unit);
	KASSERT(!unit->qi_enabled, ("QI enabled"));

	reg = 16 * DMAR_ECAP_IRO(unit->hw_ecap);
	/* See a comment about DMAR_CCMD_ICC in dmar_inv_ctx_glob. */
	dmar_write8(unit, reg + DMAR_IOTLB_REG_OFF, DMAR_IOTLB_IVT |
	    DMAR_IOTLB_IIRG_GLB | DMAR_IOTLB_DR | DMAR_IOTLB_DW);
	DMAR_WAIT_UNTIL(((dmar_read4(unit, reg + DMAR_IOTLB_REG_OFF + 4) &
	    DMAR_IOTLB_IVT32) == 0));
	return (error);
}