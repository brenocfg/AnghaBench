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
struct xbb_softc {scalar_t__ kva; int /*<<< orphan*/ * kva_free; scalar_t__ gnt_base_addr; int /*<<< orphan*/ * pseudo_phys_res; int /*<<< orphan*/  pseudo_phys_res_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENBLOCKBACK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xbb_free_communication_mem(struct xbb_softc *xbb)
{
	if (xbb->kva != 0) {
		if (xbb->pseudo_phys_res != NULL) {
			xenmem_free(xbb->dev, xbb->pseudo_phys_res_id,
			    xbb->pseudo_phys_res);
			xbb->pseudo_phys_res = NULL;
		}
	}
	xbb->kva = 0;
	xbb->gnt_base_addr = 0;
	if (xbb->kva_free != NULL) {
		free(xbb->kva_free, M_XENBLOCKBACK);
		xbb->kva_free = NULL;
	}
}