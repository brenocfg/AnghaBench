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
struct ti_clock_dev {int id; } ;
struct resource {int dummy; } ;
struct omap4_prcm_softc {struct resource* sc_res; } ;

/* Variables and functions */
 int CLKCTRL_IDLEST_ENABLED ; 
 int CLKCTRL_IDLEST_MASK ; 
 int CLKCTRL_MODULEMODE_ENABLE ; 
 int CLKCTRL_MODULEMODE_MASK ; 
 int /*<<< orphan*/  CM2_INSTANCE ; 
 int EINVAL ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  L3INIT_CM2_OFFSET ; 
 unsigned int MAX_MODULE_ENABLE_WAIT ; 
#define  USBHSHOST_CLK 135 
#define  USBP1_HSIC_CLK 134 
#define  USBP1_PHY_CLK 133 
#define  USBP1_UTMI_CLK 132 
#define  USBP2_HSIC_CLK 131 
#define  USBP2_PHY_CLK 130 
#define  USBP2_UTMI_CLK 129 
#define  USBTLL_CLK 128 
 int bus_read_4 (struct resource*,int) ; 
 int /*<<< orphan*/  bus_write_4 (struct resource*,int,int) ; 
 struct omap4_prcm_softc* omap4_prcm_get_instance_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int const,...) ; 

__attribute__((used)) static int
omap4_clk_hsusbhost_activate(struct ti_clock_dev *clkdev)
{
	struct omap4_prcm_softc *sc;
	struct resource* clk_mem_res;
	uint32_t clksel_reg_off;
	uint32_t clksel;
	unsigned int i;

	sc = omap4_prcm_get_instance_softc(CM2_INSTANCE);
	if (sc == NULL)
		return ENXIO;

	switch (clkdev->id) {
	case USBTLL_CLK:
		/* For the USBTLL module we need to enable the following clocks:
		 *  - INIT_L4_ICLK  (will be enabled by bootloader)
		 *  - TLL_CH0_FCLK
		 *  - TLL_CH1_FCLK
		 */

		/* We need the CM_L3INIT_HSUSBTLL_CLKCTRL register in CM2 register set */
		clk_mem_res = sc->sc_res;
		clksel_reg_off = L3INIT_CM2_OFFSET + 0x68;
	
		/* Enable the module and also enable the optional func clocks for
		 * channels 0 & 1 (is this needed ?)
		 */
		clksel = bus_read_4(clk_mem_res, clksel_reg_off);
		clksel &= ~CLKCTRL_MODULEMODE_MASK;
		clksel |=  CLKCTRL_MODULEMODE_ENABLE;
		
		clksel |= (0x1 << 8); /* USB-HOST optional clock: USB_CH0_CLK */
		clksel |= (0x1 << 9); /* USB-HOST optional clock: USB_CH1_CLK */
		break;

	case USBHSHOST_CLK:
	case USBP1_PHY_CLK:
	case USBP2_PHY_CLK:
	case USBP1_UTMI_CLK:
	case USBP2_UTMI_CLK:
	case USBP1_HSIC_CLK:
	case USBP2_HSIC_CLK:
		/* For the USB HS HOST module we need to enable the following clocks:
		 *  - INIT_L4_ICLK     (will be enabled by bootloader)
		 *  - INIT_L3_ICLK     (will be enabled by bootloader)
		 *  - INIT_48MC_FCLK
		 *  - UTMI_ROOT_GFCLK  (UTMI only, create a new clock for that ?)
		 *  - UTMI_P1_FCLK     (UTMI only, create a new clock for that ?)
		 *  - UTMI_P2_FCLK     (UTMI only, create a new clock for that ?)
		 *  - HSIC_P1_60       (HSIC only, create a new clock for that ?)
		 *  - HSIC_P1_480      (HSIC only, create a new clock for that ?)
		 *  - HSIC_P2_60       (HSIC only, create a new clock for that ?)
		 *  - HSIC_P2_480      (HSIC only, create a new clock for that ?)
		 */

		/* We need the CM_L3INIT_HSUSBHOST_CLKCTRL register in CM2 register set */
		clk_mem_res = sc->sc_res;
		clksel_reg_off = L3INIT_CM2_OFFSET + 0x58;
		clksel = bus_read_4(clk_mem_res, clksel_reg_off);	
		/* Enable the module and also enable the optional func clocks */
		if (clkdev->id == USBHSHOST_CLK) {
			clksel &= ~CLKCTRL_MODULEMODE_MASK;
			clksel |=  /*CLKCTRL_MODULEMODE_ENABLE*/2;

			clksel |= (0x1 << 15); /* USB-HOST clock control: FUNC48MCLK */
		}
		
		else if (clkdev->id == USBP1_UTMI_CLK)
			clksel |= (0x1 << 8);  /* UTMI_P1_CLK */
		else if (clkdev->id == USBP2_UTMI_CLK)
			clksel |= (0x1 << 9);  /* UTMI_P2_CLK */

		else if (clkdev->id == USBP1_HSIC_CLK)
			clksel |= (0x5 << 11);  /* HSIC60M_P1_CLK + HSIC480M_P1_CLK */
		else if (clkdev->id == USBP2_HSIC_CLK)
			clksel |= (0x5 << 12);  /* HSIC60M_P2_CLK + HSIC480M_P2_CLK */
		
		break;
	
	default:
		return (EINVAL);
	}
	
	bus_write_4(clk_mem_res, clksel_reg_off, clksel);
	
	/* Try MAX_MODULE_ENABLE_WAIT number of times to check if enabled */
	for (i = 0; i < MAX_MODULE_ENABLE_WAIT; i++) {
		clksel = bus_read_4(clk_mem_res, clksel_reg_off);
		if ((clksel & CLKCTRL_IDLEST_MASK) == CLKCTRL_IDLEST_ENABLED)
			break;
	}
		
	/* Check the enabled state */
	if ((clksel & CLKCTRL_IDLEST_MASK) != CLKCTRL_IDLEST_ENABLED) {
		printf("Error: HERE failed to enable module with clock %d\n", clkdev->id);
		printf("Error: 0x%08x => 0x%08x\n", clksel_reg_off, clksel);
		return (ETIMEDOUT);
	}
	
	return (0);
}