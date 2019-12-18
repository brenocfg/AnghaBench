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
struct ifmedia {int dummy; } ;
struct mii_data {struct ifmedia mii_media; } ;
struct ifnet {int dummy; } ;
struct e6060sw_softc {size_t numports; scalar_t__ vlan_mode; scalar_t__* portphy; scalar_t__ cpuport; scalar_t__ smi_offset; } ;
struct TYPE_3__ {size_t es_port; int es_pvid; int /*<<< orphan*/  es_ifr; } ;
typedef  TYPE_1__ etherswitch_port_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CORE_REGISTER ; 
 int ENXIO ; 
 scalar_t__ ETHERSWITCH_VLAN_DOT1Q ; 
 int MDIO_READREG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_WRITEREG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_DEFVLAN ; 
 int /*<<< orphan*/  SIOCSIFMEDIA ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct e6060sw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct ifnet* e6060sw_ifpforport (struct e6060sw_softc*,size_t) ; 
 struct mii_data* e6060sw_miiforport (struct e6060sw_softc*,size_t) ; 
 int ifmedia_ioctl (struct ifnet*,int /*<<< orphan*/ *,struct ifmedia*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e6060sw_setport(device_t dev, etherswitch_port_t *p)
{
	struct e6060sw_softc *sc;
	struct ifmedia *ifm;
	struct mii_data *mii;
	struct ifnet *ifp;
	int err;
	int data;

	sc = device_get_softc(dev);

	if (p->es_port < 0 || p->es_port >= sc->numports)
		return (ENXIO);

	if (sc->vlan_mode == ETHERSWITCH_VLAN_DOT1Q) {
		data = MDIO_READREG(device_get_parent(dev), 
		    CORE_REGISTER + sc->smi_offset + p->es_port,
		    PORT_DEFVLAN);
		data &= ~0xfff;
		data |= p->es_pvid;
		data |= 1 << 12;
		MDIO_WRITEREG(device_get_parent(dev), 
		    CORE_REGISTER + sc->smi_offset + p->es_port,
		    PORT_DEFVLAN, data);
	}

	if (sc->portphy[p->es_port] == sc->cpuport)
		return(0);

	mii = e6060sw_miiforport(sc, p->es_port);
	if (mii == NULL)
		return (ENXIO);

	ifp = e6060sw_ifpforport(sc, p->es_port);

	ifm = &mii->mii_media;
	err = ifmedia_ioctl(ifp, &p->es_ifr, ifm, SIOCSIFMEDIA);
	return (err);
}