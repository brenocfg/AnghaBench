#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mtx; int /*<<< orphan*/ * methods; int /*<<< orphan*/  usbrev; } ;
struct dwc_otg_softc {int sc_mode; int sc_phy_type; int sc_phy_bits; int sc_fifo_size; scalar_t__ sc_dev_ep_max; scalar_t__ sc_host_ch_max; scalar_t__ sc_dev_in_ep_max; int sc_irq_mask; TYPE_1__ sc_bus; int /*<<< orphan*/  sc_timer; } ;

/* Variables and functions */
 int DCTL_CGNPINNAK ; 
 int DCTL_CGOUTNAK ; 
 int DCTL_SFTDISCON ; 
 int DIEPMSK_XFERCOMPLMSK ; 
 int /*<<< orphan*/  DOTG_DAINTMSK ; 
 int /*<<< orphan*/  DOTG_DCTL ; 
 int /*<<< orphan*/  DOTG_DEACHINTMSK ; 
 int /*<<< orphan*/  DOTG_DIEPEACHINTMSK (scalar_t__) ; 
 int /*<<< orphan*/  DOTG_DIEPMSK ; 
 int /*<<< orphan*/  DOTG_DOEPEACHINTMSK (scalar_t__) ; 
 int /*<<< orphan*/  DOTG_DOEPMSK ; 
 int /*<<< orphan*/  DOTG_GAHBCFG ; 
 int /*<<< orphan*/  DOTG_GGPIO ; 
 int DOTG_GGPIO_I2CPADEN ; 
 int DOTG_GGPIO_NOVBUSSENS ; 
 int DOTG_GGPIO_PWRDWN ; 
 int DOTG_GGPIO_VBUSASEN ; 
 int DOTG_GGPIO_VBUSBSEN ; 
 int /*<<< orphan*/  DOTG_GHWCFG2 ; 
 int /*<<< orphan*/  DOTG_GHWCFG3 ; 
 int /*<<< orphan*/  DOTG_GHWCFG4 ; 
 int /*<<< orphan*/  DOTG_GINTMSK ; 
 int /*<<< orphan*/  DOTG_GLPMCFG ; 
 int /*<<< orphan*/  DOTG_GOTGCTL ; 
 int /*<<< orphan*/  DOTG_GRSTCTL ; 
 int /*<<< orphan*/  DOTG_GSNPSID ; 
 int /*<<< orphan*/  DOTG_GUSBCFG ; 
 int /*<<< orphan*/  DOTG_HCFG ; 
 int /*<<< orphan*/  DOTG_PCGCCTL ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
#define  DWC_MODE_DEVICE 133 
#define  DWC_MODE_HOST 132 
 int DWC_MODE_OTG ; 
 scalar_t__ DWC_OTG_MAX_CHANNELS ; 
 scalar_t__ DWC_OTG_MAX_ENDPOINTS ; 
 int DWC_OTG_MSK_GINT_THREAD_IRQ ; 
