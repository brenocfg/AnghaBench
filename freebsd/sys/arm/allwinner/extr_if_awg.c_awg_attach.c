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
typedef  int /*<<< orphan*/  uint8_t ;
struct awg_softc {int /*<<< orphan*/  ifp; int /*<<< orphan*/  miibus; int /*<<< orphan*/  ih; int /*<<< orphan*/ * res; int /*<<< orphan*/  link_task; int /*<<< orphan*/  mtx; int /*<<< orphan*/  stat_ch; int /*<<< orphan*/  type; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  ocd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_UDP ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFCAP_HWCSUM ; 
 int /*<<< orphan*/  IFCAP_POLLING ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MIIF_DOPAUSE ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MII_PHY_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct awg_softc*) ; 
 scalar_t__ TX_DESC_COUNT ; 
 size_t _RES_IRQ ; 
 int /*<<< orphan*/  awg_get_eaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  awg_init ; 
 int /*<<< orphan*/  awg_intr ; 
 int /*<<< orphan*/  awg_ioctl ; 
 int /*<<< orphan*/  awg_link_task ; 
 int /*<<< orphan*/  awg_media_change ; 
 int /*<<< orphan*/  awg_media_status ; 
 int awg_reset (int /*<<< orphan*/ ) ; 
 int awg_setup_dma (int /*<<< orphan*/ ) ; 
 int awg_setup_extres (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  awg_spec ; 
 int /*<<< orphan*/  awg_start ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct awg_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct awg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifattach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_getcapabilities (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilities (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setcapabilitiesbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_sethwassist (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setinitfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setioctlfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsendqlen (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  if_setsendqready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setsoftc (int /*<<< orphan*/ ,struct awg_softc*) ; 
 int /*<<< orphan*/  if_setstartfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
awg_attach(device_t dev)
{
	uint8_t eaddr[ETHER_ADDR_LEN];
	struct awg_softc *sc;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->type = ofw_bus_search_compatible(dev, compat_data)->ocd_data;

	if (bus_alloc_resources(dev, awg_spec, sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	mtx_init(&sc->mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK, MTX_DEF);
	callout_init_mtx(&sc->stat_ch, &sc->mtx, 0);
	TASK_INIT(&sc->link_task, 0, awg_link_task, sc);

	/* Setup clocks and regulators */
	error = awg_setup_extres(dev);
	if (error != 0)
		return (error);

	/* Read MAC address before resetting the chip */
	awg_get_eaddr(dev, eaddr);

	/* Soft reset EMAC core */
	error = awg_reset(dev);
	if (error != 0)
		return (error);

	/* Setup DMA descriptors */
	error = awg_setup_dma(dev);
	if (error != 0)
		return (error);

	/* Install interrupt handler */
	error = bus_setup_intr(dev, sc->res[_RES_IRQ],
	    INTR_TYPE_NET | INTR_MPSAFE, NULL, awg_intr, sc, &sc->ih);
	if (error != 0) {
		device_printf(dev, "cannot setup interrupt handler\n");
		return (error);
	}

	/* Setup ethernet interface */
	sc->ifp = if_alloc(IFT_ETHER);
	if_setsoftc(sc->ifp, sc);
	if_initname(sc->ifp, device_get_name(dev), device_get_unit(dev));
	if_setflags(sc->ifp, IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST);
	if_setstartfn(sc->ifp, awg_start);
	if_setioctlfn(sc->ifp, awg_ioctl);
	if_setinitfn(sc->ifp, awg_init);
	if_setsendqlen(sc->ifp, TX_DESC_COUNT - 1);
	if_setsendqready(sc->ifp);
	if_sethwassist(sc->ifp, CSUM_IP | CSUM_UDP | CSUM_TCP);
	if_setcapabilities(sc->ifp, IFCAP_VLAN_MTU | IFCAP_HWCSUM);
	if_setcapenable(sc->ifp, if_getcapabilities(sc->ifp));
#ifdef DEVICE_POLLING
	if_setcapabilitiesbit(sc->ifp, IFCAP_POLLING, 0);
#endif

	/* Attach MII driver */
	error = mii_attach(dev, &sc->miibus, sc->ifp, awg_media_change,
	    awg_media_status, BMSR_DEFCAPMASK, MII_PHY_ANY, MII_OFFSET_ANY,
	    MIIF_DOPAUSE);
	if (error != 0) {
		device_printf(dev, "cannot attach PHY\n");
		return (error);
	}

	/* Attach ethernet interface */
	ether_ifattach(sc->ifp, eaddr);

	return (0);
}