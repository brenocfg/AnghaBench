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
struct phy_list {int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;
struct hwrst_list {int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;
struct generic_ehci_fdt_softc {int /*<<< orphan*/  phy_list; int /*<<< orphan*/  rst_list; int /*<<< orphan*/  clk_list; } ;
struct clk_list {int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; } ;
typedef  int /*<<< orphan*/  phy_t ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PHY_USB_MODE_HOST ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct phy_list*,int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 struct generic_ehci_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int generic_ehci_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_ehci_fdt_detach (int /*<<< orphan*/ ) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct phy_list* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int phy_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ phy_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int phy_usb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
generic_ehci_fdt_attach(device_t dev)
{
	int err;
#ifdef EXT_RESOURCES
	struct generic_ehci_fdt_softc *sc;
	struct clk_list *clkp;
	clk_t clk;
	struct hwrst_list *rstp;
	hwreset_t rst;
	struct phy_list *phyp;
	phy_t phy;
	int off;

	sc = device_get_softc(dev);

	TAILQ_INIT(&sc->clk_list);
	/* Enable clock */
	for (off = 0; clk_get_by_ofw_index(dev, 0, off, &clk) == 0; off++) {
		err = clk_enable(clk);
		if (err != 0) {
			device_printf(dev, "Could not enable clock %s\n",
			    clk_get_name(clk));
			goto error;
		}
		clkp = malloc(sizeof(*clkp), M_DEVBUF, M_WAITOK | M_ZERO);
		clkp->clk = clk;
		TAILQ_INSERT_TAIL(&sc->clk_list, clkp, next);
	}

	/* De-assert reset */
	TAILQ_INIT(&sc->rst_list);
	for (off = 0; hwreset_get_by_ofw_idx(dev, 0, off, &rst) == 0; off++) {
		err = hwreset_deassert(rst);
		if (err != 0) {
			device_printf(dev, "Could not de-assert reset\n");
			goto error;
		}
		rstp = malloc(sizeof(*rstp), M_DEVBUF, M_WAITOK | M_ZERO);
		rstp->rst = rst;
		TAILQ_INSERT_TAIL(&sc->rst_list, rstp, next);
	}

	/* Enable USB PHY */
	TAILQ_INIT(&sc->phy_list);
	for (off = 0; phy_get_by_ofw_idx(dev, 0, off, &phy) == 0; off++) {
		err = phy_usb_set_mode(phy, PHY_USB_MODE_HOST);
		if (err != 0) {
			device_printf(dev, "Could not set phy to host mode\n");
			goto error;
		}
		err = phy_enable(phy);
		if (err != 0) {
			device_printf(dev, "Could not enable phy\n");
			goto error;
		}
		phyp = malloc(sizeof(*phyp), M_DEVBUF, M_WAITOK | M_ZERO);
		phyp->phy = phy;
		TAILQ_INSERT_TAIL(&sc->phy_list, phyp, next);
	}
#endif

	err = generic_ehci_attach(dev);
	if (err != 0)
		goto error;

	return (0);

error:
	generic_ehci_fdt_detach(dev);
	return (err);
}