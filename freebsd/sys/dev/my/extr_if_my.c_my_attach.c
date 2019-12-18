#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct my_type {int my_vid; int /*<<< orphan*/  my_name; } ;
struct TYPE_7__ {int ifm_media; } ;
struct my_softc {int my_phy_addr; int /*<<< orphan*/  my_mtx; int /*<<< orphan*/ * my_res; int /*<<< orphan*/ * my_irq; int /*<<< orphan*/ * my_ldata_ptr; int /*<<< orphan*/  my_intrhand; TYPE_2__ ifmedia; struct my_type* my_pinfo; TYPE_1__* my_info; struct ifnet* my_ifp; struct my_list_data* my_ldata; int /*<<< orphan*/  my_bhandle; int /*<<< orphan*/  my_btag; int /*<<< orphan*/  my_watchdog; int /*<<< orphan*/  my_autoneg_timer; int /*<<< orphan*/  my_dev; } ;
struct my_list_data {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct ifnet {int if_flags; int if_baudrate; TYPE_4__ if_snd; int /*<<< orphan*/  if_init; int /*<<< orphan*/  if_start; int /*<<< orphan*/  if_ioctl; struct my_softc* if_softc; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_6__ {scalar_t__ my_did; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_READ_1 (struct my_softc*,scalar_t__) ; 
 int ENOSPC ; 
 int ENXIO ; 
 int ETHER_ADDR_LEN ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_100_TX ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_4__*) ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 scalar_t__ MTD800ID ; 
 scalar_t__ MTD803ID ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_NETWORK_LOCK ; 
 int /*<<< orphan*/  MY_FLAG_FORCEDELAY ; 
 int /*<<< orphan*/  MY_LOCK (struct my_softc*) ; 
 scalar_t__ MY_PAR0 ; 
 int /*<<< orphan*/  MY_PCI_LOIO ; 
 int MY_PHYADDR_MAX ; 
 int MY_PHYADDR_MIN ; 
 int /*<<< orphan*/  MY_RES ; 
 int MY_RID ; 
 int /*<<< orphan*/  MY_UNLOCK (struct my_softc*) ; 
 scalar_t__ MY_USEIOSPACE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PHY_BMSR ; 
 int /*<<< orphan*/  PHY_DEVID ; 
 size_t PHY_UNKNOWN ; 
 int /*<<< orphan*/  PHY_VENID ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct my_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct my_list_data*,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct my_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  my_autoneg_mii (struct my_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_getmode_mii (struct my_softc*) ; 
 int /*<<< orphan*/  my_ifmedia_sts ; 
 int /*<<< orphan*/  my_ifmedia_upd ; 
 TYPE_1__* my_info_tmp ; 
 int /*<<< orphan*/  my_init ; 
 int /*<<< orphan*/  my_intr ; 
 int /*<<< orphan*/  my_ioctl ; 
 int my_phy_readreg (struct my_softc*,int /*<<< orphan*/ ) ; 
 struct my_type* my_phys ; 
 int /*<<< orphan*/  my_reset (struct my_softc*) ; 
 int /*<<< orphan*/  my_start ; 
 int /*<<< orphan*/  my_stop (struct my_softc*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
my_attach(device_t dev)
{
	int             i;
	u_char          eaddr[ETHER_ADDR_LEN];
	u_int32_t       iobase;
	struct my_softc *sc;
	struct ifnet   *ifp;
	int             media = IFM_ETHER | IFM_100_TX | IFM_FDX;
	unsigned int    round;
	caddr_t         roundptr;
	struct my_type *p;
	u_int16_t       phy_vid, phy_did, phy_sts = 0;
	int             rid, error = 0;

	sc = device_get_softc(dev);
	sc->my_dev = dev;
	mtx_init(&sc->my_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);
	callout_init_mtx(&sc->my_autoneg_timer, &sc->my_mtx, 0);
	callout_init_mtx(&sc->my_watchdog, &sc->my_mtx, 0);

	/*
	 * Map control/status registers.
	 */
	pci_enable_busmaster(dev);

	if (my_info_tmp->my_did == MTD800ID) {
		iobase = pci_read_config(dev, MY_PCI_LOIO, 4);
		if (iobase & 0x300)
			MY_USEIOSPACE = 0;
	}

	rid = MY_RID;
	sc->my_res = bus_alloc_resource_any(dev, MY_RES, &rid, RF_ACTIVE);

	if (sc->my_res == NULL) {
		device_printf(dev, "couldn't map ports/memory\n");
		error = ENXIO;
		goto destroy_mutex;
	}
	sc->my_btag = rman_get_bustag(sc->my_res);
	sc->my_bhandle = rman_get_bushandle(sc->my_res);

	rid = 0;
	sc->my_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
					    RF_SHAREABLE | RF_ACTIVE);

	if (sc->my_irq == NULL) {
		device_printf(dev, "couldn't map interrupt\n");
		error = ENXIO;
		goto release_io;
	}

	sc->my_info = my_info_tmp;

	/* Reset the adapter. */
	MY_LOCK(sc);
	my_reset(sc);
	MY_UNLOCK(sc);

	/*
	 * Get station address
	 */
	for (i = 0; i < ETHER_ADDR_LEN; ++i)
		eaddr[i] = CSR_READ_1(sc, MY_PAR0 + i);

	sc->my_ldata_ptr = malloc(sizeof(struct my_list_data) + 8,
				  M_DEVBUF, M_NOWAIT);
	if (sc->my_ldata_ptr == NULL) {
		device_printf(dev, "no memory for list buffers!\n");
		error = ENXIO;
		goto release_irq;
	}
	sc->my_ldata = (struct my_list_data *) sc->my_ldata_ptr;
	round = (uintptr_t)sc->my_ldata_ptr & 0xF;
	roundptr = sc->my_ldata_ptr;
	for (i = 0; i < 8; i++) {
		if (round % 8) {
			round++;
			roundptr++;
		} else
			break;
	}
	sc->my_ldata = (struct my_list_data *) roundptr;
	bzero(sc->my_ldata, sizeof(struct my_list_data));

	ifp = sc->my_ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "can not if_alloc()\n");
		error = ENOSPC;
		goto free_ldata;
	}
	ifp->if_softc = sc;
	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_ioctl = my_ioctl;
	ifp->if_start = my_start;
	ifp->if_init = my_init;
	ifp->if_baudrate = 10000000;
	IFQ_SET_MAXLEN(&ifp->if_snd, ifqmaxlen);
	ifp->if_snd.ifq_drv_maxlen = ifqmaxlen;
	IFQ_SET_READY(&ifp->if_snd);

