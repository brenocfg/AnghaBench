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
struct vtbe_softc {int hdrsize; int is_attached; struct ifnet* ifp; int /*<<< orphan*/  dev; int /*<<< orphan*/  pio_recv; int /*<<< orphan*/  pio_send; int /*<<< orphan*/  beri_mem_offset; int /*<<< orphan*/  mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct virtio_net_hdr {int dummy; } ;
struct TYPE_3__ {int ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_hdrlen; TYPE_1__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; struct vtbe_softc* if_softc; int /*<<< orphan*/  if_baudrate; } ;
struct ether_vlan_header {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DESC_COUNT ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_PROMISC ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,int) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_1__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int VIRTIO_F_NOTIFY_ON_EMPTY ; 
 int VIRTIO_ID_NETWORK ; 
 int /*<<< orphan*/  VIRTIO_MMIO_DEVICE_ID ; 
 int /*<<< orphan*/  VIRTIO_MMIO_HOST_FEATURES ; 
 int /*<<< orphan*/  VIRTIO_MMIO_QUEUE_NUM_MAX ; 
 int VIRTIO_NET_F_MAC ; 
 int /*<<< orphan*/  WRITE4 (struct vtbe_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct vtbe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int htobe32 (int) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ setup_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setup_pio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ vtbe_get_hwaddr (struct vtbe_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtbe_init ; 
 int /*<<< orphan*/  vtbe_ioctl ; 
 int /*<<< orphan*/  vtbe_spec ; 
 int /*<<< orphan*/  vtbe_txstart ; 

__attribute__((used)) static int
vtbe_attach(device_t dev)
{
	uint8_t macaddr[ETHER_ADDR_LEN];
	struct vtbe_softc *sc;
	struct ifnet *ifp;
	int reg;

	sc = device_get_softc(dev);
	sc->dev = dev;

	sc->hdrsize = sizeof(struct virtio_net_hdr);

	if (bus_alloc_resources(dev, vtbe_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	mtx_init(&sc->mtx, device_get_nameunit(sc->dev),
	    MTX_NETWORK_LOCK, MTX_DEF);

	if (setup_offset(dev, &sc->beri_mem_offset) != 0)
		return (ENXIO);
	if (setup_pio(dev, "pio-send", &sc->pio_send) != 0)
		return (ENXIO);
	if (setup_pio(dev, "pio-recv", &sc->pio_recv) != 0)
		return (ENXIO);

	/* Setup MMIO */

	/* Specify that we provide network device */
	reg = htobe32(VIRTIO_ID_NETWORK);
	WRITE4(sc, VIRTIO_MMIO_DEVICE_ID, reg);

	/* The number of desc we support */
	reg = htobe32(DESC_COUNT);
	WRITE4(sc, VIRTIO_MMIO_QUEUE_NUM_MAX, reg);

	/* Our features */
	reg = htobe32(VIRTIO_NET_F_MAC |
    			VIRTIO_F_NOTIFY_ON_EMPTY);
	WRITE4(sc, VIRTIO_MMIO_HOST_FEATURES, reg);

	/* Get MAC */
	if (vtbe_get_hwaddr(sc, macaddr)) {
		device_printf(sc->dev, "can't get mac\n");
		return (ENXIO);
	}

	/* Set up the ethernet interface. */
	sc->ifp = ifp = if_alloc(IFT_ETHER);
	ifp->if_baudrate = IF_Gbps(10);
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = (IFF_BROADCAST | IFF_SIMPLEX |
			 IFF_MULTICAST | IFF_PROMISC);
	ifp->if_capabilities = IFCAP_VLAN_MTU;
	ifp->if_capenable = ifp->if_capabilities;
	ifp->if_start = vtbe_txstart;
	ifp->if_ioctl = vtbe_ioctl;
	ifp->if_init = vtbe_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, DESC_COUNT - 1);
	ifp->if_snd.ifq_drv_maxlen = DESC_COUNT - 1;
	IFQ_SET_READY(&ifp->if_snd);
	ifp->if_hdrlen = sizeof(struct ether_vlan_header);

	/* All ready to run, attach the ethernet interface. */
	ether_ifattach(ifp, macaddr);

	sc->is_attached = true;

	return (0);
}