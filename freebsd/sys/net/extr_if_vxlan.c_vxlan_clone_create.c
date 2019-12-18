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
typedef  int /*<<< orphan*/  vxlp ;
struct TYPE_2__ {int /*<<< orphan*/  octet; } ;
struct vxlan_softc {int vxl_unit; TYPE_1__ vxl_hwaddr; int /*<<< orphan*/  vxl_media; int /*<<< orphan*/  vxl_port_hash_key; int /*<<< orphan*/  vxl_lock; int /*<<< orphan*/  vxl_callout; struct ifnet* vxl_ifp; } ;
struct ifvxlanparam {int dummy; } ;
struct ifnet {int if_flags; int if_capabilities; int if_capenable; scalar_t__ if_hdrlen; scalar_t__ if_baudrate; int /*<<< orphan*/  if_qflush; int /*<<< orphan*/  if_transmit; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_init; struct vxlan_softc* if_softc; } ;
struct if_clone {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOSPC ; 
 int IFCAP_JUMBO_MTU ; 
 int IFCAP_LINKSTATE ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_SIMPLEX ; 
 int IFM_AUTO ; 
 int IFM_ETHER ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  M_VXLAN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  callout_init_rw (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int copyin (scalar_t__,struct ifvxlanparam*,int) ; 
 int /*<<< orphan*/  ether_gen_addr (struct ifnet*,TYPE_1__*) ; 
 int /*<<< orphan*/  ether_ifattach (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vxlan_softc*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifmedia_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_set (int /*<<< orphan*/ *,int) ; 
 struct vxlan_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rm_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vxlan_ftable_init (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_init ; 
 int /*<<< orphan*/  vxlan_ioctl ; 
 int /*<<< orphan*/  vxlan_media_change ; 
 int /*<<< orphan*/  vxlan_media_status ; 
 int /*<<< orphan*/  vxlan_name ; 
 int /*<<< orphan*/  vxlan_qflush ; 
 int /*<<< orphan*/  vxlan_set_default_config (struct vxlan_softc*) ; 
 int vxlan_set_user_config (struct vxlan_softc*,struct ifvxlanparam*) ; 
 int /*<<< orphan*/  vxlan_sysctl_setup (struct vxlan_softc*) ; 
 int /*<<< orphan*/  vxlan_transmit ; 

__attribute__((used)) static int
vxlan_clone_create(struct if_clone *ifc, int unit, caddr_t params)
{
	struct vxlan_softc *sc;
	struct ifnet *ifp;
	struct ifvxlanparam vxlp;
	int error;

	sc = malloc(sizeof(struct vxlan_softc), M_VXLAN, M_WAITOK | M_ZERO);
	sc->vxl_unit = unit;
	vxlan_set_default_config(sc);

	if (params != 0) {
		error = copyin(params, &vxlp, sizeof(vxlp));
		if (error)
			goto fail;

		error = vxlan_set_user_config(sc, &vxlp);
		if (error)
			goto fail;
	}

	ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		error = ENOSPC;
		goto fail;
	}

	sc->vxl_ifp = ifp;
	rm_init(&sc->vxl_lock, "vxlanrm");
	callout_init_rw(&sc->vxl_callout, &sc->vxl_lock, 0);
	sc->vxl_port_hash_key = arc4random();
	vxlan_ftable_init(sc);

	vxlan_sysctl_setup(sc);

	ifp->if_softc = sc;
	if_initname(ifp, vxlan_name, unit);
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_init = vxlan_init;
	ifp->if_ioctl = vxlan_ioctl;
	ifp->if_transmit = vxlan_transmit;
	ifp->if_qflush = vxlan_qflush;
	ifp->if_capabilities |= IFCAP_LINKSTATE | IFCAP_JUMBO_MTU;
	ifp->if_capenable |= IFCAP_LINKSTATE | IFCAP_JUMBO_MTU;

	ifmedia_init(&sc->vxl_media, 0, vxlan_media_change, vxlan_media_status);
	ifmedia_add(&sc->vxl_media, IFM_ETHER | IFM_AUTO, 0, NULL);
	ifmedia_set(&sc->vxl_media, IFM_ETHER | IFM_AUTO);

	ether_gen_addr(ifp, &sc->vxl_hwaddr);
	ether_ifattach(ifp, sc->vxl_hwaddr.octet);

	ifp->if_baudrate = 0;
	ifp->if_hdrlen = 0;

	return (0);

fail:
	free(sc, M_VXLAN);
	return (error);
}