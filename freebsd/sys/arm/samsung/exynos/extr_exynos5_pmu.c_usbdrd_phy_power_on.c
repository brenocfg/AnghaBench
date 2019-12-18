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
struct pmu_softc {scalar_t__ model; } ;

/* Variables and functions */
 scalar_t__ EXYNOS5420 ; 
 int /*<<< orphan*/  EXYNOS5420_USBDRD1_PHY_CTRL ; 
 int /*<<< orphan*/  EXYNOS5_USBDRD_PHY_CTRL ; 
 int /*<<< orphan*/  PHY_POWER_ON ; 
 int /*<<< orphan*/  WRITE4 (struct pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmu_softc* pmu_sc ; 

int
usbdrd_phy_power_on(void)
{
	struct pmu_softc *sc;

	sc = pmu_sc;
	if (sc == NULL)
		return (-1);

	/*
	 * First XHCI controller (left-side USB port on chromebook2)
	 */
	WRITE4(sc, EXYNOS5_USBDRD_PHY_CTRL, PHY_POWER_ON);

	/*
	 * Second XHCI controller (right-side USB port on chrombook2)
	 * Only available on 5420.
	 */
	if (sc->model == EXYNOS5420)
		WRITE4(sc, EXYNOS5420_USBDRD1_PHY_CTRL, PHY_POWER_ON);

	return (0);
}