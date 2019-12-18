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
typedef  int /*<<< orphan*/  uint8_t ;
struct msk_softc {int msk_pflags; scalar_t__ msk_hw_id; struct msk_if_softc** msk_if; int /*<<< orphan*/  msk_mtx; } ;
struct msk_mii_data {int port; int /*<<< orphan*/  mii_flags; } ;
struct msk_if_softc {int msk_port; int msk_flags; int /*<<< orphan*/ * msk_if_dev; int /*<<< orphan*/  msk_miibus; struct ifnet* msk_ifp; struct msk_softc* msk_softc; int /*<<< orphan*/  msk_tick_ch; int /*<<< orphan*/  msk_rxq; int /*<<< orphan*/  msk_txsq; int /*<<< orphan*/  msk_txq; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_hwassist; int if_capenable; int if_hdrlen; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct msk_if_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ B2_MAC_1 ; 
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 int /*<<< orphan*/  CSR_READ_1 (struct msk_softc*,scalar_t__) ; 
 int CSUM_TSO ; 
 int EINVAL ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int MSK_CSUM_FEATURES ; 
 int MSK_FLAG_DESCV2 ; 
 int MSK_FLAG_NOHWVLAN ; 
 int MSK_FLAG_NORX_CSUM ; 
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 int MSK_PORT_A ; 
 scalar_t__ MSK_TX_RING_CNT ; 
 int /*<<< orphan*/  PHY_ADDR_MARV ; 
 int /*<<< orphan*/  Q_R1 ; 
 int /*<<< orphan*/  Q_R2 ; 
 int /*<<< orphan*/  Q_XA1 ; 
 int /*<<< orphan*/  Q_XA2 ; 
 int /*<<< orphan*/  Q_XS1 ; 
 int /*<<< orphan*/  Q_XS2 ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct msk_mii_data* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 void* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msk_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msk_init ; 
 int /*<<< orphan*/  msk_ioctl ; 
 int /*<<< orphan*/  msk_mediachange ; 
 int /*<<< orphan*/  msk_mediastatus ; 
 int /*<<< orphan*/  msk_rx_dma_jalloc (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_start ; 
 int /*<<< orphan*/  msk_sysctl_node (struct msk_if_softc*) ; 
 int msk_txrx_dma_alloc (struct msk_if_softc*) ; 

__attribute__((used)) static int
msk_attach(device_t dev)
{
	struct msk_softc *sc;
	struct msk_if_softc *sc_if;
	struct ifnet *ifp;
	struct msk_mii_data *mmd;
	int i, port, error;
	uint8_t eaddr[6];

	if (dev == NULL)
		return (EINVAL);

	error = 0;
	sc_if = device_get_softc(dev);
	sc = device_get_softc(device_get_parent(dev));
	mmd = device_get_ivars(dev);
	port = mmd->port;

	sc_if->msk_if_dev = dev;
	sc_if->msk_port = port;
	sc_if->msk_softc = sc;
	sc_if->msk_flags = sc->msk_pflags;
	sc->msk_if[port] = sc_if;
	/* Setup Tx/Rx queue register offsets. */
	if (port == MSK_PORT_A) {
		sc_if->msk_txq = Q_XA1;
		sc_if->msk_txsq = Q_XS1;
		sc_if->msk_rxq = Q_R1;
	} else {
		sc_if->msk_txq = Q_XA2;
		sc_if->msk_txsq = Q_XS2;
		sc_if->msk_rxq = Q_R2;
	}

	callout_init_mtx(&sc_if->msk_tick_ch, &sc_if->msk_softc->msk_mtx, 0);
	msk_sysctl_node(sc_if);

	if ((error = msk_txrx_dma_alloc(sc_if)) != 0)
		goto fail;
	msk_rx_dma_jalloc(sc_if);

	ifp = sc_if->msk_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(sc_if->msk_if_dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc_if;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_capabilities = IFCAP_TXCSUM | IFCAP_TSO4;
	/*
	 * Enable Rx checksum offloading if controller supports
	 * new descriptor formant and controller is not Yukon XL.
	 */
	if ((sc_if->msk_flags & MSK_FLAG_DESCV2) == 0 &&
	    sc->msk_hw_id != CHIP_ID_YUKON_XL)
		ifp->if_capabilities |= IFCAP_RXCSUM;
	if ((sc_if->msk_flags & MSK_FLAG_DESCV2) != 0 &&
	    (sc_if->msk_flags & MSK_FLAG_NORX_CSUM) == 0)
		ifp->if_capabilities |= IFCAP_RXCSUM;
	ifp->if_hwassist = MSK_CSUM_FEATURES | CSUM_TSO;
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_ioctl = msk_ioctl;
	ifp->if_start = msk_start;
	ifp->if_init = msk_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, MSK_TX_RING_CNT - 1);
	ifp->if_snd.ifq_drv_maxlen = MSK_TX_RING_CNT - 1;
	IFQ_SET_READY(&ifp->if_snd);
	/*
	 * Get station address for this interface. Note that
	 * dual port cards actually come with three station
	 * addresses: one for each port, plus an extra. The
	 * extra one is used by the SysKonnect driver software
	 * as a 'virtual' station address for when both ports
	 * are operating in failover mode. Currently we don't
	 * use this extra address.
	 */
	MSK_IF_LOCK(sc_if);
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		eaddr[i] = CSR_READ_1(sc, B2_MAC_1 + (port * 8) + i);

	/*
	 * Call MI attach routine.  Can't hold locks when calling into ether_*.
	 */
	MSK_IF_UNLOCK(sc_if);
	ether_ifattach(ifp, eaddr);
	MSK_IF_LOCK(sc_if);

	/* VLAN capability setup */
	ifp->if_capabilities |= IFCAP_VLAN_MTU;
	if ((sc_if->msk_flags & MSK_FLAG_NOHWVLAN) == 0) {
		/*
		 * Due to Tx checksum offload hardware bugs, msk(4) manually
		 * computes checksum for short frames. For VLAN tagged frames
		 * this workaround does not work so disable checksum offload
		 * for VLAN interface.
		 */
		ifp->if_capabilities |= IFCAP_VLAN_HWTAGGING | IFCAP_VLAN_HWTSO;
		/*
		 * Enable Rx checksum offloading for VLAN tagged frames
		 * if controller support new descriptor format.
		 */
		if ((sc_if->msk_flags & MSK_FLAG_DESCV2) != 0 &&
		    (sc_if->msk_flags & MSK_FLAG_NORX_CSUM) == 0)
			ifp->if_capabilities |= IFCAP_VLAN_HWCSUM;
	}
	ifp->if_capenable = ifp->if_capabilities;
	/*
	 * Disable RX checksum offloading on controllers that don't use
	 * new descriptor format but give chance to enable it.
	 */
	if ((sc_if->msk_flags & MSK_FLAG_DESCV2) == 0)
		ifp->if_capenable &= ~IFCAP_RXCSUM;

	/*
	 * Tell the upper layer(s) we support long frames.
	 * Must appear after the call to ether_ifattach() because
	 * ether_ifattach() sets ifi_hdrlen to the default value.
	 */
        ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/*
	 * Do miibus setup.
	 */
	MSK_IF_UNLOCK(sc_if);
	error = mii_attach(dev, &sc_if->msk_miibus, ifp, msk_mediachange,
	    msk_mediastatus, BMSR_DEFCAPMASK, PHY_ADDR_MARV, MII_OFFSET_ANY,
	    mmd->mii_flags);
	if (error != 0) {
		device_printf(sc_if->msk_if_dev, "attaching PHYs failed\n");
		ether_ifdetach(ifp);
		error = ENXIO;
		goto fail;
	}

fail:
	if (error != 0) {
		/* Access should be ok even though lock has been dropped */
		sc->msk_if[port] = NULL;
		msk_detach(dev);
	}

	return (error);
}