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
struct vtdmap {int gsr; int /*<<< orphan*/  gcr; int /*<<< orphan*/  rta; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTD_GCR_SRTP ; 
 int VTD_GSR_RTPS ; 
 int drhd_num ; 
 int /*<<< orphan*/  root_table ; 
 int /*<<< orphan*/  vtd_ctx_global_invalidate (struct vtdmap*) ; 
 int /*<<< orphan*/  vtd_iotlb_global_invalidate (struct vtdmap*) ; 
 int /*<<< orphan*/  vtd_translation_enable (struct vtdmap*) ; 
 int /*<<< orphan*/  vtd_wbflush (struct vtdmap*) ; 
 struct vtdmap** vtdmaps ; 
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtd_enable(void)
{
	int i;
	struct vtdmap *vtdmap;

	for (i = 0; i < drhd_num; i++) {
		vtdmap = vtdmaps[i];
		vtd_wbflush(vtdmap);

		/* Update the root table address */
		vtdmap->rta = vtophys(root_table);
		vtdmap->gcr = VTD_GCR_SRTP;
		while ((vtdmap->gsr & VTD_GSR_RTPS) == 0)
			;

		vtd_ctx_global_invalidate(vtdmap);
		vtd_iotlb_global_invalidate(vtdmap);

		vtd_translation_enable(vtdmap);
	}
}