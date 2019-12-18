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
struct usbphy_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct usbphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_ccm_usbphy_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
usbphy_attach(device_t dev)
{
	struct usbphy_softc *sc;

	sc = device_get_softc(dev);

	/*
         * Turn on the phy clocks.
         */
	imx_ccm_usbphy_enable(dev);

	return (0);
}