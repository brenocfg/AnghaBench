#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int es_nports; int /*<<< orphan*/  es_name; int /*<<< orphan*/  es_vlan_caps; int /*<<< orphan*/  es_nvlangroups; } ;
struct rtl8366rb_softc {int numphys; scalar_t__ chip_type; int /*<<< orphan*/  callout_mtx; int /*<<< orphan*/  callout_tick; TYPE_2__** ifp; int /*<<< orphan*/ * miibus; int /*<<< orphan*/ * ifname; TYPE_1__ info; scalar_t__ phy4cpu; scalar_t__ smi_acquired; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int if_flags; struct rtl8366rb_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMSR_DEFCAPMASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETHERSWITCH_VLAN_DOT1Q ; 
 int IFF_BROADCAST ; 
 int IFF_DRV_RUNNING ; 
 int IFF_SIMPLEX ; 
 int IFF_UP ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  MII_OFFSET_ANY ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ RTL8366RB ; 
 int /*<<< orphan*/  RTL8366_CVCR ; 
 int RTL8366_NUM_PHYS ; 
 int /*<<< orphan*/  RTL8366_NUM_VLANS ; 
 int /*<<< orphan*/  RTL_WAITOK ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct rtl8366rb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  rtl8366rb_ifmedia_sts ; 
 int /*<<< orphan*/  rtl8366rb_ifmedia_upd ; 
 int /*<<< orphan*/  rtl8366rb_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8366rb_tick (struct rtl8366rb_softc*) ; 
 int /*<<< orphan*/  smi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
rtl8366rb_attach(device_t dev)
{
	struct rtl8366rb_softc *sc;
	uint16_t rev = 0;
	char name[IFNAMSIZ];
	int err = 0;
	int i;

	sc = device_get_softc(dev);

	sc->dev = dev;
	mtx_init(&sc->sc_mtx, "rtl8366rb", NULL, MTX_DEF);
	sc->smi_acquired = 0;
	mtx_init(&sc->callout_mtx, "rtl8366rbcallout", NULL, MTX_DEF);

	rtl8366rb_init(dev);
	smi_read(dev, RTL8366_CVCR, &rev, RTL_WAITOK);
	device_printf(dev, "rev. %d\n", rev & 0x000f);

	sc->phy4cpu = 0;
	(void) resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "phy4cpu", &sc->phy4cpu);

	sc->numphys = sc->phy4cpu ? RTL8366_NUM_PHYS - 1 : RTL8366_NUM_PHYS;

	sc->info.es_nports = sc->numphys + 1;
	sc->info.es_nvlangroups = RTL8366_NUM_VLANS;
	sc->info.es_vlan_caps = ETHERSWITCH_VLAN_DOT1Q;
	if (sc->chip_type == RTL8366RB)
		sprintf(sc->info.es_name, "Realtek RTL8366RB");
	else
		sprintf(sc->info.es_name, "Realtek RTL8366SR");

	/* attach miibus and phys */
	/* PHYs need an interface, so we generate a dummy one */
	for (i = 0; i < sc->numphys; i++) {
		sc->ifp[i] = if_alloc(IFT_ETHER);
		if (sc->ifp[i] == NULL) {
			device_printf(dev, "couldn't allocate ifnet structure\n");
			err = ENOMEM;
			break;
		}

		sc->ifp[i]->if_softc = sc;
		sc->ifp[i]->if_flags |= IFF_UP | IFF_BROADCAST | IFF_DRV_RUNNING
			| IFF_SIMPLEX;
		snprintf(name, IFNAMSIZ, "%sport", device_get_nameunit(dev));
		sc->ifname[i] = malloc(strlen(name)+1, M_DEVBUF, M_WAITOK);
		bcopy(name, sc->ifname[i], strlen(name)+1);
		if_initname(sc->ifp[i], sc->ifname[i], i);
		err = mii_attach(dev, &sc->miibus[i], sc->ifp[i], rtl8366rb_ifmedia_upd, \
			rtl8366rb_ifmedia_sts, BMSR_DEFCAPMASK, \
			i, MII_OFFSET_ANY, 0);
		if (err != 0) {
			device_printf(dev, "attaching PHY %d failed\n", i);
			return (err);
		}
	}

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	err = bus_generic_attach(dev);
	if (err != 0)
		return (err);
	
	callout_init_mtx(&sc->callout_tick, &sc->callout_mtx, 0);
	rtl8366rb_tick(sc);
	
	return (err);
}