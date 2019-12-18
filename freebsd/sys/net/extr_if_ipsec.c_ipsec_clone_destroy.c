#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ipsec_softc {scalar_t__ reqid; } ;
struct ifnet {struct ipsec_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_REMOVE (struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSEC_WAIT () ; 
 int /*<<< orphan*/  M_IPSEC ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct ipsec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idhash ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ipsec_delete_tunnel (struct ipsec_softc*) ; 
 int /*<<< orphan*/  ipsec_ioctl_sx ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipsec_clone_destroy(struct ifnet *ifp)
{
	struct ipsec_softc *sc;

	sx_xlock(&ipsec_ioctl_sx);
	sc = ifp->if_softc;
	ipsec_delete_tunnel(sc);
	/*
	 * Delete softc from idhash on interface destroy, since
	 * ipsec_delete_tunnel() keeps reqid unchanged.
	 */
	if (sc->reqid != 0)
		CK_LIST_REMOVE(sc, idhash);
	bpfdetach(ifp);
	if_detach(ifp);
	ifp->if_softc = NULL;
	sx_xunlock(&ipsec_ioctl_sx);

	IPSEC_WAIT();
	if_free(ifp);
	free(sc, M_IPSEC);
}