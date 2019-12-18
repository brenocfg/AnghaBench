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
typedef  int /*<<< orphan*/  uint32_t ;
struct tegra_xhci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARU_C11_CSBRANGE_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARU_C11_CSBRANGE_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPCI_WR4 (struct tegra_xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_C11_CSBRANGE ; 

__attribute__((used)) static void
CSB_WR4(struct tegra_xhci_softc *sc, uint32_t addr, uint32_t val)
{

	FPCI_WR4(sc, XUSB_CFG_ARU_C11_CSBRANGE, ARU_C11_CSBRANGE_PAGE(addr));
	FPCI_WR4(sc, ARU_C11_CSBRANGE_ADDR(addr), val);
}