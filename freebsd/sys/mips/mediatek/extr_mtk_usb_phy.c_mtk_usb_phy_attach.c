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
struct mtk_usb_phy_softc {int socid; int /*<<< orphan*/ * res; int /*<<< orphan*/  sr_coef; int /*<<< orphan*/  u2_base; int /*<<< orphan*/  fm_base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MT7621_FM_FEG_BASE ; 
 int /*<<< orphan*/  MT7621_SR_COEF ; 
 int /*<<< orphan*/  MT7621_U2_BASE ; 
 int /*<<< orphan*/  MT7628_FM_FEG_BASE ; 
 int /*<<< orphan*/  MT7628_SR_COEF ; 
 int /*<<< orphan*/  MT7628_U2_BASE ; 
#define  MTK_SOC_MT7621 130 
#define  MTK_SOC_MT7628 129 
#define  MTK_SOC_MT7688 128 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RESET_ASSERT_DELAY ; 
 int /*<<< orphan*/  RESET_DEASSERT_DELAY ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYSCFG1_USB_HOST_MODE ; 
 int /*<<< orphan*/  SYSCTL_SYSCFG1 ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mtk_usb_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_clock_enable_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_reset_assert_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_reset_deassert_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sysctl_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_sysctl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_usb_phy_mt7621_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_usb_phy_mt7628_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_usb_phy_attach(device_t dev)
{
	struct mtk_usb_phy_softc * sc = device_get_softc(dev);
	phandle_t node;
	uint32_t val;
	int rid;

	sc->dev = dev;

	/* Get our FDT node and SoC id */
	node = ofw_bus_get_node(dev);

	/* Now let's see about setting USB to host or device mode */
	/* XXX: is it the same for all SoCs? */
	val = mtk_sysctl_get(SYSCTL_SYSCFG1);
	if (OF_hasprop(node, "mtk,usb-device"))
		val &= ~SYSCFG1_USB_HOST_MODE;
	else
		val |= SYSCFG1_USB_HOST_MODE;
	mtk_sysctl_set(SYSCTL_SYSCFG1, val);

	/* If we have clocks defined - enable them */
	if (OF_hasprop(node, "clocks"))
		fdt_clock_enable_all(dev);

	/* If we have resets defined - perform a reset sequence */
	if (OF_hasprop(node, "resets")) {
		fdt_reset_assert_all(dev);
		DELAY(RESET_ASSERT_DELAY);
		fdt_reset_deassert_all(dev);
		DELAY(RESET_DEASSERT_DELAY);
	}

	/* Careful, some devices actually require resources */
	if (OF_hasprop(node, "reg")) {
		rid = 0;
		sc->res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
		    RF_ACTIVE);
		if (sc->res == NULL) {
			device_printf(dev, "could not map memory\n");
			return (ENXIO);
		}
	} else {
		sc->res = NULL;
	}

	/* Some SoCs require specific USB PHY init... handle these */
	switch (sc->socid) {
	case MTK_SOC_MT7628: /* Fallthrough */
	case MTK_SOC_MT7688:
		if (sc->res == NULL)
			return (ENXIO);
		sc->fm_base = MT7628_FM_FEG_BASE;
		sc->u2_base = MT7628_U2_BASE;
		sc->sr_coef = MT7628_SR_COEF;
		mtk_usb_phy_mt7628_init(dev);
		break;
	case MTK_SOC_MT7621:
		if (sc->res == NULL)
			return (ENXIO);
		sc->fm_base = MT7621_FM_FEG_BASE;
		sc->u2_base = MT7621_U2_BASE;
		sc->sr_coef = MT7621_SR_COEF;
		mtk_usb_phy_mt7621_init(dev);
		break;
	}

	/* We no longer need the resources, release them */
	if (sc->res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->res);

	return (0);
}