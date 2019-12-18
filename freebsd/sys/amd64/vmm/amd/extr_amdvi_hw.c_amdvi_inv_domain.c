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
typedef  int /*<<< orphan*/  uint16_t ;
struct amdvi_softc {int /*<<< orphan*/  dev; } ;
struct amdvi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDVI_INVD_PAGE_ALL_ADDR ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  amdvi_cmd_inv_iommu_pages (struct amdvi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct amdvi_cmd* amdvi_get_cmd_tail (struct amdvi_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amdvi_inv_domain(struct amdvi_softc *softc, uint16_t domain_id)
{
	struct amdvi_cmd *cmd;

	cmd = amdvi_get_cmd_tail(softc);
	KASSERT(cmd != NULL, ("Cmd is NULL"));

	/*
	 * See section 3.3.3 of IOMMU spec rev 2.0, software note
	 * for invalidating domain.
	 */
	amdvi_cmd_inv_iommu_pages(softc, domain_id, AMDVI_INVD_PAGE_ALL_ADDR,
				false, true, true);

#ifdef AMDVI_DEBUG_CMD
	device_printf(softc->dev, "Invalidate domain:0x%x\n", domain_id);

#endif
}