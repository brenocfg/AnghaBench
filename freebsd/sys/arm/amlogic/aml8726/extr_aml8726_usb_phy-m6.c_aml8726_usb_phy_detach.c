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
typedef  size_t uint32_t ;
struct aml8726_usb_phy_softc {size_t npwr_en; int /*<<< orphan*/  res; TYPE_1__* pwr_en; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  pol; int /*<<< orphan*/  pin; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t AML_USB_PHY_CTRL_POR ; 
 int /*<<< orphan*/  AML_USB_PHY_CTRL_REG ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ) ; 
 size_t CSR_READ_4 (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_usb_phy_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  GPIO_PIN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PIN_OFF_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_usb_phy_spec ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aml8726_usb_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_usb_phy_detach(device_t dev)
{
	struct aml8726_usb_phy_softc *sc = device_get_softc(dev);
	uint32_t i;
	uint32_t value;

	/*
	 * Disable by issuing a power on reset.
	 */

	value = CSR_READ_4(sc, AML_USB_PHY_CTRL_REG);

	value |= AML_USB_PHY_CTRL_POR;

	CSR_WRITE_4(sc, AML_USB_PHY_CTRL_REG, value);

	CSR_BARRIER(sc, AML_USB_PHY_CTRL_REG);

	/* Turn off power */
	i = sc->npwr_en;
	while (i-- != 0) {
		GPIO_PIN_SET(sc->pwr_en[i].dev, sc->pwr_en[i].pin,
		    PIN_OFF_FLAG(sc->pwr_en[i].pol));
	}
	free (sc->pwr_en, M_DEVBUF);
	sc->pwr_en = NULL;

	bus_release_resources(dev, aml8726_usb_phy_spec, sc->res);

	return (0);
}