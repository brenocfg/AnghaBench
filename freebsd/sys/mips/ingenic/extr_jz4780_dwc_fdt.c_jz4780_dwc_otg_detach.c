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
struct jz4780_dwc_otg_softc {scalar_t__ phy_clk; scalar_t__ otg_clk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  clk_release (scalar_t__) ; 
 struct jz4780_dwc_otg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dwc_otg_detach (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_dwc_otg_detach(device_t dev)
{
	struct jz4780_dwc_otg_softc *sc;
	int err;

	err = dwc_otg_detach(dev);
	if (err != 0)
		return (err);

	sc = device_get_softc(dev);
	if (sc->otg_clk)
		clk_release(sc->otg_clk);
	if (sc->phy_clk)
		clk_release(sc->phy_clk);
	return (0);
}