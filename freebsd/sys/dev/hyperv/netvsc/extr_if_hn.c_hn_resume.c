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
struct hn_softc {int hn_flags; scalar_t__ hn_pollhz; TYPE_1__* hn_ifp; int /*<<< orphan*/ * hn_vf_ifp; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int HN_FLAG_RXVF ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  hn_polling (struct hn_softc*,scalar_t__) ; 
 int /*<<< orphan*/  hn_resume_data (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_resume_mgmt (struct hn_softc*) ; 
 scalar_t__ hn_xpnt_vf ; 

__attribute__((used)) static void
hn_resume(struct hn_softc *sc)
{

	/*
	 * If the non-transparent mode VF is activated, the synthetic
	 * device have to receive packets, so the data path of the
	 * synthetic device must be resumed.
	 */
	if ((sc->hn_ifp->if_drv_flags & IFF_DRV_RUNNING) ||
	    (sc->hn_flags & HN_FLAG_RXVF))
		hn_resume_data(sc);

	/*
	 * Don't resume link status change if VF is attached/activated.
	 * - In the non-transparent VF mode, the synthetic device marks
	 *   link down until the VF is deactivated; i.e. VF is down.
	 * - In transparent VF mode, VF's media status is used until
	 *   the VF is detached.
	 */
	if ((sc->hn_flags & HN_FLAG_RXVF) == 0 &&
	    !(hn_xpnt_vf && sc->hn_vf_ifp != NULL))
		hn_resume_mgmt(sc);

	/*
	 * Re-enable polling if this interface is running and
	 * the polling is requested.
	 */
	if ((sc->hn_ifp->if_drv_flags & IFF_DRV_RUNNING) && sc->hn_pollhz > 0)
		hn_polling(sc, sc->hn_pollhz);
}