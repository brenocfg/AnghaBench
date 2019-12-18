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
struct me_softc {int dummy; } ;
struct ifnet {struct me_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ME_WAIT () ; 
 int /*<<< orphan*/  M_IFME ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct me_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  me_delete_tunnel (struct me_softc*) ; 
 int /*<<< orphan*/  me_ioctl_sx ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
me_clone_destroy(struct ifnet *ifp)
{
	struct me_softc *sc;

	sx_xlock(&me_ioctl_sx);
	sc = ifp->if_softc;
	me_delete_tunnel(sc);
	bpfdetach(ifp);
	if_detach(ifp);
	ifp->if_softc = NULL;
	sx_xunlock(&me_ioctl_sx);

	ME_WAIT();
	if_free(ifp);
	free(sc, M_IFME);
}