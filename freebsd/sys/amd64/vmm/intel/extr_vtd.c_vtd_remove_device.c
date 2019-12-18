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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vtdmap {int dummy; } ;

/* Variables and functions */
 size_t PCI_RID2BUS (int /*<<< orphan*/ ) ; 
 int VTD_RID2IDX (int /*<<< orphan*/ ) ; 
 scalar_t__** ctx_tables ; 
 int drhd_num ; 
 int /*<<< orphan*/  vtd_ctx_global_invalidate (struct vtdmap*) ; 
 int /*<<< orphan*/  vtd_iotlb_global_invalidate (struct vtdmap*) ; 
 struct vtdmap** vtdmaps ; 

__attribute__((used)) static void
vtd_remove_device(void *arg, uint16_t rid)
{
	int i, idx;
	uint64_t *ctxp;
	struct vtdmap *vtdmap;
	uint8_t bus;

	bus = PCI_RID2BUS(rid);
	ctxp = ctx_tables[bus];
	idx = VTD_RID2IDX(rid);

	/*
	 * Order is important. The 'present' bit is must be cleared first.
	 */
	ctxp[idx] = 0;
	ctxp[idx + 1] = 0;

	/*
	 * Invalidate the Context Cache and the IOTLB.
	 *
	 * XXX use device-selective invalidation for Context Cache
	 * XXX use domain-selective invalidation for IOTLB
	 */
	for (i = 0; i < drhd_num; i++) {
		vtdmap = vtdmaps[i];
		vtd_ctx_global_invalidate(vtdmap);
		vtd_iotlb_global_invalidate(vtdmap);
	}
}