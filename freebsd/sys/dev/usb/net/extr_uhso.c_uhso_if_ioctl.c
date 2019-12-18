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
typedef  int u_long ;
struct uhso_softc {int /*<<< orphan*/  sc_mtx; } ;
struct ifnet {int if_flags; int if_drv_flags; struct uhso_softc* if_softc; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
#define  SIOCADDMULTI 131 
#define  SIOCDELMULTI 130 
#define  SIOCSIFADDR 129 
#define  SIOCSIFFLAGS 128 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhso_if_init (struct uhso_softc*) ; 
 int /*<<< orphan*/  uhso_if_stop (struct uhso_softc*) ; 

__attribute__((used)) static int
uhso_if_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct uhso_softc *sc;

	sc = ifp->if_softc;

	switch (cmd) {
	case SIOCSIFFLAGS:
		if (ifp->if_flags & IFF_UP) {
			if (!(ifp->if_drv_flags & IFF_DRV_RUNNING)) {
				uhso_if_init(sc);
			}
		}
		else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				mtx_lock(&sc->sc_mtx);
				uhso_if_stop(sc);
				mtx_unlock(&sc->sc_mtx);
			}
		}
		break;
	case SIOCSIFADDR:
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		break;
	default:
		return (EINVAL);
	}
	return (0);
}