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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint32_t ;
struct usb_hw_ep_profile {unsigned int max_in_frame_size; unsigned int max_out_frame_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mtx; int /*<<< orphan*/ * methods; int /*<<< orphan*/  usbrev; } ;
struct saf1761_otg_softc {int sc_hw_mode; int sc_interrupt_cfg; int sc_intr_enable; TYPE_1__ sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 unsigned int SAF1761_READ_LE_4 (struct saf1761_otg_softc*,int) ; 
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int,unsigned int) ; 
 int SOTG_ADDRESS ; 
 int SOTG_ATL_IRQ_MASK_AND ; 
 int SOTG_ATL_IRQ_MASK_OR ; 
 int SOTG_ATL_PTD_LAST_PTD ; 
 int SOTG_ATL_PTD_SKIP_PTD ; 
 int SOTG_CONFIGFLAG ; 
 unsigned int SOTG_CONFIGFLAG_ENABLE ; 
 int SOTG_CTRL_BDIS_ACON_EN ; 
 unsigned int SOTG_CTRL_CLR (int) ; 
 int SOTG_CTRL_SEL_CP_EXT ; 
 unsigned int SOTG_CTRL_SET (int) ; 
 int SOTG_CTRL_SET_CLR ; 
 int SOTG_CTRL_SW_SEL_HC_DC ; 
 int SOTG_CTRL_VBUS_DRV ; 
 int SOTG_DCCHIP_ID ; 
 int SOTG_DCINTERRUPT_EN ; 
 int SOTG_DCINTERRUPT_IEBRST ; 
 int SOTG_DCINTERRUPT_IESUSP ; 
 int SOTG_DCINTERRUPT_IEVBUS ; 
 int SOTG_DCSCRATCH ; 
 int SOTG_EP_INDEX ; 
 int SOTG_EP_INDEX_DIR_IN ; 
 int SOTG_EP_INDEX_DIR_OUT ; 
 int SOTG_EP_INDEX_ENDP_INDEX_SHIFT ; 
 int SOTG_EP_MAXPACKET ; 
 int SOTG_HCBUFFERSTATUS ; 
 unsigned int SOTG_HCBUFFERSTATUS_ATL_BUF_FILL ; 
 unsigned int SOTG_HCBUFFERSTATUS_INT_BUF_FILL ; 
 unsigned int SOTG_HCBUFFERSTATUS_ISO_BUF_FILL ; 
 unsigned int SOTG_HCINTERRUPT_ALT_IRQ ; 
 int SOTG_HCINTERRUPT_ENABLE ; 
 unsigned int SOTG_HCINTERRUPT_INT_IRQ ; 
 unsigned int SOTG_HCINTERRUPT_ISO_IRQ ; 
 unsigned int SOTG_HCINTERRUPT_OTG_IRQ ; 
 int SOTG_HCSCRATCH ; 
 int SOTG_HW_MODE_CTRL ; 
 unsigned int SOTG_HW_MODE_CTRL_ALL_ATX_RESET ; 
 int SOTG_HW_MODE_CTRL_COMN_INT ; 
 int SOTG_HW_MODE_CTRL_GLOBAL_INTR_EN ; 
 int SOTG_INTERRUPT_CFG ; 
 int SOTG_INTERRUPT_CFG_CDBGMOD ; 
 int SOTG_INTERRUPT_CFG_DDBGMODIN ; 
 int SOTG_INTERRUPT_CFG_DDBGMODOUT ; 
 int SOTG_INT_IRQ_MASK_AND ; 
 int SOTG_INT_IRQ_MASK_OR ; 
 int SOTG_INT_PTD_LAST_PTD ; 
 int SOTG_INT_PTD_SKIP_PTD ; 
 unsigned int SOTG_IRQ_ENABLE_CLR (int) ; 
 unsigned int SOTG_IRQ_ENABLE_SET (int) ; 
 int SOTG_IRQ_ENABLE_SET_CLR ; 
 int SOTG_IRQ_ID ; 
 int SOTG_IRQ_VBUS_VLD ; 
 int SOTG_ISO_IRQ_MASK_AND ; 
 int SOTG_ISO_IRQ_MASK_OR ; 
 int SOTG_ISO_PTD_LAST_PTD ; 
 int SOTG_ISO_PTD_SKIP_PTD ; 
 int SOTG_MODE ; 
 unsigned int SOTG_MODE_CLKAON ; 
 unsigned int SOTG_MODE_GLINTENA ; 
 unsigned int SOTG_MODE_SFRESET ; 
 unsigned int SOTG_MODE_WKUPCS ; 
 int SOTG_POWER_DOWN ; 
 int SOTG_POWER_DOWN_HC_CLK_EN ; 
 int SOTG_SW_RESET ; 
 unsigned int SOTG_SW_RESET_ALL ; 
 unsigned int SOTG_SW_RESET_HC ; 
 int SOTG_UNLOCK_DEVICE ; 
 unsigned int SOTG_UNLOCK_DEVICE_CODE ; 
 int SOTG_USBCMD ; 
 unsigned int SOTG_USBCMD_HCRESET ; 
 unsigned int SOTG_USBCMD_RS ; 
 int SOTG_VEND_PROD_ID ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  USB_REV_2_0 ; 
 int hz ; 
 int /*<<< orphan*/  saf1761_otg_bus_methods ; 
 int /*<<< orphan*/  saf1761_otg_do_poll (TYPE_1__*) ; 
 int /*<<< orphan*/  saf1761_otg_get_hw_ep_profile (int /*<<< orphan*/ *,struct usb_hw_ep_profile const**,int) ; 
 int /*<<< orphan*/  saf1761_otg_pull_down (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  saf1761_otg_update_vbus (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

usb_error_t
saf1761_otg_init(struct saf1761_otg_softc *sc)
{
	const struct usb_hw_ep_profile *pf;
	uint32_t x;

	DPRINTF("\n");

	/* set up the bus structure */
	sc->sc_bus.usbrev = USB_REV_2_0;
	sc->sc_bus.methods = &saf1761_otg_bus_methods;

	USB_BUS_LOCK(&sc->sc_bus);

	/* Reset Host controller, including HW mode */
	SAF1761_WRITE_LE_4(sc, SOTG_SW_RESET, SOTG_SW_RESET_ALL);

	DELAY(1000);

	/* Reset Host controller, including HW mode */
	SAF1761_WRITE_LE_4(sc, SOTG_SW_RESET, SOTG_SW_RESET_HC);

	/* wait a bit */
	DELAY(1000);

	SAF1761_WRITE_LE_4(sc, SOTG_SW_RESET, 0);

	/* wait a bit */
	DELAY(1000);

	/* Enable interrupts */
	sc->sc_hw_mode |= SOTG_HW_MODE_CTRL_GLOBAL_INTR_EN |
	    SOTG_HW_MODE_CTRL_COMN_INT;

	/* unlock device */
	SAF1761_WRITE_LE_4(sc, SOTG_UNLOCK_DEVICE, SOTG_UNLOCK_DEVICE_CODE);

	/*
	 * Set correct hardware mode, must be written twice if bus
	 * width is changed:
	 */
	SAF1761_WRITE_LE_4(sc, SOTG_HW_MODE_CTRL, sc->sc_hw_mode);
	SAF1761_WRITE_LE_4(sc, SOTG_HW_MODE_CTRL, sc->sc_hw_mode);

	SAF1761_WRITE_LE_4(sc, SOTG_DCSCRATCH, 0xdeadbeef);
	SAF1761_WRITE_LE_4(sc, SOTG_HCSCRATCH, 0xdeadbeef);

	DPRINTF("DCID=0x%08x VEND_PROD=0x%08x HWMODE=0x%08x SCRATCH=0x%08x,0x%08x\n",
	    SAF1761_READ_LE_4(sc, SOTG_DCCHIP_ID),
	    SAF1761_READ_LE_4(sc, SOTG_VEND_PROD_ID),
	    SAF1761_READ_LE_4(sc, SOTG_HW_MODE_CTRL),
	    SAF1761_READ_LE_4(sc, SOTG_DCSCRATCH),
	    SAF1761_READ_LE_4(sc, SOTG_HCSCRATCH));

	/* reset device controller */
	SAF1761_WRITE_LE_4(sc, SOTG_MODE, SOTG_MODE_SFRESET);
	SAF1761_WRITE_LE_4(sc, SOTG_MODE, 0);

	/* wait a bit */
	DELAY(1000);

	/* reset host controller */
	SAF1761_WRITE_LE_4(sc, SOTG_USBCMD, SOTG_USBCMD_HCRESET);

	/* wait for reset to clear */
	for (x = 0; x != 10; x++) {
		if ((SAF1761_READ_LE_4(sc, SOTG_USBCMD) & SOTG_USBCMD_HCRESET) == 0)
			break;
		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 10);
	}

	SAF1761_WRITE_LE_4(sc, SOTG_HW_MODE_CTRL, sc->sc_hw_mode |
	    SOTG_HW_MODE_CTRL_ALL_ATX_RESET);

	/* wait a bit */
	DELAY(1000);

	SAF1761_WRITE_LE_4(sc, SOTG_HW_MODE_CTRL, sc->sc_hw_mode);

	/* wait a bit */
	DELAY(1000);

	/* do a pulldown */
	saf1761_otg_pull_down(sc);

	/* wait 10ms for pulldown to stabilise */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 100);

	for (x = 1;; x++) {

		saf1761_otg_get_hw_ep_profile(NULL, &pf, x);
		if (pf == NULL)
			break;

		/* select the correct endpoint */
		SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX,
		    (x << SOTG_EP_INDEX_ENDP_INDEX_SHIFT) |
		    SOTG_EP_INDEX_DIR_IN);

		/* select the maximum packet size */
		SAF1761_WRITE_LE_4(sc, SOTG_EP_MAXPACKET, pf->max_in_frame_size);

		/* select the correct endpoint */
		SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX,
		    (x << SOTG_EP_INDEX_ENDP_INDEX_SHIFT) |
		    SOTG_EP_INDEX_DIR_OUT);

		/* select the maximum packet size */
		SAF1761_WRITE_LE_4(sc, SOTG_EP_MAXPACKET, pf->max_out_frame_size);
	}

	/* enable interrupts */
	SAF1761_WRITE_LE_4(sc, SOTG_MODE, SOTG_MODE_GLINTENA |
	    SOTG_MODE_CLKAON | SOTG_MODE_WKUPCS);

	sc->sc_interrupt_cfg |=
	    SOTG_INTERRUPT_CFG_CDBGMOD |
	    SOTG_INTERRUPT_CFG_DDBGMODIN |
	    SOTG_INTERRUPT_CFG_DDBGMODOUT;

	/* set default values */
	SAF1761_WRITE_LE_4(sc, SOTG_INTERRUPT_CFG, sc->sc_interrupt_cfg);

	/* enable VBUS and ID interrupt */
	SAF1761_WRITE_LE_4(sc, SOTG_IRQ_ENABLE_SET_CLR,
	    SOTG_IRQ_ENABLE_CLR(0xFFFF));
	SAF1761_WRITE_LE_4(sc, SOTG_IRQ_ENABLE_SET_CLR,
	    SOTG_IRQ_ENABLE_SET(SOTG_IRQ_ID | SOTG_IRQ_VBUS_VLD));

	/* enable interrupts */
	sc->sc_intr_enable = SOTG_DCINTERRUPT_IEVBUS |
	    SOTG_DCINTERRUPT_IEBRST | SOTG_DCINTERRUPT_IESUSP;
	SAF1761_WRITE_LE_4(sc, SOTG_DCINTERRUPT_EN, sc->sc_intr_enable);

	/*
	 * Connect ATX port 1 to device controller, select external
	 * charge pump and driver VBUS to +5V:
	 */
	SAF1761_WRITE_LE_4(sc, SOTG_CTRL_SET_CLR,
	    SOTG_CTRL_CLR(0xFFFF));
