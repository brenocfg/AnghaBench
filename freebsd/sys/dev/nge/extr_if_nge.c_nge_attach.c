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
typedef  int /*<<< orphan*/  uint16_t ;
struct nge_softc {scalar_t__ nge_res_type; int nge_res_id; int /*<<< orphan*/  nge_intrhand; int /*<<< orphan*/ * nge_irq; int /*<<< orphan*/  nge_miibus; int /*<<< orphan*/  nge_flags; int /*<<< orphan*/  nge_dev; struct ifnet* nge_ifp; int /*<<< orphan*/ * nge_res; int /*<<< orphan*/  nge_mtx; int /*<<< orphan*/  nge_stat_ch; } ;
struct TYPE_3__ {scalar_t__ ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; int if_hdrlen; int /*<<< orphan*/  if_hwassist; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct nge_softc* if_softc; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  eaddr ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSR_READ_4 (struct nge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct nge_softc*,int /*<<< orphan*/ ,int) ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int IFCAP_POLLING ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_MTU ; 
 int IFCAP_WOL ; 
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
 int /*<<< orphan*/  NGE_CFG ; 
 int NGE_CFG_TBI_EN ; 
 int /*<<< orphan*/  NGE_CSUM_FEATURES ; 
 int /*<<< orphan*/  NGE_EE_NODEADDR ; 
 int /*<<< orphan*/  NGE_FLAG_TBI ; 
 int /*<<< orphan*/  NGE_GPIO ; 
 int NGE_GPIO_GP1_OUTENB ; 
 int NGE_GPIO_GP2_OUTENB ; 
 int NGE_GPIO_GP3_IN ; 
 int NGE_GPIO_GP3_OUTENB ; 
 int NGE_GPIO_GP4_IN ; 
 int NGE_GPIO_GP4_OUT ; 
 int /*<<< orphan*/  NGE_LOCK_DESTROY (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_LOCK_INIT (struct nge_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ NGE_TX_RING_CNT ; 
 int /*<<< orphan*/  PCIM_CMD_MWRICEN ; 
 void* PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIY_PMG ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 void* SYS_RES_IOPORT ; 
 scalar_t__ SYS_RES_IRQ ; 
 scalar_t__ SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nge_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct nge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nge_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ nge_dma_alloc (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_init ; 
 int /*<<< orphan*/  nge_intr ; 
 int /*<<< orphan*/  nge_ioctl ; 
 int /*<<< orphan*/  nge_mediachange ; 
 int /*<<< orphan*/  nge_mediastatus ; 
 int /*<<< orphan*/  nge_read_eeprom (struct nge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nge_reset (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_start ; 
 int /*<<< orphan*/  nge_sysctl_node (struct nge_softc*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nge_attach(device_t dev)
{
	uint8_t eaddr[ETHER_ADDR_LEN];
	uint16_t ea[ETHER_ADDR_LEN/2], ea_temp, reg;
	struct nge_softc *sc;
	struct ifnet *ifp;
	int error, i, rid;

	error = 0;
	sc = device_get_softc(dev);
	sc->nge_dev = dev;

	NGE_LOCK_INIT(sc, device_get_nameunit(dev));
	callout_init_mtx(&sc->nge_stat_ch, &sc->nge_mtx, 0);

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

#ifdef NGE_USEIOSPACE
	sc->nge_res_type = SYS_RES_IOPORT;
	sc->nge_res_id = PCIR_BAR(0);
#else
	sc->nge_res_type = SYS_RES_MEMORY;
	sc->nge_res_id = PCIR_BAR(1);
#endif
	sc->nge_res = bus_alloc_resource_any(dev, sc->nge_res_type,
	    &sc->nge_res_id, RF_ACTIVE);

	if (sc->nge_res == NULL) {
		if (sc->nge_res_type == SYS_RES_MEMORY) {
			sc->nge_res_type = SYS_RES_IOPORT;
			sc->nge_res_id = PCIR_BAR(0);
		} else {
			sc->nge_res_type = SYS_RES_MEMORY;
			sc->nge_res_id = PCIR_BAR(1);
		}
		sc->nge_res = bus_alloc_resource_any(dev, sc->nge_res_type,
		    &sc->nge_res_id, RF_ACTIVE);
		if (sc->nge_res == NULL) {
			device_printf(dev, "couldn't allocate %s resources\n",
			    sc->nge_res_type == SYS_RES_MEMORY ? "memory" :
			    "I/O");
			NGE_LOCK_DESTROY(sc);
			return (ENXIO);
		}
	}

	/* Allocate interrupt */
	rid = 0;
	sc->nge_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE);

	if (sc->nge_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto fail;
	}

	/* Enable MWI. */
	reg = pci_read_config(dev, PCIR_COMMAND, 2);
	reg |= PCIM_CMD_MWRICEN;
	pci_write_config(dev, PCIR_COMMAND, reg, 2);

	/* Reset the adapter. */
	nge_reset(sc);

	/*
	 * Get station address from the EEPROM.
	 */
	nge_read_eeprom(sc, (caddr_t)ea, NGE_EE_NODEADDR, 3);
	for (i = 0; i < ETHER_ADDR_LEN / 2; i++)
		ea[i] = le16toh(ea[i]);
	ea_temp = ea[0];
	ea[0] = ea[2];
	ea[2] = ea_temp;
	bcopy(ea, eaddr, sizeof(eaddr));

	if (nge_dma_alloc(sc) != 0) {
		error = ENXIO;
		goto fail;
	}

	nge_sysctl_node(sc);

	ifp = sc->nge_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not allocate ifnet structure\n");
		error = ENOSPC;
		goto fail;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = nge_ioctl;
	ifp->if_start = nge_start;
	ifp->if_init = nge_init;
	ifp->if_snd.ifq_drv_maxlen = NGE_TX_RING_CNT - 1;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifp->if_snd.ifq_drv_maxlen);
	IFQ_SET_READY(&ifp->if_snd);
	ifp->if_hwassist = NGE_CSUM_FEATURES;
	ifp->if_capabilities = IFCAP_HWCSUM;
	/*
	 * It seems that some hardwares doesn't provide 3.3V auxiliary
	 * supply(3VAUX) to drive PME such that checking PCI power
	 * management capability is necessary.
	 */
	if (pci_find_cap(sc->nge_dev, PCIY_PMG, &i) == 0)
		ifp->if_capabilities |= IFCAP_WOL;
	ifp->if_capenable = ifp->if_capabilities;

	if ((CSR_READ_4(sc, NGE_CFG) & NGE_CFG_TBI_EN) != 0) {
		sc->nge_flags |= NGE_FLAG_TBI;
		device_printf(dev, "Using TBI\n");
		/* Configure GPIO. */
		CSR_WRITE_4(sc, NGE_GPIO, CSR_READ_4(sc, NGE_GPIO)
		    | NGE_GPIO_GP4_OUT
		    | NGE_GPIO_GP1_OUTENB | NGE_GPIO_GP2_OUTENB
		    | NGE_GPIO_GP3_OUTENB
		    | NGE_GPIO_GP3_IN | NGE_GPIO_GP4_IN);
	}

	/*
	 * Do MII setup.
	 */
	error = mii_attach(dev, &sc->nge_miibus, ifp, nge_mediachange,
	    nge_mediastatus, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY, 0);
	if (error != 0) {
		device_printf(dev, "attaching PHYs failed\n");
		goto fail;
	}

	/*
	 * Call MI attach routine.
	 */
	ether_ifattach(ifp, eaddr);

	/* VLAN capability setup. */
	ifp->if_capabilities |= IFCAP_VLAN_MTU | IFCAP_VLAN_HWTAGGING;
	ifp->if_capabilities |= IFCAP_VLAN_HWCSUM;
	ifp->if_capenable = ifp->if_capabilities;
#ifdef DEVICE_POLLING
	ifp->if_capabilities |= IFCAP_POLLING;
#endif
	/*
	 * Tell the upper layer(s) we support long frames.
	 * Must appear after the call to ether_ifattach() because
	 * ether_ifattach() sets ifi_hdrlen to the default value.
	 */
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/*
	 * Hookup IRQ last.
	 */
	error = bus_setup_intr(dev, sc->nge_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, nge_intr, sc, &sc->nge_intrhand);
	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		goto fail;
	}

fail:
	if (error != 0)
		nge_detach(dev);
	return (error);
}