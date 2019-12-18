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
struct aml8726_usb_phy_softc {int npwr_en; int /*<<< orphan*/  res; struct aml8726_usb_phy_gpio* pwr_en; int /*<<< orphan*/  dev; } ;
struct aml8726_usb_phy_gpio {void* pol; void* pin; int /*<<< orphan*/ * dev; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  void* pcell_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AML_USB_PHY_CFG_A_PHYS_RST ; 
 int AML_USB_PHY_CFG_A_PLL_RST ; 
 int AML_USB_PHY_CFG_A_POR ; 
 int AML_USB_PHY_CFG_A_RST ; 
 int AML_USB_PHY_CFG_B_PHYS_RST ; 
 int AML_USB_PHY_CFG_B_PLL_RST ; 
 int AML_USB_PHY_CFG_B_POR ; 
 int AML_USB_PHY_CFG_B_RST ; 
 int AML_USB_PHY_CFG_CLK_DETECTED ; 
 int AML_USB_PHY_CFG_CLK_DIV_MASK ; 
 int AML_USB_PHY_CFG_CLK_DIV_SHIFT ; 
 int AML_USB_PHY_CFG_CLK_EN ; 
 int AML_USB_PHY_CFG_CLK_SEL_MASK ; 
 int AML_USB_PHY_CFG_CLK_SEL_XTAL ; 
 int /*<<< orphan*/  AML_USB_PHY_CFG_REG ; 
 int /*<<< orphan*/  AML_USB_PHY_MISC_A_REG ; 
 int /*<<< orphan*/  AML_USB_PHY_MISC_B_REG ; 
 int AML_USB_PHY_MISC_ID_OVERIDE_DEVICE ; 
 int AML_USB_PHY_MISC_ID_OVERIDE_EN ; 
 int AML_USB_PHY_MISC_ID_OVERIDE_HOST ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 scalar_t__ GPIO_PIN_SET (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/ * OF_device_from_xref (void*) ; 
 scalar_t__ OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char*,int,void**) ; 
 int /*<<< orphan*/  OF_prop_free (void**) ; 
 int /*<<< orphan*/  PIN_OFF_FLAG (void*) ; 
 int /*<<< orphan*/  PIN_ON_FLAG (void*) ; 
 scalar_t__ aml8726_usb_phy_mode (char*,int*) ; 
 int /*<<< orphan*/  aml8726_usb_phy_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_usb_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct aml8726_usb_phy_gpio*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_usb_phy_attach(device_t dev)
{
	struct aml8726_usb_phy_softc *sc = device_get_softc(dev);
	int err;
	int npwr_en;
	pcell_t *prop;
	phandle_t node;
	ssize_t len;
	uint32_t div;
	uint32_t i;
	uint32_t mode_a;
	uint32_t mode_b;
	uint32_t value;

	sc->dev = dev;

	if (aml8726_usb_phy_mode("/soc/usb@c9040000", &mode_a) != 0) {
		device_printf(dev, "missing usb@c9040000 node in FDT\n");
		return (ENXIO);
	}

	if (aml8726_usb_phy_mode("/soc/usb@c90c0000", &mode_b) != 0) {
		device_printf(dev, "missing usb@c90c0000 node in FDT\n");
		return (ENXIO);
	}

	if (bus_alloc_resources(dev, aml8726_usb_phy_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	node = ofw_bus_get_node(dev);

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

	div = 2;

	value = CSR_READ_4(sc, AML_USB_PHY_CFG_REG);

	value &= ~(AML_USB_PHY_CFG_CLK_DIV_MASK | AML_USB_PHY_CFG_CLK_SEL_MASK);

	value &= ~(AML_USB_PHY_CFG_A_RST | AML_USB_PHY_CFG_B_RST);
	value &= ~(AML_USB_PHY_CFG_A_PLL_RST | AML_USB_PHY_CFG_B_PLL_RST);
	value &= ~(AML_USB_PHY_CFG_A_PHYS_RST | AML_USB_PHY_CFG_B_PHYS_RST);
	value &= ~(AML_USB_PHY_CFG_A_POR | AML_USB_PHY_CFG_B_POR);

	value |= AML_USB_PHY_CFG_CLK_SEL_XTAL;
	value |= ((div - 1) << AML_USB_PHY_CFG_CLK_DIV_SHIFT) &
	    AML_USB_PHY_CFG_CLK_DIV_MASK;
	value |= AML_USB_PHY_CFG_CLK_EN;

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	/*
	 * Issue the reset sequence.
	 */

	value |= (AML_USB_PHY_CFG_A_RST | AML_USB_PHY_CFG_B_RST);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	value &= ~(AML_USB_PHY_CFG_A_RST | AML_USB_PHY_CFG_B_RST);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	value |= (AML_USB_PHY_CFG_A_PLL_RST | AML_USB_PHY_CFG_B_PLL_RST);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	value &= ~(AML_USB_PHY_CFG_A_PLL_RST | AML_USB_PHY_CFG_B_PLL_RST);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	value |= (AML_USB_PHY_CFG_A_PHYS_RST | AML_USB_PHY_CFG_B_PHYS_RST);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	value &= ~(AML_USB_PHY_CFG_A_PHYS_RST | AML_USB_PHY_CFG_B_PHYS_RST);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	value |= (AML_USB_PHY_CFG_A_POR | AML_USB_PHY_CFG_B_POR);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);
	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	/*
	 * Enable by clearing the power on reset.
	 */

	value &= ~(AML_USB_PHY_CFG_A_POR | AML_USB_PHY_CFG_B_POR);

	CSR_WRITE_4(sc, AML_USB_PHY_CFG_REG, value);

	CSR_BARRIER(sc, AML_USB_PHY_CFG_REG);

	DELAY(200);

	/*
	 * Check if the clock was detected.
	 */
	value = CSR_READ_4(sc, AML_USB_PHY_CFG_REG);
	if ((value & AML_USB_PHY_CFG_CLK_DETECTED) !=
	    AML_USB_PHY_CFG_CLK_DETECTED)
		device_printf(dev, "PHY Clock not detected\n");

	/*
	 * Configure the mode for each port.
	 */

	value = CSR_READ_4(sc, AML_USB_PHY_MISC_A_REG);

	value &= ~(AML_USB_PHY_MISC_ID_OVERIDE_EN |
	    AML_USB_PHY_MISC_ID_OVERIDE_DEVICE |
	    AML_USB_PHY_MISC_ID_OVERIDE_HOST);
	value |= mode_a;

	CSR_WRITE_4(sc, AML_USB_PHY_MISC_A_REG, value);

	value = CSR_READ_4(sc, AML_USB_PHY_MISC_B_REG);

	value &= ~(AML_USB_PHY_MISC_ID_OVERIDE_EN |
	    AML_USB_PHY_MISC_ID_OVERIDE_DEVICE |
	    AML_USB_PHY_MISC_ID_OVERIDE_HOST);
	value |= mode_b;

	CSR_WRITE_4(sc, AML_USB_PHY_MISC_B_REG, value);

	CSR_BARRIER(sc, AML_USB_PHY_MISC_B_REG);

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