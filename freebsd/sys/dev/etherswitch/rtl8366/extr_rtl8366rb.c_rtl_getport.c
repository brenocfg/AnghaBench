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
struct rtl8366rb_softc {int numphys; int* vid; int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * miibus; scalar_t__ phy4cpu; } ;
struct ifmedia {int dummy; } ;
struct mii_data {struct ifmedia mii_media; } ;
struct ifmediareq {int ifm_status; int ifm_count; int /*<<< orphan*/ * ifm_ulist; scalar_t__ ifm_mask; int /*<<< orphan*/  ifm_active; int /*<<< orphan*/  ifm_current; } ;
struct TYPE_3__ {int es_port; int es_pvid; int /*<<< orphan*/  es_flags; int /*<<< orphan*/  es_ifr; struct ifmediareq es_ifmr; } ;
typedef  TYPE_1__ etherswitch_port_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ETHERSWITCH_PORT_CPU ; 
 int ETHERSWITCH_VID_MASK ; 
 int /*<<< orphan*/  IFM_1000_T ; 
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 int /*<<< orphan*/  IFM_FDX ; 
 int /*<<< orphan*/  IFM_MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RTL8366_NUM_PHYS ; 
 scalar_t__ RTL8366_PLSR_BASE ; 
 int RTL8366_PVCR_GET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL8366_PVCR_REG (int) ; 
 int /*<<< orphan*/  RTL_WAITOK ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ifmedia*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8366rb_update_ifmedia (int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smi_read (int /*<<< orphan*/ ,scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtl_getport(device_t dev, etherswitch_port_t *p)
{
	struct rtl8366rb_softc *sc;
	struct ifmedia *ifm;
	struct mii_data *mii;
	struct ifmediareq *ifmr;
	uint16_t v;
	int err, vlangroup;
	
	sc = device_get_softc(dev);

	ifmr = &p->es_ifmr;

	if (p->es_port < 0 || p->es_port >= (sc->numphys + 1))
		return (ENXIO);
	if (sc->phy4cpu && p->es_port == sc->numphys) {
		vlangroup = RTL8366_PVCR_GET(p->es_port + 1,
		    rtl_readreg(dev, RTL8366_PVCR_REG(p->es_port + 1)));
	} else {
		vlangroup = RTL8366_PVCR_GET(p->es_port,
		    rtl_readreg(dev, RTL8366_PVCR_REG(p->es_port)));
	}
	p->es_pvid = sc->vid[vlangroup] & ETHERSWITCH_VID_MASK;
	
	if (p->es_port < sc->numphys) {
		mii = device_get_softc(sc->miibus[p->es_port]);
		ifm = &mii->mii_media;
		err = ifmedia_ioctl(sc->ifp[p->es_port], &p->es_ifr, ifm, SIOCGIFMEDIA);
		if (err)
			return (err);
	} else {
		/* fill in fixed values for CPU port */
		p->es_flags |= ETHERSWITCH_PORT_CPU;
		smi_read(dev, RTL8366_PLSR_BASE + (RTL8366_NUM_PHYS)/2, &v, RTL_WAITOK);
		v = v >> (8 * ((RTL8366_NUM_PHYS) % 2));
		rtl8366rb_update_ifmedia(v, &ifmr->ifm_status, &ifmr->ifm_active);
		ifmr->ifm_current = ifmr->ifm_active;
		ifmr->ifm_mask = 0;
		ifmr->ifm_status = IFM_ACTIVE | IFM_AVALID;
		/* Return our static media list. */
		if (ifmr->ifm_count > 0) {
			ifmr->ifm_count = 1;
			ifmr->ifm_ulist[0] = IFM_MAKEWORD(IFM_ETHER, IFM_1000_T,
			    IFM_FDX, 0);
		} else
			ifmr->ifm_count = 0;
	}
	return (0);
}