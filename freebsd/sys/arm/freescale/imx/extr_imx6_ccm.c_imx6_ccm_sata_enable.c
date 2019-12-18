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
typedef  int uint32_t ;

/* Variables and functions */
 int CCGR5_SATA ; 
 int /*<<< orphan*/  CCM_ANALOG_PLL_ENET ; 
 int CCM_ANALOG_PLL_ENET_BYPASS ; 
 int CCM_ANALOG_PLL_ENET_ENABLE ; 
 int CCM_ANALOG_PLL_ENET_ENABLE_100M ; 
 int CCM_ANALOG_PLL_ENET_LOCK ; 
 int CCM_ANALOG_PLL_ENET_POWERDOWN ; 
 int /*<<< orphan*/  CCM_CCGR5 ; 
 int ETIMEDOUT ; 
 int RD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ccm_sc ; 

int
imx6_ccm_sata_enable(void)
{
	uint32_t v;
	int timeout;

	/* Un-gate the sata controller. */
	WR4(ccm_sc, CCM_CCGR5, RD4(ccm_sc, CCM_CCGR5) | CCGR5_SATA);

	/* Power up the PLL that feeds ENET/SATA/PCI phys, wait for lock. */
	v = RD4(ccm_sc, CCM_ANALOG_PLL_ENET);
	v &= ~CCM_ANALOG_PLL_ENET_POWERDOWN;
	WR4(ccm_sc, CCM_ANALOG_PLL_ENET, v);

	for (timeout = 100000; timeout > 0; timeout--) {
		if (RD4(ccm_sc, CCM_ANALOG_PLL_ENET) &
		   CCM_ANALOG_PLL_ENET_LOCK) {
			break;
		}
	}
	if (timeout <= 0) {
		return ETIMEDOUT;
	}

	/* Enable the PLL, and enable its 100mhz output. */
	v |= CCM_ANALOG_PLL_ENET_ENABLE;
	v &= ~CCM_ANALOG_PLL_ENET_BYPASS;
	WR4(ccm_sc, CCM_ANALOG_PLL_ENET, v);

	v |= CCM_ANALOG_PLL_ENET_ENABLE_100M;
	WR4(ccm_sc, CCM_ANALOG_PLL_ENET, v);

	return 0;
}