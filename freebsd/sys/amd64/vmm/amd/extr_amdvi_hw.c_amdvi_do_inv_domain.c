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
struct amdvi_softc {int pci_cap; } ;

/* Variables and functions */
 int AMDVI_PCI_CAP_NPCACHE ; 
 int /*<<< orphan*/  KASSERT (struct amdvi_softc*,char*) ; 
 int /*<<< orphan*/  amdvi_inv_domain (struct amdvi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdvi_wait (struct amdvi_softc*) ; 
 struct amdvi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ivhd_count ; 
 int /*<<< orphan*/ * ivhd_devs ; 

__attribute__((used)) static void
amdvi_do_inv_domain(uint16_t domain_id, bool create)
{
	struct amdvi_softc *softc;
	int i;

	for (i = 0; i < ivhd_count; i++) {
		softc = device_get_softc(ivhd_devs[i]);
		KASSERT(softc, ("softc is NULL"));
		/*
		 * If not present pages are cached, invalidate page after
		 * creating domain.
		 */
#if 0
		if (create && ((softc->pci_cap & AMDVI_PCI_CAP_NPCACHE) == 0))
			continue;
#endif
		amdvi_inv_domain(softc, domain_id);
		amdvi_wait(softc);
	}
}