#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int u_char ;
struct sis_softc {scalar_t__ sis_type; scalar_t__ sis_rev; int sis_srr; int /*<<< orphan*/  sis_intrhand; int /*<<< orphan*/ * sis_res; int /*<<< orphan*/  sis_miibus; int /*<<< orphan*/  sis_dev; struct ifnet* sis_ifp; int /*<<< orphan*/  sis_mtx; int /*<<< orphan*/  sis_stat_ch; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct sis_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOSPC ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFCAP_POLLING ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int /*<<< orphan*/  IFCAP_WOL ; 
 int /*<<< orphan*/  IFCAP_WOL_MAGIC ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  NS_EE_NODEADDR ; 
 int /*<<< orphan*/  NS_SRR ; 
 int NS_SRR_15C ; 
 int NS_SRR_15D ; 
 int NS_SRR_16A ; 
#define  NS_VENDORID 129 
 int /*<<< orphan*/  PCIR_REVID ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int /*<<< orphan*/  SIO_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIS_CFG_PERR_DETECT ; 
 int /*<<< orphan*/  SIS_CFG_RND_CNT ; 
 scalar_t__ SIS_DEVICEID_7016 ; 
 scalar_t__ SIS_DEVICEID_900 ; 
 int /*<<< orphan*/  SIS_EECMD_DONE ; 
 int SIS_EECMD_GNT ; 
 int /*<<< orphan*/  SIS_EECMD_REQ ; 
 int /*<<< orphan*/  SIS_EECTL ; 
 int /*<<< orphan*/  SIS_EECTL_CLK ; 
 int /*<<< orphan*/  SIS_EE_NODEADDR ; 
 scalar_t__ SIS_REV_630E ; 
 scalar_t__ SIS_REV_630EA1 ; 
 scalar_t__ SIS_REV_630ET ; 
 scalar_t__ SIS_REV_630S ; 
 scalar_t__ SIS_REV_635 ; 
 scalar_t__ SIS_REV_900B ; 
 scalar_t__ SIS_REV_96x ; 
 int SIS_TIMEOUT ; 
 scalar_t__ SIS_TX_LIST_CNT ; 
 scalar_t__ SIS_TYPE_7016 ; 
 scalar_t__ SIS_TYPE_83815 ; 
 scalar_t__ SIS_TYPE_900 ; 
#define  SIS_VENDORID 128 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sis_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct sis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sis_add_sysctls (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_detach (int /*<<< orphan*/ ) ; 
 int sis_dma_alloc (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_eeprom_idle (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_ifmedia_sts ; 
 int /*<<< orphan*/  sis_ifmedia_upd ; 
 int /*<<< orphan*/  sis_init ; 
 int /*<<< orphan*/  sis_intr ; 
 int /*<<< orphan*/  sis_ioctl ; 
 int /*<<< orphan*/  sis_read_cmos (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sis_read_eeprom (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis_read_mac (struct sis_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis_res_spec ; 
 int /*<<< orphan*/  sis_reset (struct sis_softc*) ; 
 int sis_reverse (int) ; 
 int /*<<< orphan*/  sis_start ; 

__attribute__((used)) static int
sis_attach(device_t dev)
{
	u_char			eaddr[ETHER_ADDR_LEN];
	struct sis_softc	*sc;
	struct ifnet		*ifp;
	int			error = 0, pmc, waittime = 0;

	waittime = 0;
	sc = device_get_softc(dev);

	sc->sis_dev = dev;

	mtx_init(&sc->sis_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->sis_stat_ch, &sc->sis_mtx, 0);

	if (pci_get_device(dev) == SIS_DEVICEID_900)
		sc->sis_type = SIS_TYPE_900;
	if (pci_get_device(dev) == SIS_DEVICEID_7016)
		sc->sis_type = SIS_TYPE_7016;
	if (pci_get_vendor(dev) == NS_VENDORID)
		sc->sis_type = SIS_TYPE_83815;

	sc->sis_rev = pci_read_config(dev, PCIR_REVID, 1);
	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	error = bus_alloc_resources(dev, sis_res_spec, sc->sis_res);
	if (error) {
		device_printf(dev, "couldn't allocate resources\n");
		goto fail;
	}

	/* Reset the adapter. */
	sis_reset(sc);

	if (sc->sis_type == SIS_TYPE_900 &&
	    (sc->sis_rev == SIS_REV_635 ||
	    sc->sis_rev == SIS_REV_900B)) {
		SIO_SET(SIS_CFG_RND_CNT);
		SIO_SET(SIS_CFG_PERR_DETECT);
	}

	/*
	 * Get station address from the EEPROM.
	 */
	switch (pci_get_vendor(dev)) {
	case NS_VENDORID:
		sc->sis_srr = CSR_READ_4(sc, NS_SRR);

		/* We can't update the device description, so spew */
		if (sc->sis_srr == NS_SRR_15C)
			device_printf(dev, "Silicon Revision: DP83815C\n");
		else if (sc->sis_srr == NS_SRR_15D)
			device_printf(dev, "Silicon Revision: DP83815D\n");
		else if (sc->sis_srr == NS_SRR_16A)
			device_printf(dev, "Silicon Revision: DP83816A\n");
		else
			device_printf(dev, "Silicon Revision %x\n", sc->sis_srr);

		/*
		 * Reading the MAC address out of the EEPROM on
		 * the NatSemi chip takes a bit more work than
		 * you'd expect. The address spans 4 16-bit words,
		 * with the first word containing only a single bit.
		 * You have to shift everything over one bit to
		 * get it aligned properly. Also, the bits are
		 * stored backwards (the LSB is really the MSB,
		 * and so on) so you have to reverse them in order
		 * to get the MAC address into the form we want.
		 * Why? Who the hell knows.
		 */
		{
			uint16_t		tmp[4];

			sis_read_eeprom(sc, (caddr_t)&tmp,
			    NS_EE_NODEADDR, 4, 0);

			/* Shift everything over one bit. */
			tmp[3] = tmp[3] >> 1;
			tmp[3] |= tmp[2] << 15;
			tmp[2] = tmp[2] >> 1;
			tmp[2] |= tmp[1] << 15;
			tmp[1] = tmp[1] >> 1;
			tmp[1] |= tmp[0] << 15;

			/* Now reverse all the bits. */
			tmp[3] = sis_reverse(tmp[3]);
			tmp[2] = sis_reverse(tmp[2]);
			tmp[1] = sis_reverse(tmp[1]);

			eaddr[0] = (tmp[1] >> 0) & 0xFF;
			eaddr[1] = (tmp[1] >> 8) & 0xFF;
			eaddr[2] = (tmp[2] >> 0) & 0xFF;
			eaddr[3] = (tmp[2] >> 8) & 0xFF;
			eaddr[4] = (tmp[3] >> 0) & 0xFF;
			eaddr[5] = (tmp[3] >> 8) & 0xFF;
		}
		break;
	case SIS_VENDORID:
	default:
#if defined(__i386__) || defined(__amd64__)
		/*
		 * If this is a SiS 630E chipset with an embedded
		 * SiS 900 controller, we have to read the MAC address
		 * from the APC CMOS RAM. Our method for doing this
		 * is very ugly since we have to reach out and grab
		 * ahold of hardware for which we cannot properly
		 * allocate resources. This code is only compiled on
		 * the i386 architecture since the SiS 630E chipset
		 * is for x86 motherboards only. Note that there are
		 * a lot of magic numbers in this hack. These are
		 * taken from SiS's Linux driver. I'd like to replace
		 * them with proper symbolic definitions, but that
		 * requires some datasheets that I don't have access
		 * to at the moment.
		 */
		if (sc->sis_rev == SIS_REV_630S ||
		    sc->sis_rev == SIS_REV_630E ||
		    sc->sis_rev == SIS_REV_630EA1)
			sis_read_cmos(sc, dev, (caddr_t)&eaddr, 0x9, 6);

		else if (sc->sis_rev == SIS_REV_635 ||
			 sc->sis_rev == SIS_REV_630ET)
			sis_read_mac(sc, dev, (caddr_t)&eaddr);
		else if (sc->sis_rev == SIS_REV_96x) {
			/* Allow to read EEPROM from LAN. It is shared
			 * between a 1394 controller and the NIC and each
			 * time we access it, we need to set SIS_EECMD_REQ.
			 */
			SIO_SET(SIS_EECMD_REQ);
			for (waittime = 0; waittime < SIS_TIMEOUT;
			    waittime++) {
				/* Force EEPROM to idle state. */
				sis_eeprom_idle(sc);
				if (CSR_READ_4(sc, SIS_EECTL) & SIS_EECMD_GNT) {
					sis_read_eeprom(sc, (caddr_t)&eaddr,
					    SIS_EE_NODEADDR, 3, 0);
					break;
				}
				DELAY(1);
			}
			/*
			 * Set SIS_EECTL_CLK to high, so a other master
			 * can operate on the i2c bus.
			 */
			SIO_SET(SIS_EECTL_CLK);
			/* Refuse EEPROM access by LAN */
			SIO_SET(SIS_EECMD_DONE);
		} else
#endif
			sis_read_eeprom(sc, (caddr_t)&eaddr,
			    SIS_EE_NODEADDR, 3, 0);
		break;
	}

	sis_add_sysctls(sc);

	/* Allocate DMA'able memory. */
	if ((error = sis_dma_alloc(sc)) != 0)
		goto fail;

	ifp = sc->sis_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = sis_ioctl;
	ifp->if_start = sis_start;
	ifp->if_init = sis_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, SIS_TX_LIST_CNT - 1);
	ifp->if_snd.ifq_drv_maxlen = SIS_TX_LIST_CNT - 1;
	IFQ_SET_READY(&ifp->if_snd);

	if (pci_find_cap(sc->sis_dev, PCIY_PMG, &pmc) == 0) {
		if (sc->sis_type == SIS_TYPE_83815)
			ifp->if_capabilities |= IFCAP_WOL;
		else
			ifp->if_capabilities |= IFCAP_WOL_MAGIC;
		ifp->if_capenable = ifp->if_capabilities;
	}

	/*
	 * Do MII setup.
	 */
	error = mii_attach(dev, &sc->sis_miibus, ifp, sis_ifmedia_upd,
	    sis_ifmedia_sts, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	/*
	 * Call MI attach routine.
	 */
	ether_ifattach(ifp, eaddr);

	/*
	 * Tell the upper layer(s) we support long frames.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
#ifdef DEVICE_POLLING
	ifp->if_capabilities |= IFCAP_POLLING;
#endif

	/* Hook interrupt last to avoid having to lock softc */
	error = bus_setup_intr(dev, sc->sis_res[1], INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, sis_intr, sc, &sc->sis_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		ether_ifdetach(ifp);
		goto fail;
	}

fail:
	if (error)
		sis_detach(dev);

	return (error);
}