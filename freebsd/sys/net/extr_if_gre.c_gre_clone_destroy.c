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
struct ifnet {struct gre_softc* if_softc; } ;
struct gre_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRE_WAIT () ; 
 int /*<<< orphan*/  M_GRE ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct gre_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gre_delete_tunnel (struct gre_softc*) ; 
 int /*<<< orphan*/  gre_ioctl_sx ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gre_clone_destroy(struct ifnet *ifp)
{
	struct gre_softc *sc;

	sx_xlock(&gre_ioctl_sx);
	sc = ifp->if_softc;
	gre_delete_tunnel(sc);
	bpfdetach(ifp);
	if_detach(ifp);
	ifp->if_softc = NULL;
	sx_xunlock(&gre_ioctl_sx);

	GRE_WAIT();
	if_free(ifp);
	free(sc, M_GRE);
}