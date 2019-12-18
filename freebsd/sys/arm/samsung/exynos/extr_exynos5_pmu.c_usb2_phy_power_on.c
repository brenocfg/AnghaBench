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
struct pmu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS5_PWR_USBHOST_PHY ; 
 int /*<<< orphan*/  PHY_POWER_ON ; 
 int /*<<< orphan*/  WRITE4 (struct pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmu_softc* pmu_sc ; 

int
usb2_phy_power_on(void)
{
	struct pmu_softc *sc;

	sc = pmu_sc;
	if (sc == NULL)
		return (-1);

	/* EHCI */
	WRITE4(sc, EXYNOS5_PWR_USBHOST_PHY, PHY_POWER_ON);

	return (0);
}