#ifdef __rtems__
	SAF1761_WRITE_LE_4(sc, SOTG_CTRL_SET_CLR,
	    SOTG_CTRL_SET(SOTG_CTRL_SEL_CP_EXT | SOTG_CTRL_VBUS_DRV));
#else
	SAF1761_WRITE_LE_4(sc, SOTG_CTRL_SET_CLR,
	    SOTG_CTRL_SET(SOTG_CTRL_SW_SEL_HC_DC |
	    SOTG_CTRL_BDIS_ACON_EN | SOTG_CTRL_SEL_CP_EXT |
	    SOTG_CTRL_VBUS_DRV));
#endif
	/* disable device address */
	SAF1761_WRITE_LE_4(sc, SOTG_ADDRESS, 0);

	/* enable host controller clock and preserve reserved bits */
	x = SAF1761_READ_LE_4(sc, SOTG_POWER_DOWN);
	SAF1761_WRITE_LE_4(sc, SOTG_POWER_DOWN, x | SOTG_POWER_DOWN_HC_CLK_EN);

	/* wait 10ms for clock */
	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 100);

	/* enable configuration flag */
	SAF1761_WRITE_LE_4(sc, SOTG_CONFIGFLAG, SOTG_CONFIGFLAG_ENABLE);

	/* clear RAM block */
	for (x = 0x400; x != 0x10000; x += 4)
		SAF1761_WRITE_LE_4(sc, x, 0);

	/* start the HC */
	SAF1761_WRITE_LE_4(sc, SOTG_USBCMD, SOTG_USBCMD_RS);

	DPRINTF("USBCMD=0x%08x\n", SAF1761_READ_LE_4(sc, SOTG_USBCMD));

	/* make HC scan all PTDs */
	SAF1761_WRITE_LE_4(sc, SOTG_ATL_PTD_LAST_PTD, (1 << 31));
	SAF1761_WRITE_LE_4(sc, SOTG_INT_PTD_LAST_PTD, (1 << 31));
	SAF1761_WRITE_LE_4(sc, SOTG_ISO_PTD_LAST_PTD, (1 << 31));

	/* skip all PTDs by default */
	SAF1761_WRITE_LE_4(sc, SOTG_ATL_PTD_SKIP_PTD, -1U);
	SAF1761_WRITE_LE_4(sc, SOTG_INT_PTD_SKIP_PTD, -1U);
	SAF1761_WRITE_LE_4(sc, SOTG_ISO_PTD_SKIP_PTD, -1U);

	/* activate all PTD types */
	SAF1761_WRITE_LE_4(sc, SOTG_HCBUFFERSTATUS,
	    SOTG_HCBUFFERSTATUS_ISO_BUF_FILL |
	    SOTG_HCBUFFERSTATUS_INT_BUF_FILL |
	    SOTG_HCBUFFERSTATUS_ATL_BUF_FILL);

	/* we don't use the AND mask */
	SAF1761_WRITE_LE_4(sc, SOTG_ISO_IRQ_MASK_AND, 0);
	SAF1761_WRITE_LE_4(sc, SOTG_INT_IRQ_MASK_AND, 0);
	SAF1761_WRITE_LE_4(sc, SOTG_ATL_IRQ_MASK_AND, 0);

	/* enable all PTD OR interrupts by default */
	SAF1761_WRITE_LE_4(sc, SOTG_ISO_IRQ_MASK_OR, -1U);
	SAF1761_WRITE_LE_4(sc, SOTG_INT_IRQ_MASK_OR, -1U);
	SAF1761_WRITE_LE_4(sc, SOTG_ATL_IRQ_MASK_OR, -1U);

	/* enable HC interrupts */
	SAF1761_WRITE_LE_4(sc, SOTG_HCINTERRUPT_ENABLE,
	    SOTG_HCINTERRUPT_OTG_IRQ |
	    SOTG_HCINTERRUPT_ISO_IRQ |
	    SOTG_HCINTERRUPT_ALT_IRQ |
	    SOTG_HCINTERRUPT_INT_IRQ);

	/* poll initial VBUS status */
	saf1761_otg_update_vbus(sc);

	USB_BUS_UNLOCK(&sc->sc_bus);

	/* catch any lost interrupts */

	saf1761_otg_do_poll(&sc->sc_bus);

	return (0);			/* success */
}