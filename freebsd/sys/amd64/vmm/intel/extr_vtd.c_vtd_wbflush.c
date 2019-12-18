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
struct vtdmap {int gsr; int /*<<< orphan*/  gcr; int /*<<< orphan*/  cap; int /*<<< orphan*/  ext_cap; } ;

/* Variables and functions */
 scalar_t__ VTD_CAP_RWBF (int /*<<< orphan*/ ) ; 
 scalar_t__ VTD_ECAP_COHERENCY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTD_GCR_WBF ; 
 int VTD_GSR_WBFS ; 
 int /*<<< orphan*/  pmap_invalidate_cache () ; 

__attribute__((used)) static void
vtd_wbflush(struct vtdmap *vtdmap)
{

	if (VTD_ECAP_COHERENCY(vtdmap->ext_cap) == 0)
		pmap_invalidate_cache();

	if (VTD_CAP_RWBF(vtdmap->cap)) {
		vtdmap->gcr = VTD_GCR_WBF;
		while ((vtdmap->gsr & VTD_GSR_WBFS) != 0)
			;
	}
}