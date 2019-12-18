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
struct ifnet {struct gif_softc* if_softc; } ;
struct gif_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIF_WAIT () ; 
 int /*<<< orphan*/  M_GIF ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct gif_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gif_delete_tunnel (struct gif_softc*) ; 
 int /*<<< orphan*/  gif_ioctl_sx ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ng_gif_detach_p (struct ifnet*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gif_clone_destroy(struct ifnet *ifp)
{
	struct gif_softc *sc;

	sx_xlock(&gif_ioctl_sx);
	sc = ifp->if_softc;
	gif_delete_tunnel(sc);
	if (ng_gif_detach_p != NULL)
		(*ng_gif_detach_p)(ifp);
	bpfdetach(ifp);
	if_detach(ifp);
	ifp->if_softc = NULL;
	sx_xunlock(&gif_ioctl_sx);

	GIF_WAIT();
	if_free(ifp);
	free(sc, M_GIF);
}