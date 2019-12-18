#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {char pin; char pol; int /*<<< orphan*/ * dev; } ;
struct aml8726_usb_phy_softc {int npwr_en; int /*<<< orphan*/  res; struct aml8726_usb_phy_gpio* pwr_en; TYPE_1__ hub_rst; scalar_t__ force_aca; int /*<<< orphan*/  dev; } ;
struct aml8726_usb_phy_gpio {char pin; char pol; int /*<<< orphan*/ * dev; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  char pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  AML_SOC_HW_REV_M8 129 
#define  AML_SOC_HW_REV_M8B 128 
 int AML_USB_PHY_ADP_BC_ACA_EN ; 
 int AML_USB_PHY_ADP_BC_ACA_FLOATING ; 
 int /*<<< orphan*/  AML_USB_PHY_ADP_BC_REG ; 
 int AML_USB_PHY_CFG_CLK_DIV_MASK ; 
 int AML_USB_PHY_CFG_CLK_DIV_SHIFT ; 
 int AML_USB_PHY_CFG_CLK_EN ; 
 int AML_USB_PHY_CFG_CLK_SEL_32K_ALT ; 
 int AML_USB_PHY_CFG_CLK_SEL_MASK ; 
 int AML_USB_PHY_CFG_CLK_SEL_XTAL ; 
 int /*<<< orphan*/  AML_USB_PHY_CFG_REG ; 
 int AML_USB_PHY_CTRL_CLK_DETECTED ; 
 int AML_USB_PHY_CTRL_FSEL_12M ; 
 int AML_USB_PHY_CTRL_FSEL_24M ; 
 int AML_USB_PHY_CTRL_FSEL_MASK ; 
 int AML_USB_PHY_CTRL_POR ; 
 int /*<<< orphan*/  AML_USB_PHY_CTRL_REG ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 scalar_t__ GPIO_PIN_SET (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 scalar_t__ GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 void* OF_device_from_xref (char) ; 
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  PIN_OFF_FLAG (char) ; 
 int /*<<< orphan*/  PIN_ON_FLAG (char) ; 
 scalar_t__ TRUE ; 
 int aml8726_soc_hw_rev ; 
 int /*<<< orphan*/  aml8726_usb_phy_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_usb_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct aml8726_usb_phy_gpio*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
aml8726_usb_phy_attach(device_t dev)
{
	struct aml8726_usb_phy_softc *sc = device_get_softc(dev);
	char *force_aca;
	int err;
	int npwr_en;
	pcell_t *prop;
	phandle_t node;
	ssize_t len;
	uint32_t div;
	uint32_t i;
	uint32_t value;

	sc->dev = dev;

	if (bus_alloc_resources(dev, aml8726_usb_phy_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	node = ofw_bus_get_node(dev);

	len = OF_getprop_alloc(node, "force-aca",
	    (void **)&force_aca);

	sc->force_aca = FALSE;

	if (len > 0) {
		if (strncmp(force_aca, "true", len) == 0)
			sc->force_aca = TRUE;
	}

	OF_prop_free(force_aca);

	err = 0;

	len = OF_getencprop_alloc_multi(node, "usb-pwr-en",
	    3 * sizeof(pcell_t), (void **)&prop);
	npwr_en = (len > 0) ? len : 0;

	sc->npwr_en = 0;
	sc->pwr_en = (struct aml8726_usb_phy_gpio *)
	    malloc(npwr_en * sizeof (*sc->pwr_en), M_DEVBUF, M_WAITOK);

	for (i = 0; i < npwr_en; i++) {
		sc->pwr_en[i].dev = OF_device_from_xref(prop[i * 3]);
		sc->pwr_en[i].pin = prop[i * 3 + 1];
		sc->pwr_en[i].pol = prop[i * 3 + 2];

		if (sc->pwr_en[i].dev == NULL) {
			err = 1;
			break;
		}
	}

	OF_prop_free(prop);

	len = OF_getencprop_alloc_multi(node, "usb-hub-rst",
	    3 * sizeof(pcell_t), (void **)&prop);
	if (len > 0) {
		sc->hub_rst.dev = OF_device_from_xref(prop[0]);
		sc->hub_rst.pin = prop[1];
		sc->hub_rst.pol = prop[2];

		if (len > 1 || sc->hub_rst.dev == NULL)
			err = 1;
	}

	OF_prop_free(prop);

	if (err) {
		device_printf(dev, "unable to parse gpio\n");
		goto fail;
	}

	/* Turn on power by setting pin and then enabling output driver. */
	for (i = 0; i < npwr_en; i++) {
		if (GPIO_PIN_SET(sc->pwr_en[i].dev, sc->pwr_en[i].pin,
		    PIN_ON_FLAG(sc->pwr_en[i].pol)) != 0 ||
		    GPIO_PIN_SETFLAGS(sc->pwr_en[i].dev, sc->pwr_en[i].pin,
		    GPIO_PIN_OUTPUT) != 0) {
			device_printf(dev,
			    "could not use gpio to control power\n");
			goto fail;
		}

		sc->npwr_en++;
	}

	/*
	 * Configure the clock source and divider.
	 */

	value = CSR_READ_4(sc, AML_USB_PHY_CFG_REG);

	value &= ~(AML_USB_PHY_CFG_CLK_SEL_32K_ALT |
	    AML_USB_PHY_CFG_CLK_DIV_MASK |
	    AML_USB_PHY_CFG_CLK_SEL_MASK |
	    AML_USB_PHY_CFG_CLK_EN);

	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M8:
	case AML_SOC_HW_REV_M8B:
		value |= AML_USB_PHY_CFG_CLK_SEL_32K_ALT;
		break;
	default:
		div = 2;
		value |= AML_USB_PHY_CFG_CLK_SEL_XTAL;
		value |= ((div - 1) << AML_USB_PHY_CFG_CLK_DIV_SHIFT) &
		    AML_USB_PHY_CFG_CLK_DIV_MASK;
		value |= AML_USB_PHY_CFG_CLK_EN;
		break;
	}

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);

	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	/*
	 * Configure the clock frequency and issue a power on reset.
	 */

	value = CSR_READ_4(sc, AML_USB_PHY_CTRL_REG);

	value &= ~AML_USB_PHY_CTRL_FSEL_MASK;

	switch (aml8726_soc_hw_rev) {
	case AML_SOC_HW_REV_M8:
	case AML_SOC_HW_REV_M8B:
		value |= AML_USB_PHY_CTRL_FSEL_24M;
		break;
	default:
		value |= AML_USB_PHY_CTRL_FSEL_12M;
		break;
	}

	value |= AML_USB_PHY_CTRL_POR;

	CSR_WRITE_4(sc, AML_USB_PHY_CTRL_REG, value);

	CSR_BARRIER(sc, AML_USB_PHY_CTRL_REG);

	DELAY(500);

	/*
	 * Enable by clearing the power on reset.
	 */

	value &= ~AML_USB_PHY_CTRL_POR;

	CSR_WRITE_4(sc, AML_USB_PHY_CTRL_REG, value);

	CSR_BARRIER(sc, AML_USB_PHY_CTRL_REG);

	DELAY(1000);

	/*
	 * Check if the clock was detected.
	 */
	value = CSR_READ_4(sc, AML_USB_PHY_CTRL_REG);
	if ((value & AML_USB_PHY_CTRL_CLK_DETECTED) == 0)
		device_printf(dev, "PHY Clock not detected\n");

	/*
	 * If necessary enabled Accessory Charger Adaptor detection
	 * so that the port knows what mode to operate in.
	 */
	if (sc->force_aca) {
		value = CSR_READ_4(sc, AML_USB_PHY_ADP_BC_REG);

		value |= AML_USB_PHY_ADP_BC_ACA_EN;

		CSR_WRITE_4(sc, AML_USB_PHY_ADP_BC_REG, value);

		CSR_BARRIER(sc, AML_USB_PHY_ADP_BC_REG);

		DELAY(50);

		value = CSR_READ_4(sc, AML_USB_PHY_ADP_BC_REG);

		if ((value & AML_USB_PHY_ADP_BC_ACA_FLOATING) != 0) {
			device_printf(dev,
			    "force-aca requires newer silicon\n");
			goto fail;
		}
	}

	/*
	 * Reset the hub.
	 */
	if (sc->hub_rst.dev != NULL) {
		err = 0;

		if (GPIO_PIN_SET(sc->hub_rst.dev, sc->hub_rst.pin,
		    PIN_ON_FLAG(sc->hub_rst.pol)) != 0 ||
		    GPIO_PIN_SETFLAGS(sc->hub_rst.dev, sc->hub_rst.pin,
		    GPIO_PIN_OUTPUT) != 0)
			err = 1;

		DELAY(30);

		if (GPIO_PIN_SET(sc->hub_rst.dev, sc->hub_rst.pin,
		    PIN_OFF_FLAG(sc->hub_rst.pol)) != 0)
			err = 1;

		DELAY(60000);

		if (err) {
			device_printf(dev,
			    "could not use gpio to reset hub\n");
			goto fail;
		}
	}

	return (0);

fail:
	/* In the event of problems attempt to turn things back off. */
	i = sc->npwr_en;
	while (i-- != 0) {
		GPIO_PIN_SET(sc->pwr_en[i].dev, sc->pwr_en[i].pin,
		    PIN_OFF_FLAG(sc->pwr_en[i].pol));
	}

	free (sc->pwr_en, M_DEVBUF);
	sc->pwr_en = NULL;

	bus_release_resources(dev, aml8726_usb_phy_spec, sc->res);

	return (ENXIO);
}