	if (sc->my_info->my_did == MTD803ID)
		sc->my_pinfo = my_phys;
	else {
		if (bootverbose)
			device_printf(dev, "probing for a PHY\n");
		MY_LOCK(sc);
		for (i = MY_PHYADDR_MIN; i < MY_PHYADDR_MAX + 1; i++) {
			if (bootverbose)
				device_printf(dev, "checking address: %d\n", i);
			sc->my_phy_addr = i;
			phy_sts = my_phy_readreg(sc, PHY_BMSR);
			if ((phy_sts != 0) && (phy_sts != 0xffff))
				break;
			else
				phy_sts = 0;
		}
		if (phy_sts) {
			phy_vid = my_phy_readreg(sc, PHY_VENID);
			phy_did = my_phy_readreg(sc, PHY_DEVID);
			if (bootverbose) {
				device_printf(dev, "found PHY at address %d, ",
				    sc->my_phy_addr);
				printf("vendor id: %x device id: %x\n",
				    phy_vid, phy_did);
			}
			p = my_phys;
			while (p->my_vid) {
				if (phy_vid == p->my_vid) {
					sc->my_pinfo = p;
					break;
				}
				p++;
			}
			if (sc->my_pinfo == NULL)
				sc->my_pinfo = &my_phys[PHY_UNKNOWN];
			if (bootverbose)
				device_printf(dev, "PHY type: %s\n",
				       sc->my_pinfo->my_name);
		} else {
			MY_UNLOCK(sc);
			device_printf(dev, "MII without any phy!\n");
			error = ENXIO;
			goto free_if;
		}
		MY_UNLOCK(sc);
	}

	/* Do ifmedia setup. */
	ifmedia_init(&sc->ifmedia, 0, my_ifmedia_upd, my_ifmedia_sts);
	MY_LOCK(sc);
	my_getmode_mii(sc);
	my_autoneg_mii(sc, MY_FLAG_FORCEDELAY, 1);
	media = sc->ifmedia.ifm_media;
	my_stop(sc);
	MY_UNLOCK(sc);
	ifmedia_set(&sc->ifmedia, media);

	ether_ifattach(ifp, eaddr);

	error = bus_setup_intr(dev, sc->my_irq, INTR_TYPE_NET | INTR_MPSAFE,
			       NULL, my_intr, sc, &sc->my_intrhand);

	if (error) {
		device_printf(dev, "couldn't set up irq\n");
		goto detach_if;
	}
	 
	return (0);

detach_if:
	ether_ifdetach(ifp);
free_if:
	if_free(ifp);
free_ldata:
	free(sc->my_ldata_ptr, M_DEVBUF);
release_irq:
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->my_irq);
release_io:
	bus_release_resource(dev, MY_RES, MY_RID, sc->my_res);
destroy_mutex:
	mtx_destroy(&sc->my_mtx);
	return (error);
}