#define  DWC_OTG_PHY_HSIC 131 
#define  DWC_OTG_PHY_INTERNAL 130 
#define  DWC_OTG_PHY_ULPI 129 
#define  DWC_OTG_PHY_UTMI 128 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int GAHBCFG_GLBLINTRMSK ; 
 int GHWCFG2_MPI ; 
 scalar_t__ GHWCFG2_NUMDEVEPS_GET (int) ; 
 scalar_t__ GHWCFG2_NUMHSTCHNL_GET (int) ; 
 int GHWCFG3_DFIFODEPTH_GET (int) ; 
 scalar_t__ GHWCFG4_NUM_IN_EP_GET (int) ; 
 int GLPMCFG_HSIC_CONN ; 
 int GOTGCTL_ASESVLD ; 
 int GOTGCTL_BSESVLD ; 
 int GRSTCTL_CSFTRST ; 
 int GUSBCFG_FORCEDEVMODE ; 
 int GUSBCFG_FORCEHOSTMODE ; 
 int GUSBCFG_PHYIF ; 
 int GUSBCFG_PHYSEL ; 
 int GUSBCFG_TRD_TIM_SET (int) ; 
 int GUSBCFG_ULPI_UTMI_SEL ; 
 int HCFG_FSLSPCLKSEL_MASK ; 
 int HCFG_FSLSPCLKSEL_SHIFT ; 
 int HCFG_FSLSSUPP ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_REV_2_0 ; 
 int /*<<< orphan*/  dwc_otg_bus_methods ; 
 int /*<<< orphan*/  dwc_otg_clocks_off (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_clocks_on (struct dwc_otg_softc*) ; 
 int /*<<< orphan*/  dwc_otg_do_poll (TYPE_1__*) ; 
 scalar_t__ dwc_otg_init_fifo (struct dwc_otg_softc*,int) ; 
 int dwc_otg_phy_type ; 
 int /*<<< orphan*/  dwc_otg_vbus_interrupt (struct dwc_otg_softc*,int) ; 
 int hz ; 
 int /*<<< orphan*/  usb_callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

int
dwc_otg_init(struct dwc_otg_softc *sc)
{
	uint32_t temp;

	DPRINTF("start\n");

	/* set up the bus structure */
	sc->sc_bus.usbrev = USB_REV_2_0;
	sc->sc_bus.methods = &dwc_otg_bus_methods;

	usb_callout_init_mtx(&sc->sc_timer,
	    &sc->sc_bus.bus_mtx, 0);

	USB_BUS_LOCK(&sc->sc_bus);

	/* turn on clocks */
	dwc_otg_clocks_on(sc);

	temp = DWC_OTG_READ_4(sc, DOTG_GSNPSID);
	DPRINTF("Version = 0x%08x\n", temp);

	/* disconnect */
	DWC_OTG_WRITE_4(sc, DOTG_DCTL,
	    DCTL_SFTDISCON);

	/* wait for host to detect disconnect */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 32);

	DWC_OTG_WRITE_4(sc, DOTG_GRSTCTL,
	    GRSTCTL_CSFTRST);

	/* wait a little bit for block to reset */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 128);

	switch (sc->sc_mode) {
	case DWC_MODE_DEVICE:
		temp = GUSBCFG_FORCEDEVMODE;
		break;
	case DWC_MODE_HOST:
		temp = GUSBCFG_FORCEHOSTMODE;
		break;
	default:
		temp = 0;
		break;
	}

	if (sc->sc_phy_type == 0)
		sc->sc_phy_type = dwc_otg_phy_type + 1;
	if (sc->sc_phy_bits == 0)
		sc->sc_phy_bits = 16;

	/* select HSIC, ULPI, UTMI+ or internal PHY mode */
	switch (sc->sc_phy_type) {
	case DWC_OTG_PHY_HSIC:
		DWC_OTG_WRITE_4(sc, DOTG_GUSBCFG,
		    GUSBCFG_PHYIF |
		    GUSBCFG_TRD_TIM_SET(5) | temp);
		DWC_OTG_WRITE_4(sc, DOTG_GOTGCTL,
		    0x000000EC);

		temp = DWC_OTG_READ_4(sc, DOTG_GLPMCFG);
		DWC_OTG_WRITE_4(sc, DOTG_GLPMCFG,
		    temp & ~GLPMCFG_HSIC_CONN);
		DWC_OTG_WRITE_4(sc, DOTG_GLPMCFG,
		    temp | GLPMCFG_HSIC_CONN);
		break;
	case DWC_OTG_PHY_ULPI:
		DWC_OTG_WRITE_4(sc, DOTG_GUSBCFG,
		    GUSBCFG_ULPI_UTMI_SEL |
		    GUSBCFG_TRD_TIM_SET(5) | temp);
		DWC_OTG_WRITE_4(sc, DOTG_GOTGCTL, 0);

		temp = DWC_OTG_READ_4(sc, DOTG_GLPMCFG);
		DWC_OTG_WRITE_4(sc, DOTG_GLPMCFG,
		    temp & ~GLPMCFG_HSIC_CONN);
		break;
	case DWC_OTG_PHY_UTMI:
		DWC_OTG_WRITE_4(sc, DOTG_GUSBCFG,
		    (sc->sc_phy_bits == 16 ? GUSBCFG_PHYIF : 0) |
		    GUSBCFG_TRD_TIM_SET(5) | temp);
		DWC_OTG_WRITE_4(sc, DOTG_GOTGCTL, 0);

		temp = DWC_OTG_READ_4(sc, DOTG_GLPMCFG);
		DWC_OTG_WRITE_4(sc, DOTG_GLPMCFG,
		    temp & ~GLPMCFG_HSIC_CONN);
		break;
	case DWC_OTG_PHY_INTERNAL:
		DWC_OTG_WRITE_4(sc, DOTG_GUSBCFG,
		    GUSBCFG_PHYSEL |
		    GUSBCFG_TRD_TIM_SET(5) | temp);
		DWC_OTG_WRITE_4(sc, DOTG_GOTGCTL, 0);

		temp = DWC_OTG_READ_4(sc, DOTG_GLPMCFG);
		DWC_OTG_WRITE_4(sc, DOTG_GLPMCFG,
		    temp & ~GLPMCFG_HSIC_CONN);

		temp = DWC_OTG_READ_4(sc, DOTG_GGPIO);
		temp &= ~(DOTG_GGPIO_NOVBUSSENS | DOTG_GGPIO_I2CPADEN);
		temp |= (DOTG_GGPIO_VBUSASEN | DOTG_GGPIO_VBUSBSEN |
		    DOTG_GGPIO_PWRDWN);
		DWC_OTG_WRITE_4(sc, DOTG_GGPIO, temp);
		break;
	default:
		break;
	}

	/* clear global nak */
	DWC_OTG_WRITE_4(sc, DOTG_DCTL,
	    DCTL_CGOUTNAK |
	    DCTL_CGNPINNAK);

	/* disable USB port */
	DWC_OTG_WRITE_4(sc, DOTG_PCGCCTL, 0xFFFFFFFF);

	/* wait 10ms */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 100);

	/* enable USB port */
	DWC_OTG_WRITE_4(sc, DOTG_PCGCCTL, 0);

	/* wait 10ms */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 100);

	temp = DWC_OTG_READ_4(sc, DOTG_GHWCFG3);

	sc->sc_fifo_size = 4 * GHWCFG3_DFIFODEPTH_GET(temp);

	temp = DWC_OTG_READ_4(sc, DOTG_GHWCFG2);

	sc->sc_dev_ep_max = GHWCFG2_NUMDEVEPS_GET(temp);

	if (sc->sc_dev_ep_max > DWC_OTG_MAX_ENDPOINTS)
		sc->sc_dev_ep_max = DWC_OTG_MAX_ENDPOINTS;

	sc->sc_host_ch_max = GHWCFG2_NUMHSTCHNL_GET(temp);

	if (sc->sc_host_ch_max > DWC_OTG_MAX_CHANNELS)
		sc->sc_host_ch_max = DWC_OTG_MAX_CHANNELS;

	temp = DWC_OTG_READ_4(sc, DOTG_GHWCFG4);

	sc->sc_dev_in_ep_max = GHWCFG4_NUM_IN_EP_GET(temp);

	DPRINTF("Total FIFO size = %d bytes, Device EPs = %d/%d Host CHs = %d\n",
	    sc->sc_fifo_size, sc->sc_dev_ep_max, sc->sc_dev_in_ep_max,
	    sc->sc_host_ch_max);

	/* setup FIFO */
	if (dwc_otg_init_fifo(sc, sc->sc_mode)) {
		USB_BUS_UNLOCK(&sc->sc_bus);
		return (EINVAL);
	}

	/* enable interrupts */
	sc->sc_irq_mask |= DWC_OTG_MSK_GINT_THREAD_IRQ;
	DWC_OTG_WRITE_4(sc, DOTG_GINTMSK, sc->sc_irq_mask);

	if (sc->sc_mode == DWC_MODE_OTG || sc->sc_mode == DWC_MODE_DEVICE) {

		/* enable all endpoint interrupts */
		temp = DWC_OTG_READ_4(sc, DOTG_GHWCFG2);
		if (temp & GHWCFG2_MPI) {
			uint8_t x;

			DPRINTF("Disable Multi Process Interrupts\n");

			for (x = 0; x != sc->sc_dev_in_ep_max; x++) {
				DWC_OTG_WRITE_4(sc, DOTG_DIEPEACHINTMSK(x), 0);
				DWC_OTG_WRITE_4(sc, DOTG_DOEPEACHINTMSK(x), 0);
			}
			DWC_OTG_WRITE_4(sc, DOTG_DEACHINTMSK, 0);
		}
		DWC_OTG_WRITE_4(sc, DOTG_DIEPMSK,
		    DIEPMSK_XFERCOMPLMSK);
		DWC_OTG_WRITE_4(sc, DOTG_DOEPMSK, 0);
		DWC_OTG_WRITE_4(sc, DOTG_DAINTMSK, 0xFFFF);
	}

	if (sc->sc_mode == DWC_MODE_OTG || sc->sc_mode == DWC_MODE_HOST) {
		/* setup clocks */
		temp = DWC_OTG_READ_4(sc, DOTG_HCFG);
		temp &= ~(HCFG_FSLSSUPP | HCFG_FSLSPCLKSEL_MASK);
		temp |= (1 << HCFG_FSLSPCLKSEL_SHIFT);
		DWC_OTG_WRITE_4(sc, DOTG_HCFG, temp);
	}

	/* only enable global IRQ */
	DWC_OTG_WRITE_4(sc, DOTG_GAHBCFG,
	    GAHBCFG_GLBLINTRMSK);

	/* turn off clocks */
	dwc_otg_clocks_off(sc);

	/* read initial VBUS state */

	temp = DWC_OTG_READ_4(sc, DOTG_GOTGCTL);

	DPRINTFN(5, "GOTCTL=0x%08x\n", temp);

	dwc_otg_vbus_interrupt(sc,
	    (temp & (GOTGCTL_ASESVLD | GOTGCTL_BSESVLD)) ? 1 : 0);

	USB_BUS_UNLOCK(&sc->sc_bus);

	/* catch any lost interrupts */

	dwc_otg_do_poll(&sc->sc_bus);

	return (0);			/* success */
}