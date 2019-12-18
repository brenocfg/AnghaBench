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
struct amdvi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct amdvi_softc*,char*) ; 
 int /*<<< orphan*/  amdvi_cmd_inv_dte (struct amdvi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdvi_cmd_inv_iotlb (struct amdvi_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ amdvi_dev_support_iotlb (struct amdvi_softc*,int /*<<< orphan*/ ) ; 
 struct amdvi_softc* amdvi_find_iommu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdvi_wait (struct amdvi_softc*) ; 

__attribute__((used)) static void
amdvi_inv_device(uint16_t devid)
{
	struct amdvi_softc *softc;

	softc = amdvi_find_iommu(devid);
	KASSERT(softc, ("softc is NULL"));

	amdvi_cmd_inv_dte(softc, devid);
#ifdef AMDVI_ATS_ENABLE
	if (amdvi_dev_support_iotlb(softc, devid))
		amdvi_cmd_inv_iotlb(softc, devid);
#endif
	amdvi_wait(softc);
}