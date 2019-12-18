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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int ifq_maxlen; } ;
struct ifnet {int if_flags; TYPE_1__ if_snd; scalar_t__ if_addrlen; scalar_t__ if_hdrlen; int /*<<< orphan*/  if_output; int /*<<< orphan*/  if_ioctl; int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_mtu; struct disc_softc* if_softc; } ;
struct if_clone {int dummy; } ;
struct disc_softc {struct ifnet* sc_ifp; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_NULL ; 
 int /*<<< orphan*/  DSMTU ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IFT_LOOP ; 
 int /*<<< orphan*/  M_DISC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bpfattach (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  discioctl ; 
 int /*<<< orphan*/  discname ; 
 int /*<<< orphan*/  discoutput ; 
 int /*<<< orphan*/  free (struct disc_softc*,int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_attach (struct ifnet*) ; 
 int /*<<< orphan*/  if_initname (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 struct disc_softc* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
disc_clone_create(struct if_clone *ifc, int unit, caddr_t params)
{
	struct ifnet		*ifp;
	struct disc_softc	*sc;

	sc = malloc(sizeof(struct disc_softc), M_DISC, M_WAITOK | M_ZERO);
	ifp = sc->sc_ifp = if_alloc(IFT_LOOP);
	if (ifp == NULL) {
		free(sc, M_DISC);
		return (ENOSPC);
	}

	ifp->if_softc = sc;
	if_initname(ifp, discname, unit);
	ifp->if_mtu = DSMTU;
	/*
	 * IFF_LOOPBACK should not be removed from disc's flags because
	 * it controls what PF-specific routes are magically added when
	 * a network address is assigned to the interface.  Things just
	 * won't work as intended w/o such routes because the output
	 * interface selection for a packet is totally route-driven.
	 * A valid alternative to IFF_LOOPBACK can be IFF_BROADCAST or
	 * IFF_POINTOPOINT, but it would result in different properties
	 * of the interface.
	 */
	ifp->if_flags = IFF_LOOPBACK | IFF_MULTICAST;
	ifp->if_drv_flags = IFF_DRV_RUNNING;
	ifp->if_ioctl = discioctl;
	ifp->if_output = discoutput;
	ifp->if_hdrlen = 0;
	ifp->if_addrlen = 0;
	ifp->if_snd.ifq_maxlen = 20;
	if_attach(ifp);
	bpfattach(ifp, DLT_NULL, sizeof(u_int32_t));

	return (0);
}